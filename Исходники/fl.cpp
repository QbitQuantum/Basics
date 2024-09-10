uint64 TFile::GetSize(const TStr& FNm) {
    // open 
    HANDLE hFile = CreateFile(
       FNm.CStr(),            // file to open
       GENERIC_READ,          // open for reading
       FILE_SHARE_READ | FILE_SHARE_WRITE,       // share for reading
       NULL,                  // default security
       OPEN_EXISTING,         // existing file only
       FILE_ATTRIBUTE_NORMAL, // normal file
       NULL);                 // no attr. template
    // check if we could open it
    if (hFile == INVALID_HANDLE_VALUE) {
        TExcept::Throw("Can not open file " + FNm + "!"); }
    // read file times
    LARGE_INTEGER lpFileSizeHigh;
	if (!GetFileSizeEx(hFile, &lpFileSizeHigh)) {
        TExcept::Throw("Can not read size of file " + FNm + "!"); }
    // close file
    CloseHandle(hFile);
    // convert to uint64
	return uint64(lpFileSizeHigh.QuadPart);
}