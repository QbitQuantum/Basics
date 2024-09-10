int main(int argc, char *argv[])
{
  PCHAR lpRootPathName;
  PCHAR requiredVolLabel;

  CHAR lpVolumeNameBuffer[MAX_PATH+1];
  CHAR lpFileSystemNameBuffer[MAX_PATH+1];
  BOOL retVal;

  if(argc < 3)
  {
    printf("usage: chkvol.exe <Root Path Name> <Required Volume Label>\n");
    printf("example: chkvol.exe C:\\ WINXP\n");
    return 1;
  }

  lpRootPathName = argv[1];
  requiredVolLabel = argv[2];

  retVal = GetVolumeInformationA(lpRootPathName,
    lpVolumeNameBuffer,
    sizeof(lpVolumeNameBuffer),
    NULL,
    NULL,
    NULL,
    lpFileSystemNameBuffer,
    sizeof(lpFileSystemNameBuffer)
    );

  if(retVal == 0)
  {
    printf("GetVolumeInformation failed with error %i\n", GetLastError());
    return 2;
  }
  else
  {
    printf("GetVolumeInformation succeeded\n");
    printf("Volume label for '%s' is '%s'\n", lpRootPathName, lpVolumeNameBuffer);
  }

  if(StrCmpIA(requiredVolLabel, lpVolumeNameBuffer) != 0 )
  {
    printf("Volume label is NOT equial to '%s'. Return code is 3\n", requiredVolLabel);
    return 3;
  }
  else
  {
    printf("Volume label is equial to '%s'. Return code is 0\n", requiredVolLabel);
    return 0;
  }
}