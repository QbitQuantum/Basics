int main(int argc,char** argv)
{
 char pm, operation=-1, found=1, pw1[128], pw2[128], ae1[15], ae2[15];
 u32 i;
 PK0102 ce;
 PK0304 le;
 PK0506 ed;

 for (pm=1; pm < argc; pm++)
 {
  char opt;
  if (argv[pm][0] != '/') continue;

  if (argv[pm][1] == '?') {
   printf( "Encrypts or decrypts an archive following WinZip(R) 9 specifications.\n\n" \
"ZAES /D | /E:keysize [/2] archive.zip\n\n" \
"  /D         decrypts AES encrypted entries\n" \
"  /E:keysize encrypts with 128, 192 or 256-bit keys (keysize 1, 2 or 3)\n" \
"  /2         AE-2 format (sets CRC-32 to zero)\n");
   return 1;
  }

  opt = toupper(argv[pm][1]);
  if (opt== 'E') {
   Mode = atol(&argv[pm][3]);
   operation = 0;
   filter = encrypt_authenticate;
   if (Mode < 1 || Mode > 3)
    Z_ERROR("Bad encryption mode specified!");
   SaltSize = KS[Mode].Salt;
   KeySize = KS[Mode].Key;
   found++;
   continue;
  }

  if (opt== 'D') {
   operation = 1;
   filter = authenticate_decrypt;
   found++;
   continue;
  }

  if (opt== '2') {
   AE2 = 1;
   found++;
   printf("WARNING: according to AE-2 specifications, CRC-32 will be set to zero\n"\
"in encrypted entries. Reverting to original archive after decryption will\n"\
"be impossible with this utility!\n");
   continue;
  }
 }
 argv+=found;
 argc-=found;

 if (operation == -1) Z_ERROR("You must specify /E or /D switch!\nTry ZAES /?");
 if (argc < 1) Z_ERROR("You must give a ZIP archive to process!");

 register_prng(&sprng_desc);
 register_cipher(&aes_desc);
 register_hash(&sha1_desc);
//~ printf("DEBUG: sha1 id=%d, aes id=%d\n", find_hash("sha1"), find_cipher("aes"));

 if ( (ZIN=fopen(argv[0],"rb")) == 0 || (ZIN2=fopen(argv[0],"rb")) == 0 )
  Z_ERROR("Can't open input ZIP archive");

 if ( (ZOUT=topen(ae1)) == 0 || (ZTMP=topen(ae2)) == 0)
  Z_ERROR("Can't open temporary output files");

 setvbuf(ZIN , 0, _IOFBF, BLOCK);
 setvbuf(ZOUT, 0, _IOFBF, BLOCK);

 /* assumiamo uno ZIP senza commento! */
 fseek(ZIN2,-22,SEEK_END);
 safeRead(&ed, ZIN2, sizeof(PK0506));

 if (ed.Sig != 0x06054B50)
#ifdef HANDLE_COMMENT
 {
  fseek(ZIN2, -0xFFFF, SEEK_END);
  fread(p, 1, 4, ZIN2);
#else
  Z_ERROR("End directory marker not found!");
#endif
 /* verifica un minimo di coerenza nella ENDDIR */
 if (ed.Disk != 0)
  Z_ERROR("Can't process a spanned archive");

 while(1) {
  printf("Enter password: "******"\rFor your safety, please use a password of 8 characters or more.\n");
   continue;
  }
  if (operation) {
   printf("\n");
   break;
  }
  printf("\rVerify password: "******"Passwords don't match!\n");
   continue;
  }
  printf("\n");
  break;
 }

