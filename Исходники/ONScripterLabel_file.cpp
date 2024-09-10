void ONScripterLabel::searchSaveFile( SaveFileInfo &save_file_info, int no )
{
    char file_name[256];

    bool use_fullwidth = (script_h.system_menu_script == ScriptHandler::JAPANESE_SCRIPT);
    script_h.getStringFromInteger( save_file_info.sjis_no, no,
                                  (num_save_file >= 10)?2:1,
                                  false, use_fullwidth );
#if defined(LINUX) || defined(MACOSX)
    if (script_h.savedir)
        sprintf( file_name, "%ssave%d.dat", script_h.savedir, no );
    else
        sprintf( file_name, "%ssave%d.dat", script_h.save_path, no );
    struct stat buf;
    struct tm *tm;
    if ( stat( file_name, &buf ) != 0 ){
        save_file_info.valid = false;
        return;
    }
    time_t mtime = buf.st_mtime;
    tm = localtime( &mtime );

    save_file_info.month  = tm->tm_mon + 1;
    save_file_info.day    = tm->tm_mday;
    save_file_info.hour   = tm->tm_hour;
    save_file_info.minute = tm->tm_min;
#elif defined(WIN32)
    if (script_h.savedir)
        sprintf( file_name, "%ssave%d.dat", script_h.savedir, no );
    else
        sprintf( file_name, "%ssave%d.dat", script_h.save_path, no );
    HANDLE  handle;
    FILETIME    tm, ltm;
    SYSTEMTIME  stm;

    handle = CreateFile( file_name, GENERIC_READ, 0, NULL,
                         OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
    if ( handle == INVALID_HANDLE_VALUE ){
        save_file_info.valid = false;
        return;
    }

    GetFileTime( handle, NULL, NULL, &tm );
    FileTimeToLocalFileTime( &tm, &ltm );
    FileTimeToSystemTime( &ltm, &stm );
    CloseHandle( handle );

    save_file_info.month  = stm.wMonth;
    save_file_info.day    = stm.wDay;
    save_file_info.hour   = stm.wHour;
    save_file_info.minute = stm.wMinute;
#elif defined(MACOS9)
    if (script_h.savedir)
        sprintf( file_name, "%ssave%d.dat", script_h.savedir, no );
    else
        sprintf( file_name, "%ssave%d.dat", script_h.save_path, no );
	CInfoPBRec  pb;
	Str255      p_file_name;
	FSSpec      file_spec;
	DateTimeRec tm;
	c2pstrcpy( p_file_name, file_name );
	if ( FSMakeFSSpec(0, 0, p_file_name, &file_spec) != noErr ){
		save_file_info.valid = false;
		return;
	}
	pb.hFileInfo.ioNamePtr = file_spec.name;
	pb.hFileInfo.ioVRefNum = file_spec.vRefNum;
	pb.hFileInfo.ioFDirIndex = 0;
	pb.hFileInfo.ioDirID = file_spec.parID;
	if (PBGetCatInfoSync(&pb) != noErr) {
		save_file_info.valid = false;
		return;
	}
	SecondsToDate( pb.hFileInfo.ioFlMdDat, &tm );
	save_file_info.month  = tm.month;
	save_file_info.day    = tm.day;
	save_file_info.hour   = tm.hour;
	save_file_info.minute = tm.minute;
#elif defined(PSP)
    if (script_h.savedir)
        sprintf( file_name, "%ssave%d.dat", script_h.savedir, no );
    else
        sprintf( file_name, "%ssave%d.dat", script_h.save_path, no );
    SceIoStat buf;
    if ( sceIoGetstat(file_name, &buf)<0 ){
        save_file_info.valid = false;
        return;
    }

    save_file_info.month  = buf.st_mtime.month;
    save_file_info.day    = buf.st_mtime.day;
    save_file_info.hour   = buf.st_mtime.hour;
    save_file_info.minute = buf.st_mtime.minute;
#else
    sprintf( file_name, "save%d.dat", no );
    FILE *fp;
    if ( (fp = fopen( file_name, "rb" )) == NULL ){
        save_file_info.valid = false;
        return;
    }
    fclose( fp );

    save_file_info.month  = 1;
    save_file_info.day    = 1;
    save_file_info.hour   = 0;
    save_file_info.minute = 0;
#endif
    save_file_info.valid = true;
    script_h.getStringFromInteger( save_file_info.sjis_month,
                                   save_file_info.month, 2,
                                   false, use_fullwidth );
    script_h.getStringFromInteger( save_file_info.sjis_day,
                                   save_file_info.day, 2,
                                   false, use_fullwidth );
    script_h.getStringFromInteger( save_file_info.sjis_hour,
                                   save_file_info.hour, 2,
                                   false, use_fullwidth );
    script_h.getStringFromInteger( save_file_info.sjis_minute,
                                   save_file_info.minute, 2,
                                   true, use_fullwidth );
}