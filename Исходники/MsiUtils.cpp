String getMsiProductCode() {
  String productGuid = kEmptyString;

  // Copy msi file from resources to the temp folder
  prepareMsiData(kEnglishLocalId);
  MSIHANDLE msiHandle;
  String path = getTmpPath() + kMsiFileName;
  // Open msi file
  UINT result = MsiOpenPackageEx(path.c_str(),
    MSIOPENPACKAGEFLAGS_IGNOREMACHINESTATE, &msiHandle);
  if (result != ERROR_SUCCESS) {
    return productGuid;
  }

  // Get Product code property string length
  DWORD length = 0;
  result = MsiGetProperty(msiHandle, _T("ProductCode"), _T(""), &length);
  if (ERROR_MORE_DATA != result) {
    return productGuid;
  }
  // Get Product code property
  // increment length for termination character
  Char* productCode = new Char[++length];
  MsiGetProperty(msiHandle, _T("ProductCode"), productCode, &length);
  productGuid = productCode;
  delete[] productCode;

  // Delete msi file from temp folder, close handles
  MsiCloseHandle(msiHandle);
  DeleteFile(path.c_str());

  return productGuid;
}