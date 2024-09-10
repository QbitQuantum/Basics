int FMoreAction(char InputFile[MAX_LINE][MAX_CHAR_LINE],int *count)
{
  //char msg='p';
  int i0=0,i,j;
  //int listline[MAX_LINE];
  if (*count==(MAX_METHODS-1))
    {
      Fprintf(TOSCREEN,"\n Max Number of Methds Reached!\n");
      //msg='n';
    }else{
      i0=0;
      for(i=0;i<MAX_LINE;i++){
        if(strlen(InputFile[i])>1){
          j=0;
          while(isalpha(InputFile[i][j])==0)
            j++;
          if(((InputFile[i][j]=='M') || (InputFile[i][j]=='m')) && ((InputFile[i][j+1]=='A')
                                                                    ||(InputFile[i][j+1]=='a'))){
            //listline[i0]=i;
            i0++;
          }
        }
      }


    }
  if(i0==(*count))
    return WRONG;
  else{
    (*count)++; 
    return OK;
  }
}