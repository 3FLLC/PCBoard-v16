Procedure doPageLength;
Begin
   Session.Writeln('');
   Session.PipeWriteln('|0APage Length is currently set to '+IntToStr(UserPageLength));
   Session.PipeWrite('|0EEnter new length (|0C0|0E)=continuous, (|0FEnter|0E)=no change? ('+
      PadLeft(IntToStr(UserPageLength),2)+')'#8#8#8);
   UserPageLength:=StrToIntDef(GetNumberOnly(2),23);
   If not Session.Connected then Exit; {always check after inputs!}
   If UserPageLength<>UserRec.Pagelen then begin
      UserRec.Pagelen:=UserPageLength;
      SaveUserRec;
      Session.Writeln('');
      Session.PipeWriteln('|0C'+UserFirstName+', your record has been updated with changes made.');
      Session.Writeln('');
      Session.Prompt('|0APress (|0FEnter|0A) to continue? ',300);
   End;
End;
