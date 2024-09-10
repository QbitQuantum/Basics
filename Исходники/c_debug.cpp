Debugstr & Debugstr::operator<< (void *addr)
{
   char  szTemp[40];
   if (HIWORD(addr) == 0x0000)
      wsprintf (szTemp, "0x%04X", (ushort)LOWORD(PtrToLong(addr)));
   else
      wsprintf (szTemp, "0x%08lX", PtrToLong(addr));
   return (*this << szTemp);
}