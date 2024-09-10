void 
BL_CDEngine::SearchForCdPlayer(const char* aDirName) 
{
  BDirectory lDirectory;
  if (lDirectory.SetTo(aDirName) != B_OK) {
    return;
  }
  lDirectory.Rewind();

  BEntry lEntry;
  while(lDirectory.GetNextEntry(&lEntry) >= 0) {

    BPath lPath;
    if(lEntry.GetPath(&lPath) != B_OK) {
      continue;
    } 
    
    const char* lpName = lPath.Path();

    entry_ref lRef;
    if(lEntry.GetRef(&lRef) != B_OK) {
      continue;
    }

    if(lEntry.IsDirectory()) {

      // Ignore floppy. It's worth to explicitly check for the floppy 
      // device and ignore it, because opening it to get its geometry
      // would just make a lot of noise, and not any sense.
      if(strcmp(lRef.name, "floppy") == 0) {
        continue;
      }
      SearchForCdPlayer(lpName);
    
    } else {

      // Ignore partitions.
      if(strcmp(lRef.name, "raw") != 0) {
        continue;
      }

      // Try to open the device.
      int lDevice = open(lpName, O_RDONLY);
      if(lDevice < 0) {
        continue;
      }

      // Figure out is the device is a CD-ROM drive.
      device_geometry lGeometry;
      if(ioctl(lDevice, 
               B_GET_GEOMETRY, 
               &lGeometry, 
               sizeof(lGeometry)) < 0) {
        close(lDevice);
        continue;
      }

      // Hooray, we've found a CD-ROM drive.
      if(lGeometry.device_type == B_CD) {

        // Store the device's name in the list and close the device. 
        mpDevices->AddItem(strdup(lpName));
        close(lDevice);        
      }
    }
  }
}