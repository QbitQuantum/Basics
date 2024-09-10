  static int do_extract_currentfile( unzFile uf, const int* popt_extract_without_path, int* popt_overwrite, const char* password )
  {   	  
	char filename_inzipA[256];
	wchar_t filename_inzip[256];
    wchar_t* filename_withoutpath;
    wchar_t* p;
    int err=UNZ_OK;
	NSFile::CFileBinary oFile;
    FILE *fout=NULL;
    void* buf;
    uInt size_buf;

    unz_file_info file_info;
    uLong ratio=0;
    err = unzGetCurrentFileInfo(uf,&file_info,filename_inzipA,sizeof(filename_inzipA),NULL,0,NULL,0);

    std::wstring filenameW = codepage_issue_fixFromOEM(filename_inzipA);
	wcscpy(filename_inzip , filenameW.c_str());

    if (err!=UNZ_OK)
    {
      return err;
    }

    size_buf = WRITEBUFFERSIZE;
    buf = (void*)malloc(size_buf);
    if (buf==NULL)
    {
      return UNZ_INTERNALERROR;
    }

    p = filename_withoutpath = filename_inzip;
    while ((*p) != '\0')
    {
      if (((*p)=='/') || ((*p)=='\\'))
        filename_withoutpath = p+1;
      p++;
    }

    if ((*filename_withoutpath)=='\0')
    {
      if ((*popt_extract_without_path)==0)
      {
        mymkdir(filename_inzip);
      }
    }
    else
    {
      const wchar_t* write_filename;
      int skip=0;

      if ((*popt_extract_without_path)==0)
        write_filename = filename_inzip;
      else
        write_filename = filename_withoutpath;

      err = unzOpenCurrentFilePassword(uf,password);
      if (((*popt_overwrite)==0) && (err==UNZ_OK))
      {
        char rep=0;
		NSFile::CFileBinary oFileTemp;
		if (oFileTemp.OpenFile(write_filename))
        {
			oFileTemp.CloseFile();
        }

        if (rep == 'N')
          skip = 1;

        if (rep == 'A')
          *popt_overwrite=1;
      }

      if ((skip==0) && (err==UNZ_OK))
      {
		  if(oFile.CreateFileW(write_filename))
			 fout = oFile.GetFileNative();

        // some zipfile don't contain directory alone before file 
        if ((fout==NULL) && ((*popt_extract_without_path)==0) &&
		    (filename_withoutpath!=(wchar_t*)filename_inzip))
        {
          char c=*(filename_withoutpath-1);
          *(filename_withoutpath-1)='\0';
          makedir(write_filename);
          *(filename_withoutpath-1)=c;
		  if(oFile.CreateFileW(write_filename))
			  fout = oFile.GetFileNative();
        }
      }

      if (fout!=NULL)
      {
        do
        {
          err = unzReadCurrentFile(uf, buf, size_buf);
          if (err<0)
          {
            break;
          }
          if (err>0)
            if (fwrite(buf,err,1,fout)!=1)
            {			  
              err=UNZ_ERRNO;
              break;
            }
        }
        while (err>0);
		//close вызовется в oFile
        //if (fout)
        //  fclose(fout);

        if (err==0)
          change_file_date(write_filename,file_info.dosDate,
                           file_info.tmu_date);
      }

      if (err==UNZ_OK)
      {
        err = unzCloseCurrentFile (uf);
      }
      else
        unzCloseCurrentFile(uf); // don't lose the error 
    }

    free(buf);
    return err;
  }