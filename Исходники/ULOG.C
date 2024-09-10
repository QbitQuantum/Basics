void WriteLog(PCHAR buf, WORD len)
{
  WORD F;
  if (LogPath != NULL)
   {
    F = FOpen((PCHARFAR)&LogPath);
    if (F == 0xffff)
    {
     F = FCreate((PCHARFAR)&LogPath);
    }
    FSize(F);
    FWrite(F, (PCHARFAR)buf, len);
    FClose(F);
   }
}