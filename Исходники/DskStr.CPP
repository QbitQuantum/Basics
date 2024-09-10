U8 *DirNameAbs(U8 *_dirname)
{
    I64 maxlen;
    U8 drv[3],*cur_dir,*buf2,*buf3,*buf,*dirname,*temp_name;
    if (!Fs->cur_dir || !*Fs->cur_dir)
        return StrNew(_dirname);
    dirname=MStrUtil(_dirname,
                     SUF_REM_LEADING|SUF_REM_TRAILING|SUF_REM_CTRL_CHARS);
    temp_name=dirname;
    *drv=Prt2Drv;
    drv[1]=':';
    drv[2]=0;
    if (*dirname && dirname[1]==':') {
        if (*dirname==':')
            *drv=*sys_acct;
        else
            *drv=*dirname;
        dirname=dirname+2;
        cur_dir=StrNew("/");
    } else
        cur_dir=StrNew(Fs->cur_dir);
    if (*dirname=='/') {
        Free(cur_dir);
        cur_dir=StrNew("/");
        dirname++;
    }

    buf2=StrNew(dirname);
    maxlen=StrLen(cur_dir)+1+StrLen(buf2)+1;
    buf3=MAlloc(maxlen);
    buf =MAlloc(maxlen);
    StrCpy(buf3,cur_dir);
    while (*buf2) {
        StrFirstRem(buf2,"/",buf);
        if (!*buf)
            StrCpy(buf3,"/");
        else if (!StrCmp(buf,"..")) {
            StrLastRem(buf3,"/");
            if (!*buf3)
                StrCpy(buf3,"/");
        } else if (!StrCmp(buf,".")) {
            ;
        } else if (*buf) {
            if (!StrCmp(buf,"HOME")) {
                Free(buf3);
                buf3=MAlloc(maxlen+StrLen(sys_acct));
                StrCpy(buf3,sys_acct+2);
                *drv=*sys_acct;
            } else {
                if (StrCmp(buf3,"/"))
                    StrCat(buf3,"/");
                StrCat(buf3,buf);
            }
        }
    }
    Free(cur_dir);
    cur_dir=MAlloc(StrLen(buf3)+3);
    StrCpy(cur_dir,drv);
    StrCpy(cur_dir+2,buf3);
    Free(buf);
    Free(buf2);
    Free(buf3);
    Free(temp_name);
    return cur_dir;
}