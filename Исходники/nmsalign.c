/*********************************************************
* writePort -
*/
int writePort( int serialPort, int smpnum )
{
  char  charbuf[20];
  char   *ptr;
  int   wbyte, stat;

  sprintf(charbuf,"%d", smpnum);
  ptr = charbuf;

  while (*ptr != '\000')
  {
     wbyte = write(serialPort, ptr, 1);
     ptr++;
     stat = readPort(serialPort, 1, 6);
     if (stat == SMPTIMEOUT) /* and read the echo back till end of text "0x03" */
     return(stat);
  }
  return (0);
}