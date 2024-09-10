int burnAPP(TCHAR *path) {
   int errorcode = 0;
   unsigned char *buf = (unsigned char *)0x80000000;
   unsigned char *buftemp = buf;
   unsigned char headbuf[512];
   unsigned int rdlen;
   APPHEADER *header = (APPHEADER * )headbuf;
   FIL file;
   FRESULT fret;
   int ret;
   char disbuf[32];
   unsigned int  percent = 0, percentold = 0;
   unsigned int  filesize, count;
   APPPACKHEAD *apppackhead = (APPPACKHEAD * )(buf + 32);
   APPSETCTION *appsection1 = &(apppackhead->appsec1);
   APPSETCTION *appsection2 = &(apppackhead->appsec2);
   fret = f_open(&file, path, FA_READ);
   if (fret != FR_OK) {
      errorcode = BURNAPP_READERROR;
      return errorcode;
   }
   filesize = file.fsize;
   if ((filesize > APP_MAX_SIZE) || (filesize <= 1024)) {
      errorcode = BURNAPP_FILE_ERROR;
      goto ERROR;
   }

   count = DIVUP(filesize, 512);
   memset(headbuf, 0, sizeof headbuf);
   statBarPrint(0, "reading");
   delay(300);
   for (int i = 0; i < count; i++, buftemp+=512) {
      fret = f_read(&file, buftemp, 512, &rdlen);
      if (fret != FR_OK)  goto ERROR;
      for (int j = 0; j < 256; j++) {
         buftemp[j] ^= ProgramTable[j];
         buftemp[j + 256] ^= ProgramTable[j];
      }
      if (i == 0) {
        /*
         if ((buftemp[0] != 'T') || (buftemp[1] != 'H') || (buftemp[2] != 'J')) {
            errorcode = BURNAPP_FILE_ERROR;
            goto ERROR;
         }
         if ((buftemp[10] != 'A') || (buftemp[11] != 'R') || (buftemp[12] != 'A')) {
            errorcode = BURNAPP_FILE_ERROR;
            goto ERROR;
         }
        */
         apppackhead = (APPPACKHEAD * )(buftemp + 32);
         appsection1 = &(apppackhead->appsec1);
         appsection2 = &(apppackhead->appsec2);
         if ((apppackhead->secflag & 0x01) &&
             ((appsection1->imageaddr + appsection1->imageSize) > (filesize - 16))) {
            errorcode = BURNAPP_FILE_ERROR;
            goto ERROR;
         }
         if ((apppackhead->secflag & 0x02) &&
             ((appsection2->imageaddr + appsection2->imageSize) > (filesize - 16))) {
            errorcode = BURNAPP_FILE_ERROR;
            goto ERROR;
         }
      } else {
         percent = i * 100 / count;
         if (percent / 5 != percentold / 5) {
            sprintf(disbuf, "%d%%", percent);
            statBarPrint(0, disbuf);
            percentold = percent;
         }
      }
   }
   MD5_CTX md5context;
   unsigned char decrypt[16];
   statBarPrint(0, "processing please waite");
   MD5Init(& md5context);
   MD5Update(& md5context, buf, filesize-16);
   MD5Final(& md5context, decrypt);
   if (memcmp(buf + filesize - 16, decrypt, 16)) {
      errorcode = BURNAPP_FILE_ERROR;
      goto ERROR;
   }
   statBarPrint(0, "write file please waite");
   delay(300);
   header->magic = APP_MAGIC_NO;
   header->secflag = apppackhead->secflag;
   if (apppackhead->secflag & 0x01) {
      header->appsec1.imageaddr = APP_BEGIN_SECTOR;
      header->appsec1.imageSize = DIVUP(appsection1->imageSize, 512);
      header->appsec1.imageRevPrefix = appsection1->imageRevPrefix;
      header->appsec1.imageMainRev = appsection1->imageMainRev;
      header->appsec1.imageMidRev = appsection1->imageMidRev;
      header->appsec1.imageMinRev = appsection1->imageMinRev;
   }
   if (apppackhead->secflag & 0x02) {
      header->appsec2.imageaddr = BAG_BEGIN_SETCTOR;
      header->appsec2.imageSize = DIVUP(appsection2->imageSize, 512);
      header->appsec2.imageRevPrefix = appsection2->imageRevPrefix;
      header->appsec2.imageMainRev = appsection2->imageMainRev;
      header->appsec2.imageMidRev = appsection2->imageMidRev;
      header->appsec2.imageMinRev = appsection2->imageMinRev;
   }
   ret = MMCSDP_Write(mmcsdctr, headbuf, APP_HEAD_SECTOR, 1);
   if (FALSE == ret) {
      errorcode = BURNAPP_WRITEERROR;
      goto ERROR;
   }
   if (apppackhead->secflag & 0x01) {
      ret = MMCSDP_Write(mmcsdctr, (void *)(buf + appsection1->imageaddr), header->appsec1.imageaddr, header->appsec1.imageSize);
      if (FALSE == ret) {
         errorcode = BURNAPP_WRITEERROR;
         goto ERROR;
      }
      header->magic = APP_MAGIC_OK;
   }
   if (apppackhead->secflag & 0x02) {
      ret = MMCSDP_Write(mmcsdctr, (void *)(buf + appsection2->imageaddr), header->appsec2.imageaddr, header->appsec2.imageSize);
      if (FALSE == ret) {
         errorcode = BURNAPP_WRITEERROR;
         goto ERROR;
      }
   }
   MMCSDP_Write(mmcsdctr, headbuf, APP_HEAD_SECTOR, 1);
   return 0;
ERROR:
   f_close(&file);
   return errorcode;
}