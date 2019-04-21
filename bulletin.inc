Procedure doBulletinViewer;
var
   Ws:String;

Begin
   While Session.Connected do begin
      SendFile('GEN/BLT');
      Session.Writeln('');
      Session.PipeWrite('|0E(1-1), Bulletin to view (|0FEnter|0E)=quit? |07');
      Ws:=GetNumberOnly(1);
      If not Session.Connected then Exit; {always check after inputs!}
      Case StrToIntDef(Ws,0) of
         0:Exit;
         1:Begin
            SendFile('GEN/BLT'+Ws);
            Session.Writeln('');
            Session.Prompt('|0APress (|0FEnter|0A) to continue? ',300);
         End;
         Else Begin
            Session.PipeWriteln('|0CInvalid Entry!  Please try again, '+UserFirstName+' ...');
            Yield(1000);
         End;
      End;
   End;
End;
