    bool DirectoryInfo::RemoveDirectoryA(LPCSTR dirName,bool recursive)
    { WCHAR dirNameW[MAX_PATH];

      if( NULL!=dirName )
      { THROW_LASTERROREXCEPTION1( ::MultiByteToWideChar( CP_ACP, 0, dirName, -1,dirNameW, MAX_PATH) ); }

      return dirName!=NULL ? RemoveDirectoryW(dirNameW,recursive) : false;;
    } // of DirectoryInfo::RemoveDirectoryA()