{############################################################################
#   Purpose....: Centralize all PCBoard related INPUT routines in one file. #
#   Design Goal: Help refactor v16 INPUT routines, simplify modifications   #
#   ...........:                                                            #
#   ...........:                                                            #
#   Created....: 1190415 by G.E. Ozz Nixon Jr.                              #
############################################################################}

Function GetPassword(L:Longint):String;
var
   Ch:Char;
   Ws:String;
   Loop:Longint;
   Possible:TCharArray;

Label
   GetNextChar;

Begin
   Possible:=[#13,#8,#127];
   For Loop:=32 to 126 do begin
      SetLength(Possible,Length(Possible)+1);
      Possible[Length(Possible)-1]:=Chr(Loop);
   End;
// Like a FLUSH //
   While Session.CountWaiting>0 do begin
      Session.ReadStr(Session.CountWaiting,500);
      Yield(1);
   End;
   Result:='';
GetNextChar:
   Ch:=Session.ReadChar(Possible,300);

   Case Ch of
      #0:Begin
         TimedOut;
         Exit;
      End;
      #127,#8:If Length(Ws)>0 then Begin
         Delete(Ws,Length(Ws),1);
         Session.Write(#8#32#8);
      End
      Else Session.Write(#7);
      #13:Begin
         Result:=Ws;
         Session.Writeln('');
         Exit;
      End;
      Else Begin
         Session.Write('%');
         Ws+=Ch;
      End;
   End;

   Goto GetNextChar;
End;

Function GetPhone(L:Longint):String;
var
   Ch:Char;
   Ws:String;
   Loop:Longint;
   Possible:TCharArray;

Label
   GetNextChar;

Begin
   Possible:=[#13,#8,#127,'0','1','2','3','4','5','6','7','8','9','(',')','-','+'];
// Like a FLUSH //
   While Session.CountWaiting>0 do begin
      Session.ReadStr(Session.CountWaiting,500);
      Yield(1);
   End;
   Result:='';
GetNextChar:
   Ch:=Session.ReadChar(Possible,300);

   Case Ch of
      #0:Begin
         TimedOut;
         Exit;
      End;
      #127,#8:If Length(Ws)>0 then Begin
         Delete(Ws,Length(Ws),1);
         Session.Write(#8#32#8);
      End
      Else Session.Write(#7);
      #13:Begin
         Result:=Ws;
         Session.Writeln('');
         Exit;
      End;
      Else Begin
         Session.Write(Ch);
         Ws+=Ch;
      End;
   End;

   Goto GetNextChar;
End;

Function GetNumberOnly(L:Longint):String;
var
   Ch:Char;
   Ws:String;
   Loop:Longint;
   Possible:TCharArray;

Label
   GetNextChar;

Begin
   Possible:=[#13,#8,#127,'0','1','2','3','4','5','6','7','8','9'];
// Like a FLUSH //
   While Session.CountWaiting>0 do begin
      Session.ReadStr(Session.CountWaiting,500);
      Yield(1);
   End;
   Result:='';
GetNextChar:
   Ch:=Session.ReadChar(Possible,300);

   Case Ch of
      #0:Begin
         TimedOut;
         Exit;
      End;
      #127,#8:If Length(Ws)>0 then Begin
         Delete(Ws,Length(Ws),1);
         Session.Write(#8#32#8);
      End
      Else Session.Write(#7);
      #13:Begin
         Result:=Ws;
         Session.Writeln('');
         Exit;
      End;
      Else Begin
         Session.Write(Ch);
         Ws+=Ch;
      End;
   End;

   Goto GetNextChar;
End;

Function GetNumberQuit(L:Longint):String;
var
   Ch:Char;
   Ws:String;
   Loop:Longint;
   Possible:TCharArray;

Label
   GetNextChar;

Begin
   Possible:=[#13,#8,#127,'0','1','2','3','4','5','6','7','8','9','q','Q'];
// Like a FLUSH //
   While Session.CountWaiting>0 do begin
      Session.ReadStr(Session.CountWaiting,500);
      Yield(1);
   End;
   Result:='';
GetNextChar:
   Ch:=Session.ReadChar(Possible,300);

   Case Ch of
      #0:Begin
         TimedOut;
         Exit;
      End;
      #127,#8:If Length(Ws)>0 then Begin
         Delete(Ws,Length(Ws),1);
         Session.Write(#8#32#8);
      End
      Else Session.Write(#7);
      #13:Begin
         If Ws='' then Ws:='Q';
         Result:=Ws;
         Session.Writeln('');
         Exit;
      End;
      Else Begin
         Session.Write(Ch);
         Ws+=Ch;
      End;
   End;

   Goto GetNextChar;
End;
Function GetInput(L:Longint):String;
var
   Ch:Char;
   Ws:String;
   Loop:Longint;
   Possible:TCharArray;

Label
   GetNextChar;

Begin
   Possible:=[#13,#8,#127];
   For Loop:=32 to 126 do begin
      SetLength(Possible,Length(Possible)+1);
      Possible[Length(Possible)-1]:=Chr(Loop);
   End;
// Like a FLUSH //
   While Session.CountWaiting>0 do begin
      Session.ReadStr(Session.CountWaiting,500);
      Yield(1);
   End;
   Result:='';
GetNextChar:
   Ch:=Session.ReadChar(Possible,300);

   Case Ch of
      #0:Begin
         TimedOut;
         Exit;
      End;
      #127,#8:If Length(Ws)>0 then Begin
         Delete(Ws,Length(Ws),1);
         Session.Write(#8#32#8);
      End
      Else Session.Write(#7);
      #13:Begin
         Result:=Ws;
         Session.Writeln('');
         Exit;
      End;
      Else Begin
         Session.Write(Ch);
         Ws+=Ch;
      End;
   End;

   Goto GetNextChar;
End;

Function GetInputWrap(L:Longint;var Wrap:String):String;
var
   Ch:Char;
   Ws:String;
   Loop:Longint;
   Possible:TCharArray;

Label
   GetNextChar;

Begin
   If Wrap<>'' then begin
      Session.Write(Wrap);
      Ws:=Wrap;
   End;
   Wrap:='';
   Result:='';
   Possible:=[#8,#13];
   For Loop:=32 to 254 do begin
      SetLength(Possible,Length(Possible)+1);
      Possible[Length(Possible)-1]:=Chr(Loop);
   End;
// Like a FLUSH //
   While Session.CountWaiting>0 do begin
      Session.ReadStr(Session.CountWaiting,500);
      Yield(1);
   End;
GetNextChar:
   Ch:=Session.ReadChar(Possible,300);

   Case Ch of
      #0:Begin
         TimedOut;
         Exit;
      End;
      #127,#8:If Length(Ws)>0 then Begin
         Delete(Ws,Length(Ws),1);
         Session.Write(#8#32#8);
      End
      Else Session.Write(#7);
      #13:Begin
         Result:=Ws;
//         Session.Writeln('');
         Exit;
      End;
      Else Begin
         Session.Write(Ch);
         Ws+=Ch;
      End;
   End;

   If Length(Ws)=72 then begin
      Loop:=72;
      While Loop>62 do begin
         If Ws[Loop]=#32 then begin
            Wrap:=Copy(Ws,Loop+1,255);
            Delete(Ws,Loop,255);
            Result:=Ws;
            Exit;
         End
         Else Dec(Loop);
      End;
   End;

   Goto GetNextChar;
End;

Function GetYN:String;
var
   Ch:Char;
   Ws:String;

Label
   GetNextChar;

Begin
// Like a FLUSH //
   While Session.CountWaiting>0 do begin
      Session.ReadStr(Session.CountWaiting,500);
      Yield(1);
   End;
   Result:='';
GetNextChar:
   If Length(Ws)>0 then
      Ch:=Session.ReadChar([#13,#8,#127],300)
   Else
      Ch:=Session.ReadChar([#13,'y','Y','n','N'],300);

   Case Ch of
      #0:Begin
         TimedOut;
         Exit;
      End;
      #127,#8:If Length(Ws)>0 then Begin
         Delete(Ws,Length(Ws),1);
         Session.Write(#8#32#8);
      End
      Else Session.Write(#7);
      #13:Begin
         If Ws='' then Ws:='Y';
         Result:=Ws;
         Session.Writeln('');
         Exit;
      End;
      Else Begin
         Session.Write(Ch);
         Ws+=Ch;
      End;
   End;

   Goto GetNextChar;
End;

Function GetNY:String;
var
   Ch:Char;
   Ws:String;

Label
   GetNextChar;

Begin
// Like a FLUSH //
   While Session.CountWaiting>0 do begin
      Session.ReadStr(Session.CountWaiting,500);
      Yield(1);
   End;
   Result:='';
GetNextChar:
   If Length(Ws)>0 then
      Ch:=Session.ReadChar([#13,#8,#127],300)
   Else
      Ch:=Session.ReadChar([#13,'y','Y','n','N'],300);

   Case Ch of
      #0:Begin
         TimedOut;
         Exit;
      End;
      #127,#8:If Length(Ws)>0 then Begin
         Delete(Ws,Length(Ws),1);
         Session.Write(#8#32#8);
      End
      Else Session.Write(#7);
      #13:Begin
         If Ws='' then Ws:='N';
         Result:=Ws;
         Session.Writeln('');
         Exit;
      End;
      Else Begin
         Session.Write(Ch);
         Ws+=Ch;
      End;
   End;

   Goto GetNextChar;
End;

Function GetRC:String;
var
   Ch:Char;
   Ws:String;

Label
   GetNextChar;

Begin
// Like a FLUSH //
   While Session.CountWaiting>0 do begin
      Session.ReadStr(Session.CountWaiting,500);
      Yield(1);
   End;
   Result:='';
GetNextChar:
   If Length(Ws)>0 then
      Ch:=Session.ReadChar([#13,#8,#127],300)
   Else
      Ch:=Session.ReadChar([#13,'r','R','c','C'],300);

   Case Ch of
      #0:Begin
         TimedOut;
         Exit;
      End;
      #127,#8:If Length(Ws)>0 then Begin
         Delete(Ws,Length(Ws),1);
         Session.Write(#8#32#8);
      End
      Else Session.Write(#7);
      #13:Begin
         If Ws='' then Ws:='C';
         Result:=Ws;
         Session.Writeln('');
         Exit;
      End;
      Else Begin
         Session.Write(Ch);
         Ws+=Ch;
      End;
   End;

   Goto GetNextChar;
End;

Function GetAXCOZY:String;
var
   Ch:Char;
   Ws:String;

Label
   GetNextChar;

Begin
// Like a FLUSH //
   While Session.CountWaiting>0 do begin
      Session.ReadStr(Session.CountWaiting,500);
      Yield(1);
   End;
   Result:='';
GetNextChar:
   If Length(Ws)>0 then
      Ch:=Session.ReadChar([#13,'a','x','c','o','z','y','A','X','C','O','Z','Y',#8,#127],300)
   Else
      Ch:=Session.ReadChar([#13,'a','x','c','o','z','y','A','X','C','O','Z','Y'],300);

   Case Ch of
      #0:Begin
         TimedOut;
         Exit;
      End;
      #127,#8:If Length(Ws)>0 then Begin
         Delete(Ws,Length(Ws),1);
         Session.Write(#8#32#8);
      End;
      #13:Begin
         If Ws='' then Ws:='Z';
         Result:=Ws;
         Session.Writeln('');
         Exit;
      End;
      Else Begin
         Session.Write(Ch);
         Ws+=Ch;
      End;
   End;

   Goto GetNextChar;
End;

Function GetACHLNQSWYZ(L:Longint):String;
var
   Ch:Char;
   Ws:String;

Label
   GetNextChar;

Begin
// Like a FLUSH //
   While Session.CountWaiting>0 do begin
      Session.ReadStr(Session.CountWaiting,500);
      Yield(1);
   End;
   Result:='';
GetNextChar:
   If Length(Ws)>0 then
      Ch:=Session.ReadChar([#13,';','a','c','h','l','n','q','s','w','y','z','A','C','H','L','N','Q','S','W','Y','Z',#8,#127],300)
   Else
      Ch:=Session.ReadChar([#13,';','a','c','h','l','n','q','s','w','y','z','A','C','H','L','N','Q','S','W','Y','Z'],300);

   Case Ch of
      #0:Begin
         TimedOut;
         Exit;
      End;
      #127,#8:If Length(Ws)>0 then Begin
         Delete(Ws,Length(Ws),1);
         Session.Write(#8#32#8);
      End;
      #13:Begin
         If Ws='' then Ws:='Y';
         Result:=Ws;
         Session.Writeln('');
         Exit;
      End;
      Else Begin
         Session.Write(Ch);
         Ws+=Ch;
      End;
   End;

   If Length(Ws)<=L then Goto GetNextChar;
End;

Function GetACDEFHILQSU:String;
var
   Ch:Char;
   Ws:String;

Label
   GetNextChar;

Begin
// Like a FLUSH //
   While Session.CountWaiting>0 do begin
      Session.ReadStr(Session.CountWaiting,500);
      Yield(1);
   End;
   Result:='';
GetNextChar:
   If Length(Ws)>0 then
      Ch:=Session.ReadChar([#13,'a','c','d','e','f','h','i','l','q','s','u',
                                'A','C','D','E','F','H','I','L','Q','S','U',#8,#127],300)
   Else
      Ch:=Session.ReadChar([#13,'a','c','d','e','f','h','i','l','q','s','u',
                                'A','C','D','E','F','H','I','L','Q','S','U'],300);

   Case Ch of
      #0:Begin
         TimedOut;
         Exit;
      End;
      #127,#8:If Length(Ws)>0 then Begin
         Delete(Ws,Length(Ws),1);
         Session.Write(#8#32#8);
      End;
      #13:Begin
         If Ws='' then Ws:='S';
         Result:=Ws;
         Session.Writeln('');
         Exit;
      End;
      Else Begin
         Session.Write(Ch);
         Ws+=Ch;
      End;
   End;

   Goto GetNextChar;
End;

Function GetNQUSY(L:Longint):String;
var
   Ch:Char;
   Ws:String;

Label
   GetNextChar;

Begin
// Like a FLUSH //
   While Session.CountWaiting>0 do begin
      Session.ReadStr(Session.CountWaiting,500);
      Yield(1);
   End;
   Result:='';
GetNextChar:
   If Length(Ws)>0 then
      Ch:=Session.ReadChar([#13,';','n','q','u','s','y','N','Q','U','S','Y',#8,#127],300)
   Else
      Ch:=Session.ReadChar([#13,';','n','q','u','s','y','N','Q','U','S','Y'],300);

   Case Ch of
      #0:Begin
         TimedOut;
         Exit;
      End;
      #127,#8:If Length(Ws)>0 then Begin
         Delete(Ws,Length(Ws),1);
         Session.Write(#8#32#8);
      End;
      #13:Begin
         If Ws='' then Ws:='N';
         Result:=Ws;
         Session.Writeln('');
         Exit;
      End;
      Else Begin
         Session.Write(Ch);
         Ws+=Ch;
      End;
   End;

   If Length(Ws)<=L then Goto GetNextChar;
End;
