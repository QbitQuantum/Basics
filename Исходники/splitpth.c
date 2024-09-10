int _RTLENTRY _EXPFUNC _tfnsplit(const _TCHAR *pathP, _TCHAR *driveP, _TCHAR *dirP,
                         _TCHAR *nameP, _TCHAR *extP)
{
        register _TCHAR   *pB;
        register int    Wrk;
        int     Ret;

        _TCHAR buf[ MAXPATH+2 ];

        /*
          Set all string to default value zero
        */
        Ret = 0;
        if (driveP)
                *driveP = 0;
        if (dirP)
                *dirP = 0;
        if (nameP)
                *nameP = 0;
        if (extP)
                *extP = 0;

        /*
          Copy filename into template up to MAXPATH characters
        */
        pB = buf;
        if ((Wrk = _tcslen(pathP)) > MAXPATH)
                Wrk = MAXPATH;
        *pB++ = 0;
        _tcsncpy(pB, pathP, Wrk);
        *(pB += Wrk) = 0;

        /*
          Split the filename and fill corresponding nonzero pointers
        */
        Wrk = 0;
        for (; ; ) {
#if defined(_MBCS) && !defined(_UNICODE)
                if (_mbsbtype(buf+1, (pB-1) - (buf+1)) == _MBC_TRAIL) {
                        pB -= 2;
                        continue;
                }
#endif
                switch (*--pB) {
                case _TEXT('.')  :
                        if (!Wrk && (*(pB+1) == _TEXT('\0')))
#if defined(_MBCS) && !defined(_UNICODE)
                                Wrk = DotFound(buf+1, pB);
#else
                                Wrk = DotFound(pB);
#endif
                        if ((!Wrk) && ((Ret & EXTENSION) == 0)) {
                                Ret |= EXTENSION;
                                CopyIt(extP, pB, MAXEXT - 1);
                                *pB = 0;
                        }
                        continue;
                case _TEXT(':')  :
                        if (pB != &buf[2])
                                continue;
                case _TEXT('\0') :
                        if (Wrk) {
                                if (*++pB)
                                        Ret |= DIRECTORY;
                                CopyIt(dirP, pB, MAXDIR - 1);
                                *pB-- = 0;
                                break;
                        }
                case _TEXT('/')  :
                case _TEXT('\\') :
                        if (!Wrk) {
                                Wrk++;
                                if (*++pB)
                                        Ret |= FILENAME;
                                CopyIt(nameP, pB, MAXFILE - 1);
                                *pB-- = 0;
                                if (*pB == 0 || (*pB == _TEXT(':') && pB == &buf[2]))
                                        break;
                        }
                        continue;
                case _TEXT('*')  :
                case _TEXT('?')  :
                        if (!Wrk)
                                Ret |= WILDCARDS;
                default :
                        continue;
                }
                break;
        }
        if (*pB == _TEXT(':')) {
                if (buf[1])
                        Ret |= DRIVE;
                CopyIt(driveP, &buf[1], MAXDRIVE - 1);
        }

        return (Ret);
}