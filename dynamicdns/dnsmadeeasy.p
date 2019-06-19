Program DNSMadeEasy.DDNS.Update;
(* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * PROGRAM: Update Dynamic DNS Record in DNS Made Easy Records             *
 * AUTHOR: Original Java code by Esoteric Software. Port by Ozz Nixon      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *)

/*
 * run this: curl https://curl.haxx.se/ca/cacert.pem > ca-bundles.crt
 */

uses
   Sockets, DateTime, Display, Strings, Environment;

{ Original CONFIG.TXT structure
User:
Password:
Record ID:
Minutes: 30
Last IP:
Exit: false
}

Type
   MemConfRec = Packed Record
      UserID:String;
      Password:String;
      RecordID:String;
      Minutes:Longint;
      LastIP:String;
      Exit:Boolean;
      UseSSL:Boolean;
   End;

Var
   HomePath:String;
   memoryRecord:MemConfRec;

Procedure ShowHelp;
Begin
   TextColor(12);
   Write(' » ');
   TextColor(11);
   Writeln('DNSMadeEasy DDNS Update v1.6.18 (Beta 1)');
   TextColor(14);
   Writeln('   (c)opyright 2019 by Modern Pascal Solutions, Inc.');
   TextColor(10);
   Writeln('');
   Writeln('tool creates a ~/.dnsmadeeasy/config.txt file (fields in this order):');
   Writeln('User:');
   Writeln('Password:');
   Writeln('Record ID:');
   Write('Minutes: ');
   TextColor(15);
   Writeln('30');
   TextColor(10);
   Writeln('Last IP:');
   Write('Exit: ');
   TextColor(15);
   Writeln('false');
   TextColor(10);
   Write('Use SSL: ');
   TextColor(15);
   Writeln('false');
   Writeln('');
   TextColor(7);
   Writeln('Tool will poll myip.dnsmadeeasy.com port 80 for IP difference(s)');
   Halt(0);
End;

Procedure loadConfig;
var
   TFH:Text;
   Ws,Ts:String;

Begin
   AssignText(TFH, HomePath+'/.dnsmadeeasy/config.txt');
   Reset(TFH);
   While not EndOfText(TFH) do begin
      Ws:=ReadlnText(TFH);
      Ts:=Uppercase(Fetch(Ws,':'));
      Ws:=Trim(Ws);
      If TS='USER' then MemoryRecord.UserID:=Ws
      Else If TS='PASSWORD' then MemoryRecord.Password:=Ws
      Else If TS='RECORD ID' then MemoryRecord.RecordID:=Ws
      Else If TS='MINUTES' then MemoryRecord.Minutes:=StrToIntDef(Ws,5)
      Else If TS='LAST IP' then MemoryRecord.LastIP:=Ws
      Else If TS='EXIT' then MemoryRecord.Exit:=(Uppercase(Ws)='TRUE')
      Else If TS='USE SSL' then MemoryRecord.UseSSL:=(Uppercase(Ws)='TRUE')
      Else Begin
         TextColor(4);
         Writeln('');
         Writeln('Invalid Structure of CONFIG.TXT '+Ts+': '+Ws);
         Writeln('');
         CloseText(TFH);
         ShowHelp;
      End;
   End;
   CloseText(TFH);
End;

Procedure saveConfig;
var
   TFH:Text;

Begin
   AssignText(TFH, HomePath+'/.dnsmadeeasy/config.txt');
   Rewrite(TFH);
   WritelnText(TFH,'User: '+MemoryRecord.UserID);
   WritelnText(TFH,'Password: '+MemoryRecord.Password);
   WritelnText(TFH,'Record ID: '+MemoryRecord.RecordID);
   WritelnText(TFH,'Minutes: '+IntToStr(MemoryRecord.Minutes));
   WritelnText(TFH,'Last IP: '+MemoryRecord.LastIP);
   WritelnText(TFH,'Exit: '+BoolToStr(MemoryRecord.Exit));
   WritelnText(TFH,'Use SSL: '+BoolToStr(MemoryRecord.UseSSL));
   CloseText(TFH);
End;

Procedure doPoll;
Const
   UseSSLPort:Array [0..1] of Integer=[80,443];

