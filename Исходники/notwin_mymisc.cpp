//---------------------------------------------------------------------------
UINT GetTempFileName(char *PathName,char *Prefix,UINT Unique,char *TempFileName)
{
  EasyStr Ret;
  WORD Num=WORD(Unique ? WORD(Unique):WORD(rand() & 0xffff));
  for(;;){
    Ret=PathName;
    Ret+=SLASH;
    Ret+=Prefix;
    Ret.SetLength(MAX_PATH+4);
    char *StartOfNum=Ret.Right()+1;
    ultoa(Num,StartOfNum,16);
    strupr(StartOfNum);
    Ret+=".TMP";
    if (Ret.Length()<MAX_PATH){
      if (Unique==0){
        if (access(Ret,0)==0){ //File exists
          Num++;
        }else{
          strcpy(TempFileName,Ret);
          fclose(fopen(TempFileName,"wb"));
          return Num;
        }
      }else{
        strcpy(TempFileName,Ret);
        return Num;
      }
    }else{
      return 0;
    }
  }
}