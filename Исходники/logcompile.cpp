//***************************************************
int Logic::AddIncludes()
{
  TStringList IncludeStrings,IncludeLines;
  int  CurInputLine,CurIncludeLine;
  string filename;
  int err=0;
  string::size_type pos1,pos2;
  int CurLine;
  char *ptr;

  IncludeFilenames = TStringList();
  IncludeStrings = TStringList();
  EditLines = TStringList();
  IncludeLines = TStringList();
  CurLine = 0;
  for(CurInputLine = 0;CurInputLine<InputLines.num;CurInputLine++){
    EditLines.add(InputLines.at(CurInputLine));
    CurLine = EditLines.num -1;
    RealLineNum[CurLine] = CurInputLine;
    LineFile[CurLine] = 0;
#ifdef _WIN32
    if(_strnicmp(InputLines.at(CurInputLine).c_str(),"#include",8)) {
#else
    if(strncasecmp(InputLines.at(CurInputLine).c_str(),"#include",8)){
#endif
      continue;
    }
    string str = InputLines.at(CurInputLine).substr(8);
    if(str.length()<4){
      ShowError(CurLine,"Missing include filename !");
      err=1;
      continue;
    }
    if(str[0] != ' '){
      ShowError(CurLine,"' ' expected after #include.");
      err=1;
      continue;
    }
    pos1 = str.find_first_of("\"",1);
    pos2 = str.find_first_of("\"",pos1+1);
    if(pos1 == string::npos || pos2 == string::npos){
      ShowError(CurLine,"Include filenames need quote marks around them.");
      err=1;
      continue;
    }
    filename = str.substr(pos1+1,pos2-pos1-1);
    if(filename.find_first_of("/")!=string::npos){
      ShowError(CurLine,"Only files in the src directory can be included.");
      err=1;
      continue;
    }
    sprintf(tmp,"%s/src/%s",game->dir.c_str(),filename.c_str());
    FILE *fptr = fopen(tmp,"rb");
    if(fptr==NULL){
      sprintf(tmp,"Can't open include file: %s/src/%s",game->dir.c_str(),filename.c_str());
      ShowError(CurLine,tmp);
      err=1;
      continue;
    }
    IncludeLines.lfree();

    while(fgets(tmp,MAX_TMP,fptr)!=NULL){
      if((ptr=strchr(tmp,0x0a)))*ptr=0;
      if((ptr=strchr(tmp,0x0d)))*ptr=0;
      IncludeLines.add(tmp);
    }
    fclose(fptr);
    if(IncludeLines.num==0)continue;
    IncludeFilenames.add(filename);
    RemoveComments(IncludeLines);
    EditLines.replace(CurLine,empty_tmp);
    for(CurIncludeLine=0;CurIncludeLine<IncludeLines.num;CurIncludeLine++){
      EditLines.add(IncludeLines.at(CurIncludeLine));
      CurLine=EditLines.num-1;
      RealLineNum[CurLine] = CurIncludeLine;
      LineFile[CurLine] = IncludeFilenames.num;
    }
  }

  IncludeLines.lfree();
  InputLines.lfree();
  return err;

}

//***************************************************
int Logic::ReadDefines()
{
  int err=0,i;
  string::size_type pos1,pos2;
  string ThisDefineName,ThisDefineValue;
  int CurLine;

  NumDefines = 0;
  for(CurLine = 0;CurLine<EditLines.num;CurLine++){
#ifdef _WIN32
    if(_strnicmp(EditLines.at(CurLine).c_str(),"#define",7)){
#else
    if(strncasecmp(EditLines.at(CurLine).c_str(),"#define",7)){
#endif
      continue;
    }
    string str = EditLines.at(CurLine).substr(7);
    toLower(&str);
    if(str.length()<4){
      ShowError(CurLine,"Missing define name !");
      err=1;
      continue;
    }
    if(str[0] != ' '){
      ShowError(CurLine,"' ' expected after #define.");
      err=1;
      continue;
    }
    if(NumDefines >= MaxDefines){
      ShowError(CurLine,"Too many defines (max " + IntToStr(MaxDefines) + ")");
      err=1;
      continue;
    }
    pos1 = str.find_first_not_of(" ",1);
    pos2 = str.find_first_of(" ",pos1);
    if(pos1 == string::npos||pos2 == string::npos){
      ShowError(CurLine,"Missing define name !");
      err=1;
      continue;
    }
    ThisDefineName = str.substr(pos1,pos2-1);
    if(ThisDefineName.find_first_not_of("qwertyuiopasdfghjklzxcvbnm1234567890._") != string::npos){
      ShowError(CurLine,"Define name can contain only characters from [a-z],'.' and '_'.");
      err=1;
      continue;
    }
    for(i=0;i<NumDefines;i++){
      if(ThisDefineName == DefineNames[i]){
        ShowError(CurLine,ThisDefineName + " already defined !");
        err=1;
        break;
      }
    }
    if(err)continue;

    for(i=0;i<=NumAGICommands;i++){
      if(ThisDefineName == AGICommand[i].Name){
        ShowError(CurLine,"Define name can not be a command name.");
        err=1;
        break;
      }
    }
    if(err)continue;

    for(i=1;i<=NumTestCommands;i++){
      if(ThisDefineName == TestCommand[i].Name){
        ShowError(CurLine,"Define name can not be a command name.");
        err=1; break;
      }
    }
    if(err)continue;

    if(ThisDefineName == "if" || ThisDefineName == "else" || ThisDefineName == "goto"){
      ShowError(CurLine,"Invalid define name (" + ThisDefineName + ")");
      err=1;
      continue;
    }

    pos1 = str.find_first_not_of(" ",pos2+1);
    if(pos1 == string::npos){
      ShowError(CurLine,"Missing define value !");
      err=1;
      continue;
    }
    if(str[pos1] == '"'){
      ThisDefineValue = "\"" + ReadString(&pos1,str) + "\"";
      if(ErrorOccured)continue;
      if(str.find_first_not_of(" ",pos1) != string::npos){
        ShowError(CurLine,"Nothing allowed on line after define value.");
        err=1;
        continue;
      }
    }
    else{
      pos2 = str.find_first_of(" ",pos1+1);
      if(pos2 == string::npos){
        ThisDefineValue = str.substr(pos1);
      }
      else{
        ThisDefineValue = str.substr(pos1,pos2-pos1);
        if(str.find_first_not_of(" ",pos2) != string::npos){
          ShowError(CurLine,"Nothing allowed on line after define value.");
          err=1;
          continue;
        }
      }
      if(ThisDefineValue.find_first_not_of("qwertyuiopasdfghjklzxcvbnm1234567890._") != string::npos){
        ShowError(CurLine,"Non-string define value can contain only characters from [a-z],'.' and '_'.");
        err=1;
        continue;
      }
    }

    DefineNames[NumDefines]=ThisDefineName;
    DefineValues[NumDefines]=ThisDefineValue;
    DefineNameLength[NumDefines] = ThisDefineName.length();
    NumDefines++;
    EditLines.replace(CurLine,empty_tmp);
  }

  return err;
}

//***************************************************
int Logic::ReadPredefinedMessages()
{
  int err=0,i;
  string::size_type pos1;
  int MessageNum;

  for(i=0;i<MaxMessages;i++){
    Messages[i]="";
    MessageExists[i]=false;
  }
  for(CurLine = 0;CurLine<EditLines.num;CurLine++){
#ifdef _WIN32
    if(_strnicmp(EditLines.at(CurLine).c_str(),"#message",8)){
#else
    if(strncasecmp(EditLines.at(CurLine).c_str(),"#message",8)){
#endif
      continue;
    }
    string str = EditLines.at(CurLine).substr(8);
    if(str[0] != ' '){
      ShowError(CurLine,"' ' expected after #message.");
      err=1;
      continue;
    }
    MessageNum = atoi(str.c_str());
    if(MessageNum==0){
      ShowError(CurLine,"Invalid message number (must be 1-255).");
      err=1;
      continue;
    }
    pos1 = str.find_first_of("\"");
    if(pos1 == string::npos){
      ShowError(CurLine,"\" required at start of string.");
      err=1;
      continue;
    }
    Messages[MessageNum]=ReadString(&pos1,str);
    if(ErrorOccured)continue;
    if(Messages[MessageNum].find_first_not_of(" ",pos1) != string::npos){
      sprintf(tmp,"Nothing allowed on line after message. ");
      ShowError(CurLine,tmp);
      err=1;
      continue;
    }
    MessageExists[MessageNum] =true;
    EditLines.replace(CurLine,empty_tmp);
  }

  return err;

}
//***************************************************
int Logic::ReadLabels()
{
  int err=0,i;
  string::size_type pos1,pos2;
  string LabelName;
  int CurLine;

  NumLabels = 0;
  for(CurLine = 0;CurLine<EditLines.num;CurLine++){
    string str = EditLines.at(CurLine);
    toLower(&str);
    pos1 = str.find_first_not_of(" ");
    if(pos1 == string::npos)continue;
    pos2 = str.find_first_not_of("qwertyuiopasdfghjklzxcvbnm1234567890._",pos1);
    if(pos2 == string::npos)continue;
    if((pos1 == pos2) || (str[pos2]!=':'))continue;
    LabelName = str.substr(pos1,pos2-pos1);
    for(i=1;i<=NumLabels;i++){
      if(LabelName == Labels[i].Name){
        ShowError(CurLine,"Label "+LabelName+" already defined.");
        err=1;break;
      }
    }
    if(err)continue;
    if(NumLabels > MaxLabels){
      ShowError(CurLine,"Too many labels (max "+IntToStr(MaxLabels)+")");
      err=1;continue;
    }
    if(LabelName == "if" || LabelName == "else" || LabelName == "goto"){
      ShowError(CurLine,"Invalid label name ("+LabelName+")");
      err=1;continue;
    }
    for(i=0;i<NumDefines;i++){
      if((LabelName == DefineNames[i]) || (LabelName+":" == DefineNames[i])){
        ShowError(CurLine,"Can't have a label with the same name a a define.");
        err=1;break;
      }
    }
    if(err)continue;
    NumLabels++;
    Labels[NumLabels].Name = LabelName;
    Labels[NumLabels].Loc = 0;
  }

  return err;

}