var
   SSLClient:TDXSock;
   Ws:String;
   getHeader:Boolean;

Begin
   Writeln(FormatTimestamp('dddd, mmmm dd yyyy hh:nn:ss',Timestamp),' tool started.');
   Writeln('Last IP was: ',MemoryRecord.LastIP);
   SSLClient.Init;
   Repeat
      Ws:=MemoryRecord.LastIP;
// GET MYIP
      If SSLClient.ConnectTo('myip.dnsmadeeasy.com',UseSSLPort[Ord(MemoryRecord.UseSSL)]) then begin
         If MemoryRecord.UseSSL then begin
            If not SSLClient.EnableEncryption(hsAsClient, clAllLevels,
               //'IDEA-CBC-MD5:DES-CBC3-MD5:DES-CBC-MD5',
               'DES-CBC-SHA:DES-CBC3-SHA:AES128-SHA:AES256-SHA:AES128-SHA256:AES256-SHA256',
               './ca-bundles.crt', '', '', '', False, False) then begin
               Writeln('SSL/TLS Negotiation Error: ',SSLClient.LastCommandStatus);
               SSLClient.Free;
               Halt(1);
            End;
         End;
         SSLClient.Writeln('GET / HTTP/1.0'+#13#10);
         getHeader:=True;
         While getHeader do begin
            Ws:=SSLClient.Readln(300);
            getHeader:=Ws!='';
         End;
         Ws:=SSLClient.Readln(300);
         SSLClient.Disconnect;
      End
      Else begin
         Writeln('Failed to connect to myip.dnsmadeeasy.com');
         SSLClient.Free;
         Halt(3);
      End;
      If Ws<>MemoryRecord.LastIP then begin
         MemoryRecord.LastIP:=Ws;
         Writeln('IP is now: ',MemoryRecord.LastIP);
// UPDATE MYIP
         If SSLClient.ConnectTo('cp.dnsmadeeasy.com',UseSSLPort[Ord(MemoryRecord.UseSSL)]) then begin
            If MemoryRecord.UseSSL then begin
               If not SSLClient.EnableEncryption(hsAsClient, clAllLevels,
                  //'IDEA-CBC-MD5:DES-CBC3-MD5:DES-CBC-MD5',
                  'DES-CBC-SHA:DES-CBC3-SHA:AES128-SHA:AES256-SHA:AES128-SHA256:AES256-SHA256',
                  './ca-bundles.crt', '', '', '', False, False) then begin
                  Writeln('SSL/TLS Negotiation Error: ',SSLClient.LastCommandStatus);
                  SSLClient.Free;
                  Halt(1);
               End;
            End;
            SSLClient.Writeln('GET /servlet/updateip?username='+MemoryRecord.UserID+
               '&password='+MemoryRecord.Password+
               '&id='+MemoryRecord.RecordID+
               '&ip='+MemoryRecord.LastIP+' HTTP/1.0'+#13#10);
            getHeader:=True;
            While getHeader do begin
               Ws:=SSLClient.Readln(300);
               getHeader:=Ws!='';
            End;
            Ws:=SSLClient.Readln(300);
            If (Ws<>'success') then begin
               Writeln('Updating DNS Made Easy Error!');
               SSLClient.Disconnect;
               SSLClient.Free;
               Halt(2);
            End;
            SSLClient.Disconnect;
            saveConfig;
            Writeln(FormatTimestamp('dddd, mmmm dd yyyy hh:nn:ss',Timestamp),' DNS Made Easy and config.txt were updated.');
         End;
      End
      Else Write('No change. ');
      if not (MemoryRecord.Exit) then begin
         Writeln('Sleeping ',MemoryRecord.Minutes,' minutes.');
         Yield(MemoryRecord.Minutes* (60000));
      end;
   Until MemoryRecord.Exit;
   SSLClient.Free;
End;

Begin
   HomePath:=GetEnv('HOME');
   If HomePath='' then HomePath:='/etc';
   If FileExists(HomePath+'/.dnsmadeeasy/config.txt') then begin
      loadConfig;
      doPoll;
   end
   else ShowHelp;
End;
