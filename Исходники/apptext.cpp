void sTextControl::Engine(sInt pos,sInt count,sChar *insert)
{
  sInt len;
  sInt i;

  if(Static)
    return;
  Post(DoneCmd);
  Changed = 1;

  len = sGetStringLen(Text);
  if(insert)
  {
    Realloc(len+count+1);
    for(i=len;i>=pos;i--)
      Text[i+count] = Text[i];
    sCopyMem(Text+pos,insert,count);
  }
  else
  {
    if(pos+count<=len)
      sCopyMem(Text+pos,Text+pos+count,len-pos-count+1);
  }
}