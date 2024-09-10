AnsiString __fastcall TFTPFile::GetUserName(AnsiString ServerString)
{
  int pos = ServerString.LowerCase().Pos("ftp://");
  if(pos < 1)
    return "";
  ServerString = ServerString.SubString(pos + 6,ServerString.Length() - pos);
  pos = StrLScan(ServerString.c_str(),":");
  if(pos < 0)
    return "";
  return DecryFTPPassword(ServerString.SubString(1,pos));
}