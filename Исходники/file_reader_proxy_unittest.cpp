 TestFile() {
   wchar_t temp_dir[MAX_PATH];
   DWORD res = GetTempPathW(MAX_PATH, temp_dir);
   assert(res > 0 && res < MAX_PATH);
   wchar_t temp_file_path[MAX_PATH];
   UINT res2 = GetTempFileNameW(temp_dir, L"", 0, temp_file_path);
   assert(res2 != 0);
   file_path_ = temp_file_path;
   Write("");
 }