#define PUTN(x) { fileCopy(stdout, ZIN, x.NameLen); fseek(ZIN, -x.NameLen, SEEK_CUR); }

 fseek(ZIN2, ed.Offset, SEEK_SET);
 for (i=0; i < ed.Total; i++)
 {
   safeRead(&ce, ZIN2, sizeof(PK0102));
   if (ce.Sig != 0x02014B50)
    Z_ERROR("Expected central directory marker not found");
   /* Assume i dati corretti dalla LE */
   fseek(ZIN, ce.Offset, SEEK_SET);
   safeRead(&le, ZIN, sizeof(PK0304));
   if (le.Sig != 0x04034B50)
    Z_ERROR("Expected local entry marker not found");
   if ( ((le.Flag & 1) && !operation) || /* doesn't encrypt already encrypted */
        (!(le.Flag & 1) && operation) || /* doesn't decrypt already decrypted */
        ((le.Flag & 1) && operation && le.CompMethod != 99) || /* doesn't decrypt not AES encrypted */
        !le.CompSize )
   {
    ce.Offset = ftell(ZOUT);
    safeWrite(ZOUT, &le, sizeof(PK0304));
    printf("  copying: "); PUTN(le);
    fileCopy(ZOUT, ZIN, le.NameLen+le.ExtraLen+le.CompSize);
    printf("\n");
    safeWrite(ZTMP, &ce, sizeof(PK0102));
    fileCopy(ZTMP, ZIN2, ce.NameLen+ce.ExtraLen);
    continue;
   }
   if (!operation)
   {
    AE_EXTRA ae = {0x9901, 7, AE2+1, 0x4541, Mode, 0};
    ae.CompMethod = ce.CompMethod;
    ce.CompMethod = 99;
    if (AE2) ce.Crc32 = 0;
    ce.Flag |= 1;
    ce.ExtraLen += 11;
    ce.CompSize += SaltSize + 12; /* variable salt, fixed password check and hmac */
    ce.Offset = ftell(ZOUT);
    safeWrite(ZTMP, &ce, sizeof(PK0102));
    fileCopy(ZTMP, ZIN2, ce.NameLen+ce.ExtraLen-11);
    safeWrite(ZTMP, &ae, 11);
    printf("  encrypting: "); PUTN(le);
    Encrypt(&le, &ae, pw1);
    printf("\n");
   }
   else
   {
    ce.Offset = ftell(ZOUT);
    printf("  decrypting: "); PUTN(le);
    Decrypt(&le, pw1); /* Decrypts contents */
    printf("\n");
    ce.CompMethod = le.CompMethod;
    if (AE2) ce.Crc32 = 0;
    ce.Flag ^= 1;
    ce.ExtraLen -= 11;
    ce.CompSize = le.CompSize;
    safeWrite(ZTMP, &ce, sizeof(PK0102));
    /* Copy the extra data (may be LE != CE) */
    fileCopy(ZTMP, ZIN2, ce.NameLen);
    for(ce.ExtraLen+=11; ce.ExtraLen;)
    {
     u16 u[2];
     safeRead(u, ZIN2, 4);
     ce.ExtraLen -= (4 + u[1]);
     if (u[0] == 0x9901)
     {
      fseek(ZIN2, u[1], SEEK_CUR);
      continue;
     }
     safeWrite(ZTMP, u, 4);
     fileCopy(ZTMP, ZIN2, u[1]);
    }
   }
 }

 ed.Offset = ftell(ZOUT); /* new central directory start */
 ed.Size = ftell(ZTMP); /* new central directory size */
 fseek(ZTMP, 0, SEEK_SET);
 fclose(ZIN);
 fclose(ZIN2);
 /* Copies central directory */
 fileCopy(ZOUT, ZTMP, ed.Size);
 safeWrite(ZOUT, &ed, sizeof(PK0506));
 fclose(ZTMP);
 fclose(ZOUT);
 remove(ae2);
 if (remove(argv[0]))
 {
  printf("Can't remove old archive; new one is in file '%s'\n", ae1);
 } else
 if (rename(ae1, argv[0]))
 {
  printf("Can't rename old archive; new one is in file '%s'\n", ae1);
 }
 memset(&BUF, 0, sizeof(BUF));
 memset(&ctr, 0, sizeof(ctr));
 memset(pw1, 0, 128);
 memset(pw2, 0, 128);
 return 0;
}