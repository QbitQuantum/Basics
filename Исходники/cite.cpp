static QCString getListOfBibFiles(const QCString &sep,bool namesOnly)
{
  QCString result;
  QStrList &citeDataList = Config_getList("CITE_BIB_FILES");
  const char *bibdata = citeDataList.first();
  while (bibdata)
  {
    int i;
    QCString bibFile = bibdata;
    if (namesOnly && bibFile.right(4)==".bib") // strip extension
    {
      bibFile = bibFile.left(bibFile.length()-4);
    }
    if ((i=bibFile.findRev('/'))!=-1) // strip path
    {
      bibFile = bibFile.mid(i+1);
    }
    if (!bibFile.isEmpty())
    {
      if (namesOnly) // bare names
      {
        result+=bibFile;
      }
      else // add quotes for paths with spaces
      {
        result+="\""+bibFile+"\""; 
      }
      bibdata = citeDataList.next();
      if (bibdata)
      {
        result+=sep;
      }
    }
    else
    {
      bibdata = citeDataList.next();
    }
  }
  return result;
}