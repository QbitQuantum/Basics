unzFile UnCompressZip::unzOpenInternal (const void *path,
                               zlib_filefunc64_32_def* pzlib_filefunc64_32_def,
                               int is64bitOpenFunction)
{
    unz64_s us;
    unz64_s *s;
    ZPOS64_T central_pos;
    uLong   uL;

    uLong number_disk;          /* number of the current dist, used for
                                   spaning ZIP, unsupported, always 0*/
    uLong number_disk_with_CD;  /* number the the disk with central dir, used
                                   for spaning ZIP, unsupported, always 0*/
    ZPOS64_T number_entry_CD;      /* total number of entries in
                                   the central dir
                                   (same than number_entry on nospan) */

    int err=UNZ_OK;

    //if (unz_copyright[0]!=' ')
        //return NULL;

    us.z_filefunc.zseek32_file = NULL;
    us.z_filefunc.ztell32_file = NULL;
    if (pzlib_filefunc64_32_def==NULL)
        fill_fopen64_filefunc(&us.z_filefunc.zfile_func64);
    else
        us.z_filefunc = *pzlib_filefunc64_32_def;
    us.is64bitOpenFunction = is64bitOpenFunction;

    us.filestream = ZOPEN64(us.z_filefunc, path, ZLIB_FILEFUNC_MODE_READ | ZLIB_FILEFUNC_MODE_EXISTING);
    if (us.filestream==NULL)
        return NULL;

    central_pos = unz64local_SearchCentralDir64(&us.z_filefunc,us.filestream);
    if (central_pos)
    {
       uLong uS;
       ZPOS64_T uL64;

       us.isZip64 = 1;

       if (ZSEEK64(us.z_filefunc, us.filestream, central_pos,ZLIB_FILEFUNC_SEEK_SET)!=0)
         err=UNZ_ERRNO;

       if (unz64local_getLong(&us.z_filefunc, us.filestream,&uL)!=UNZ_OK)
         err=UNZ_ERRNO;

        
       if (unz64local_getLong64(&us.z_filefunc, us.filestream,&uL64)!=UNZ_OK)
         err=UNZ_ERRNO;

        
       if (unz64local_getShort(&us.z_filefunc, us.filestream,&uS)!=UNZ_OK)
            err=UNZ_ERRNO;

        
        if (unz64local_getShort(&us.z_filefunc, us.filestream,&uS)!=UNZ_OK)
            err=UNZ_ERRNO;

        
        if (unz64local_getLong(&us.z_filefunc, us.filestream,&number_disk)!=UNZ_OK)
            err=UNZ_ERRNO;

       
        if (unz64local_getLong(&us.z_filefunc, us.filestream,&number_disk_with_CD)!=UNZ_OK)
            err=UNZ_ERRNO;

        
        if (unz64local_getLong64(&us.z_filefunc, us.filestream,&us.gi.number_entry)!=UNZ_OK)
            err=UNZ_ERRNO;

        
        if (unz64local_getLong64(&us.z_filefunc, us.filestream,&number_entry_CD)!=UNZ_OK)
            err=UNZ_ERRNO;

        if ((number_entry_CD!=us.gi.number_entry) ||
            (number_disk_with_CD!=0) ||
            (number_disk!=0))
            err=UNZ_BADZIPFILE;

        
        if (unz64local_getLong64(&us.z_filefunc, us.filestream,&us.size_central_dir)!=UNZ_OK)
            err=UNZ_ERRNO;

        
        if (unz64local_getLong64(&us.z_filefunc, us.filestream,&us.offset_central_dir)!=UNZ_OK)
            err=UNZ_ERRNO;

        us.gi.size_comment = 0;
    }
    else
    {
        central_pos = unz64local_SearchCentralDir(&us.z_filefunc,us.filestream);
        if (central_pos==0)
            err=UNZ_ERRNO;

        us.isZip64 = 0;

        if (ZSEEK64(us.z_filefunc, us.filestream,
                                        central_pos,ZLIB_FILEFUNC_SEEK_SET)!=0)
            err=UNZ_ERRNO;

        
        if (unz64local_getLong(&us.z_filefunc, us.filestream,&uL)!=UNZ_OK)
            err=UNZ_ERRNO;

       
        if (unz64local_getShort(&us.z_filefunc, us.filestream,&number_disk)!=UNZ_OK)
            err=UNZ_ERRNO;

        
        if (unz64local_getShort(&us.z_filefunc, us.filestream,&number_disk_with_CD)!=UNZ_OK)
            err=UNZ_ERRNO;

        
        if (unz64local_getShort(&us.z_filefunc, us.filestream,&uL)!=UNZ_OK)
            err=UNZ_ERRNO;
        us.gi.number_entry = uL;

       
        if (unz64local_getShort(&us.z_filefunc, us.filestream,&uL)!=UNZ_OK)
            err=UNZ_ERRNO;
        number_entry_CD = uL;

        if ((number_entry_CD!=us.gi.number_entry) ||
            (number_disk_with_CD!=0) ||
            (number_disk!=0))
            err=UNZ_BADZIPFILE;

     
        if (unz64local_getLong(&us.z_filefunc, us.filestream,&uL)!=UNZ_OK)
            err=UNZ_ERRNO;
        us.size_central_dir = uL;

        if (unz64local_getLong(&us.z_filefunc, us.filestream,&uL)!=UNZ_OK)
            err=UNZ_ERRNO;
        us.offset_central_dir = uL;


        if (unz64local_getShort(&us.z_filefunc, us.filestream,&us.gi.size_comment)!=UNZ_OK)
            err=UNZ_ERRNO;
    }

    if ((central_pos<us.offset_central_dir+us.size_central_dir) &&
        (err==UNZ_OK))
        err=UNZ_BADZIPFILE;

    if (err!=UNZ_OK)
    {
        ZCLOSE64(us.z_filefunc, us.filestream);
        return NULL;
    }

    us.byte_before_the_zipfile = central_pos - (us.offset_central_dir+us.size_central_dir);
    us.central_pos = central_pos;
    us.pfile_in_zip_read = NULL;
    us.encrypted = 0;

    s=(unz64_s*)ALLOC(sizeof(unz64_s));
    if( s != NULL)
    {
        *s=us;
        Bytef buf[UNZ_BUFSIZE];
        char  name[100];
        if (unzGoToFirstFile((unzFile)s) != UNZ_OK)
          return (unzFile)UNZ_ERRNO;
        ::CreateDirectory(m_uncompresspath.GetBuffer(MAX_PATH), NULL);
        m_uncompresspath.ReleaseBuffer();
        do 
        {
          
          unzOpenCurrentFile((unzFile)s);
          uInt filelength = unzReadCurrentFile((unzFile)s, buf, UNZ_BUFSIZE);
          unz64local_GetCurrentFileInfoInternal((unzFile)s, &s->cur_file_info,
             &s->cur_file_info_internal, name,100,NULL,0,NULL,0);

          std::wstring path = m_uncompresspath.GetString();
          path += L"\\";
          std::wstring filename = Strings::StringToWString(name);
          path += filename;

          HANDLE hfile = CreateFile(path.c_str(), GENERIC_WRITE, 0, 0, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, 0);
          CloseHandle(hfile);

          FILE* file;
          _wfopen_s(&file, path.c_str(), L"wb");
          fwrite(buf, 1, filelength, file);
          fclose(file);
        }
        while(unzGoToNextFile((unzFile)s) == UNZ_OK);
       
        unzClose((unzFile)s);
    }
    return (unzFile)s;
}