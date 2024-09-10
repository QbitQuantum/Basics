void shell_move_file(const std::string & source, bool unlink_source, const std::string & target) {
  if (std::string(source.begin(), source.begin() + 7) == "file://") {
    const std::string sfp(source.begin() + 7, source.end());

    wchar_t soure_buff[MAX_PATH];
    soure_buff[MultiByteToWideChar(CP_UTF8, 0, sfp.c_str(), sfp.size(), soure_buff, MAX_PATH)] = '\0';

    if (PathFileExistsW(soure_buff) == TRUE) {
      if (std::string(target.begin(), target.begin() + 7) == "file://") {
        const std::string tfp(target.begin() + 7, target.end());

        wchar_t target_buff[MAX_PATH];
        target_buff[MultiByteToWideChar(CP_UTF8, 0, tfp.c_str(), tfp.size(), target_buff, MAX_PATH)] = '\0';

        CopyFileW(soure_buff, target_buff, false);
      }

      if (unlink_source) {
        DeleteFileW(soure_buff);
      }
    }
  }
}