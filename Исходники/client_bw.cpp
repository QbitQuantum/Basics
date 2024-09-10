  virtual int load_driver_()
  {
      SYSTEM_INFO sys_info;
      ZeroMemory(&sys_info, sizeof(sys_info));

      GetCurrentDirectory(MAX_PATH - 10, driver_filename);

      GetNativeSystemInfo(&sys_info);
      switch(sys_info.wProcessorArchitecture)
      {
          case PROCESSOR_ARCHITECTURE_AMD64:
            wcscat_s(driver_filename, MAX_PATH, L"\\winpmem_64.sys");
            if(GetFileAttributes(driver_filename) ==  INVALID_FILE_ATTRIBUTES)
            {
                std::cout << "ERROR: winpmem_64.sys not found in current directory. Download it from https://volatility.googlecode.com/svn-history/r2813/branches/scudette/tools/windows/winpmem/binaries/winpmem_64.sys ." << std::endl;
                std::cout << "ERROR: Memory bandwidth statistics will not be available." << std::endl;
            }
            break;
          case PROCESSOR_ARCHITECTURE_INTEL:
            wcscat_s(driver_filename, MAX_PATH, L"\\winpmem_32.sys");
            if(GetFileAttributes(driver_filename) ==  INVALID_FILE_ATTRIBUTES)
            {
                std::cout << "ERROR: winpmem_32.sys not found in current directory. Download it from https://volatility.googlecode.com/svn-history/r2813/branches/scudette/tools/windows/winpmem/binaries/winpmem_32.sys ." << std::endl;
                std::cout << "ERROR: Memory bandwidth statistics will not be available." << std::endl;
            }
            break;
        default:
            return -1;
      }
      return 1;
  }