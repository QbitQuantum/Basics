std::vector<unsigned char> CTestCaseData::LoadFile(const std::string filename)
{
  std::vector<unsigned char> vectorBuffer;
  char* pFileSamplesPath;
  size_t len = 0;
  if (_dupenv_s(&pFileSamplesPath, &len, "FileSamplesPath") || !pFileSamplesPath)
  {
	  pFileSamplesPath = TEST_DATA_PATH;
  }
  std::string fileSamplesPath(pFileSamplesPath);
  if (fileSamplesPath.size() && (*fileSamplesPath.rbegin() != '\\'))
  {
	  fileSamplesPath += L'\\';
  }
  auto file = fileSamplesPath + filename;
  if (PathFileExistsA(file.c_str()))
  {
    HANDLE hFile = CreateFileA(file.c_str(), FILE_READ_ACCESS, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (hFile != INVALID_HANDLE_VALUE)
    {
      auto fileSize = GetFileSize(hFile, NULL);
      vectorBuffer.resize(fileSize);
      DWORD dwBytesRead = 0;
      ReadFile(hFile, &vectorBuffer[0], fileSize, &dwBytesRead, NULL);
      CloseHandle(hFile);
    }
  }
  else
  {
    vectorBuffer.resize(MAX_PATH);
    GetCurrentDirectoryA(vectorBuffer.size() - 1, (LPSTR)&vectorBuffer[0]);
    std::string filePath((LPSTR)&vectorBuffer[0]);
    filePath += "\\" + file;
    const std::wstring errorMessage(L"File not found: " + CPtoUCS2(filePath, CP_ACP));
    Microsoft::VisualStudio::CppUnitTestFramework::Assert::Fail(errorMessage.c_str(), LINE_INFO());
  }
  return vectorBuffer;
}