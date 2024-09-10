 static std::string WIN32_GetKnownFolderPath(REFKNOWNFOLDERID rfid)
 {
     std::string path;
     wchar_t* wpath = nullptr;
     if (SUCCEEDED(SHGetKnownFolderPath(rfid, KF_FLAG_CREATE, nullptr, &wpath)))
     {
         path = String::ToUtf8(std::wstring(wpath));
     }
     CoTaskMemFree(wpath);
     return path;
 }