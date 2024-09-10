bool CHttpApi::checkForFunctionTypeParas(CStdString &cmd, CStdString &paras)
{
  int open, close;
  open = cmd.Find("(");
  if (open>0)
  {
    close=cmd.length();
    while (close>open && cmd.Mid(close,1)!=")")
      close--;
    if (close>open)
    {
      paras = cmd.Mid(open + 1, close - open - 1);
      cmd = cmd.Left(open);
      return (close-open)>1;
    }
  }
  return false;
}