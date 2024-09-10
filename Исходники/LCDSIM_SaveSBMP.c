/*********************************************************************
*
*       LCDSIM_SaveSBMPEx
*/
int LCDSIM_SaveSBMPEx(const char * sFileName, int x0, int y0, int xSize, int ySize) {
  HANDLE hFile = CreateFile(sFileName, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
  if (hFile == INVALID_HANDLE_VALUE) {
    return 1;
  }
  _Serialize(x0, y0, xSize, ySize, hFile);
  if (CloseHandle(hFile) == 0) {
    return 1;
  }
  return 0;
}