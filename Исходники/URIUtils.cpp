bool URIUtils::IsRAR(const CStdString& strFile)
{
  CStdString strExtension = GetExtension(strFile);

  if (strExtension.Equals(".001") && strFile.Mid(strFile.length()-7,7).CompareNoCase(".ts.001"))
    return true;

  if (strExtension.CompareNoCase(".cbr") == 0)
    return true;

  if (strExtension.CompareNoCase(".rar") == 0)
    return true;

  return false;
}