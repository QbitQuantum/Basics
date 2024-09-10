hpatch_BOOL _hpatch_getPathStat_noEndDirSeparator(const char* path_utf8,hpatch_TPathType* out_type,
                                                  hpatch_StreamPos_t* out_fileSize,size_t* out_st_mode){
#if (_IS_USED_WIN32_UTF8_WAPI)
    int            wsize;
    wchar_t        path_w[hpatch_kPathMaxSize];
    struct _stat64 s;
#else
#   ifdef _MSC_VER
    struct _stat64 s;
#   else
    struct stat  s;
#   endif
#endif
    
    int          rt;
    assert(out_type!=0);
    memset(&s,0,sizeof(s));
#if (_IS_USED_WIN32_UTF8_WAPI)
    wsize=_utf8FileName_to_w(path_utf8,path_w,hpatch_kPathMaxSize);
    if (wsize<=0) return hpatch_FALSE;
    rt = _wstat64(path_w,&s);
#else
#   ifdef _MSC_VER
    rt = _stat64(path_utf8,&s);
#   else
    rt = stat(path_utf8,&s);
#   endif
#endif
    
    if(rt!=0){
        if (errno==ENOENT){
            *out_type=kPathType_notExist;
            return hpatch_TRUE;
        }
        return hpatch_FALSE; //error
    }else if ((s.st_mode&S_IFMT)==S_IFREG){
        *out_type=kPathType_file;
        if (out_fileSize) *out_fileSize=s.st_size;
        if (out_st_mode) *out_st_mode=s.st_mode;
        return hpatch_TRUE;
    }else if ((s.st_mode&S_IFMT)==S_IFDIR){
        *out_type=kPathType_dir;
        if (out_fileSize) *out_fileSize=0;
        if (out_st_mode) *out_st_mode=s.st_mode;
        return hpatch_TRUE;
    }else{
        return hpatch_FALSE; //as error; unknow how to dispose
    }
}