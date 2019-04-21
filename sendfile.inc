Procedure SendFile(FName:String);
var
   SendFile:TStringList;
   LineCount:Byte;
   Ws,Prefix:String;
   Loop:Longint;

Begin
   If FileExists(FName) then Prefix:='';
   If FileExists(RootPath+FName) then Prefix:=RootPath;
   If not FileExists(Prefix+FName) then begin
      Session.PipeWriteln(Prefix+FName+' not found.');
      Exit;
   End;
   LineCount:=0;
   SendFile.Init;
   SendFile.LoadFromFile(Prefix+FName);
   For Loop:=0 to SendFile.getCount-1 do begin
      Ws:=StringReplace(SendFile.getStrings(Loop),'@X','|',[rfReplaceAll]);
      Session.PipeWriteln(ProcessPCBMacro(Ws));
      Inc(LineCount);
      If (LineCount>UserRec.Pagelen) and (UserRec.Pagelen>0) then begin
         Session.PipeWrite('|0E(|04'+IntToStr((DisconnectAt-Timestamp) div 60)+'|0E min. left), More? |07');
         If Uppercase(GetYN)<>'Y' then break;
         LineCount:=0;
      End;
   End;
   SendFile.Free;
End;
