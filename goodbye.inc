Procedure doGoodbye;
Begin
   Session.Writeln('');
   Session.PipeWrite('|0BAre you sure you want to disconnect (|0FEnter|0B)=no? (|07N|0F)|07'#8#8);
   If Uppercase(GetNY)='N' then Exit;
   Session.Writeln('');
   Session.PipeWrite('|0FLeave a comment for the sysop (|0AEnter|0F)=no? (|07N|0F)|07'#8#8);
   If Uppercase(GetNY)='Y' then doTextEditor;
   ShowElapsedTime;
End;
