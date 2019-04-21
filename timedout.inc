Procedure TimedOut;
var
   ElapsedMinutes:Longint;

Begin
   Session.Writeln('');
   Session.PipeWriteln('|0CKeyboard Time Expired!');
   ShowElapsedTime;
End;
