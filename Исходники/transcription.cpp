string CTranscription::duodec2dec(string val)
{
  long i, n, digit;
  string res;

  n=0;
  for(i=val.size()-1;i>=0;i--)
  {
    if((val[i]>='0')&&(val[i]<='9'))
      digit=val[i]-'0';
    else
      digit=val[i]-'a'+10;
    n+=digit*(int)pow((float)12, (int)(val.size()-i-1));
  }
  res=ltoa(n);

  return res;
}