Procedure ShowElapsedTime;
var
   ElapsedMinutes:Longint;

Begin
   Session.Writeln('');
   ElapsedMinutes:=Timestamp-ConnectedAt;
   If ElapsedMinutes>59 then Session.PipeWriteln('|0BMinutes Used: '+IntToStr(ElapsedMinutes div 60)+'|07');
   If (UserFirstName<>'') then begin
      Session.Writeln('');
      Session.PipeWriteln('|0AThanks for calling, '+UserFirstName+'!|07');
   End;
   Session.Disconnect;
End;
