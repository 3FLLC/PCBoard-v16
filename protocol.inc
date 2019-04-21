Function doGetProtocol(ExitEarly:Boolean):String;
Begin
   Session.PipeWriteln('');
   Session.PipeWriteln('|0B   (A) Ascii');
   Session.PipeWriteln('   (X) Xmodem/Checksum');
   Session.PipeWriteln('   (C) Xmodem/CRC');
   Session.PipeWriteln('   (O) 1K-Xmodem       (a.k.a. non-BATCH Ymodem)');
   Session.PipeWriteln('   (Y) Ymodem BATCH');
   Session.PipeWriteln('|0F=>|0B (Z) Zmodem (batch)');
   Session.PipeWriteln('');
   Session.PipeWrite('|0ADefault Protocol Desired (|0FEnter|0A)=no change? (|07Z|0A)'#8#8);
   Result:=Uppercase(GetAXCOZY);
   If ExitEarly then Exit;
   Session.PipeWriteln('');
   Session.Prompt('|0APress (|0FEnter|0A) to continue? ',300);
End;
