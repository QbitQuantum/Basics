void cCamCryptNagra::Signature(unsigned char *sig, const unsigned char *key, const unsigned char *msg, int len)
{
  unsigned char buff[16];
  memcpy(buff,key,16);
  for(int i=0; i<len; i+=8) {
    idea.Decrypt(msg+i,8,buff,buff,0);
    xxor(buff,8,buff,&msg[i]);
    memcpy(&buff[8],buff,8);
    }
  memcpy(sig,buff,8);
}