  vl::String get_system_font_directory()
  {
#ifdef _WIN32
    char buffer[MAX_PATH];
    memset(buffer,0,sizeof(char)*MAX_PATH);
    GetWindowsDirectoryA(buffer,MAX_PATH);
    return vl::String(buffer) + "/fonts";
#else
    /* Ubuntu's Microsoft TrueType Core Fonts directory */
    return "/usr/share/fonts/truetype/msttcorefonts";
#endif
  }