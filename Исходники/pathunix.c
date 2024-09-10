DWORD ShortPathToLongPath(LPCTSTR lpszShortPath,LPTSTR lpszLongPath,DWORD
                          cchBuffer)
{
    LONG i=0;
    TCHAR path[_MAX_PATH]={0};
    TCHAR ret[_MAX_PATH]={0};
    LONG pos=0, prev_pos=0;
    LONG len=_tcslen(lpszShortPath);

    /* Is the string valid? */
    if (!lpszShortPath) {
        SetLastError(ERROR_INVALID_PARAMETER);
        return 0;
    }

    /* Is the path valid? */
    if (GetFileAttributes(lpszShortPath)==INVALID_FILE_ATTRIBUTES)
        return 0;

    /* Convert "/" to "\" */
    for (i=0;i<len;++i) {
        if (lpszShortPath[i]==_T('/'))
            path[i]=_T('\\');
        else
            path[i]=lpszShortPath[i];
    }

    /* UNC path? */
    if (path[0]==_T('\\') && path[1]==_T('\\')) {
        pos=2;
        for (i=0;i<2;++i) {
            while (path[pos]!=_T('\\') && path[pos]!=_T('\0'))
                ++pos;
            ++pos;
        }
        _tcsncpy(ret,path,pos-1);
    } /* Drive letter? */
    else if (path[1]==_T(':')) {
        if (path[2]==_T('\\'))
            pos=3;
        if (len==3) {
            if (cchBuffer>3)
                _tcscpy(lpszLongPath,lpszShortPath);
            return len;
        }
        _tcsncpy(ret,path,2);
        ret[0] = toupper(ret[0]);
    }

    /* Expand the path for each subpath, and strip trailing backslashes */
    for (prev_pos = pos-1;pos<=len;++pos) {
        if (path[pos]==_T('\\') || (path[pos]==_T('\0') &&
                                    path[pos-1]!=_T('\\'))) {
            WIN32_FIND_DATA fd;
            HANDLE hf=0;
            TCHAR c=path[pos];
            char* new_element;
            path[pos]=_T('\0');

            /* the path[prev_pos+1]... path[pos] range is the part of
               path we're handling right now. We need to find long
               name for that element and add it. */
            new_element = path + prev_pos + 1;

            /* First add separator, but only if there's something in result already. */
            if (ret[0] != _T('\0'))
            {
                _tcscat(ret,_T("\\"));
            }

            /* If it's ".." element, we need to append it, not
               the name in parent that FindFirstFile will return.
               Same goes for "." */

            if (new_element[0] == _T('.') && new_element[1] == _T('\0') ||
                new_element[0] == _T('.') && new_element[1] == _T('.')
                && new_element[2] == _T('\0'))
            {
                _tcscat(ret, new_element);
            }
            else
            {
                hf=FindFirstFile(path, &fd);
                if (hf==INVALID_HANDLE_VALUE)
                    return 0;

                _tcscat(ret,fd.cFileName);
                FindClose(hf);
            }

            path[pos]=c;

            prev_pos = pos;
        }
    }

    len=_tcslen(ret)+1;
    if (cchBuffer>=len)
        _tcscpy(lpszLongPath,ret);

    return len;
}