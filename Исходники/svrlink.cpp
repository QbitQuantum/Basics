int CSvrLink::SetBUError(int errcode, char *szErrMsg)
{
   unsigned char sbuf[MAXMSG];
   RP_SETERROR *pse = (RP_SETERROR *)sbuf;
   unsigned short len;
   len = strlen(szErrMsg);
   pse->iErrorCode = htonl(errcode);
   if (len>255)
      len = 255;
   Strncpy(pse->szmsg,szErrMsg,len+1);
   return(SendMsg(MT_SETERROR,sizeof(RP_SETERROR)+len,sbuf));
}