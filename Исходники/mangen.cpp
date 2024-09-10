static QCString buildFileName(const char *name)
{
  QCString fileName;
  if (name==0) return "noname";

  const char *p=name;
  char c;
  while ((c=*p++))
  {
    switch (c)
    {
      case ':':
        fileName+="_";
        if (*p==':') p++;
        break;
      case '<':
      case '>':
      case '&':
      case '*':
      case '!':
      case '^':
      case '~':
      case '%':
      case '+':
      case '/':
        fileName+="_";
        break;
      default:
        fileName+=c;
    }
  }

  QCString manExtension = "." + getExtension();
  if (fileName.right(manExtension.length())!=manExtension) 
  {
    fileName+=manExtension;
  }

  return fileName;
}