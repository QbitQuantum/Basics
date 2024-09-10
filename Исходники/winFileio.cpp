// [tom, 7/12/2005] Rather then converting this to unicode, just using the ANSI
// versions of the Win32 API as its quicker for testing.
bool Platform::cdFileExists(const char *filePath, const char *volumeName, S32 serialNum)
{
   if (!filePath || !filePath[0])
      return true;

   //first find the CD device...
   char fileBuf[1024];
   char drivesBuf[256];
   S32 length = GetLogicalDriveStringsA(256, drivesBuf);
   char *drivePtr = drivesBuf;
   while (S32(drivePtr - drivesBuf) < length)
   {
      char driveVolume[256], driveFileSystem[256];
      U32 driveSerial, driveFNLength, driveFlags;
      if ((dStricmp(drivePtr, "A:\\") != 0 && dStricmp(drivePtr, "B:\\") != 0) &&
          GetVolumeInformationA((const char*)drivePtr, &driveVolume[0], (unsigned long)255,
                               (unsigned long*)&driveSerial, (unsigned long*)&driveFNLength,
                               (unsigned long*)&driveFlags, &driveFileSystem[0], (unsigned long)255))
      {
#if defined (TORQUE_DEBUG) || !defined (TORQUE_SHIPPING)
         Con::printf("Found Drive: %s, vol: %s, serial: %d", drivePtr, driveVolume, driveSerial);
#endif
         //see if the volume and serial number match
         if (!dStricmp(volumeName, driveVolume) && (!serialNum || (serialNum == driveSerial)))
         {
            //see if the file exists on this volume
            if(dStrlen(drivePtr) == 3 && drivePtr[2] == '\\' && filePath[0] == '\\')
               dSprintf(fileBuf, sizeof(fileBuf), "%s%s", drivePtr, filePath + 1);
            else
               dSprintf(fileBuf, sizeof(fileBuf), "%s%s", drivePtr, filePath);
#if defined (TORQUE_DEBUG) || !defined (TORQUE_SHIPPING)
            Con::printf("Looking for file: %s on %s", fileBuf, driveVolume);
#endif
            WIN32_FIND_DATAA findData;
            HANDLE h = FindFirstFileA(fileBuf, &findData);
            if(h != INVALID_HANDLE_VALUE)
            {
               FindClose(h);
               return true;
            }
            FindClose(h);
         }
      }

      //check the next drive
      drivePtr += dStrlen(drivePtr) + 1;
   }

   return false;
}