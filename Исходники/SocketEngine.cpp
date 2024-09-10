//////////////////////////////////////////////////////////////////////
// util
//////////////////////////////////////////////////////////////////////
void ReplaceUrl(TDes8& aUrl,const TDesC8& aIsRepeatedKStr,const TDesC8& aStr){
  HBufC8* tmp=HBufC8::NewL(aUrl.Length()+aStr.Length()+128);
  int iPos=aUrl.FindF(aIsRepeatedKStr);
  if(iPos>=0){
    tmp->Des().Copy(aUrl.Left(iPos)); //加上前面有用的字符
    tmp->Des().Append(aStr);
    int iStart=iPos+aIsRepeatedKStr.Length(); //要被替换的字符，加上要被替换的字符长度
    int iLen2=aUrl.Length()-iStart;
    tmp->Des().Append(aUrl.Mid(iStart,iLen2)); //加上后面有用的字符
    aUrl.Copy(tmp->Des());
  }
  delete tmp;
}