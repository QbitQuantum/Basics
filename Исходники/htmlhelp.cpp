QCString HtmlHelp::recode(const QCString &s) 
{
  int iSize        = s.length();
  int oSize        = iSize*4+1;
  QCString output(oSize);
  size_t iLeft     = iSize;
  size_t oLeft     = oSize;
  const char *iPtr = s.data();
  char *oPtr       = output.data();
  if (!portable_iconv(m_fromUtf8,&iPtr,&iLeft,&oPtr,&oLeft))
  {
    oSize -= oLeft;
    output.resize(oSize+1);
    output.at(oSize)='\0';
    return output;
  }
  else
  {
    return s;
  }
}