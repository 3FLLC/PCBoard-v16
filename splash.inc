Procedure doSplash(Color:Boolean);
Begin
   If Color then Begin
      Session.SetANSIMode; {Enabled PCB Pipes}
      Session.AnsiClrScr;
      UserASCIIMode:=False;
   End
   Else Begin
      Session.ClrScr;     {Otherwise filter out Pipes}
      UserASCIIMode:=True;
   End;
   SendFile('GEN/WELCOME');
End;
