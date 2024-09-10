DiskMuninNodePlugin::DiskMuninNodePlugin() 
{
  int i;
  for (i = 0; i < 32; i++) {
    drives[i][0] = NULL;
  }
  i = 0;
  for (int d = 'A'; d <= 'Z'; d++) {
    drives[i][0] = d;
    drives[i][1] = ':';
    drives[i][2] = NULL;//'\\';
    drives[i][3] = NULL;
    if (GetDriveTypeA(drives[i]) != DRIVE_FIXED) {
      // Remove it
      drives[i][0] = NULL;
    } else {
      i++;
    }
  }
}