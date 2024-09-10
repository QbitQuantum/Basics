// this function is called a *lot* of times (as I learned after seeing from
// profiler output that it is called ~12000 times from Mahogany start up code!)
// so it is important to optimize it - in particular, avoid using generic
// string functions here and do everything manually because it is faster
//
// I still kept the old version to be able to check that the optimized code has
// the same output as the non optimized version.
void wxRegConfig::SetPath(const wxString& strPath)
{
    // remember the old path
    wxString strOldPath = m_strPath;

#ifdef WX_DEBUG_SET_PATH // non optimized version kept here for testing
    wxString m_strPathAlt;

    {
        wxArrayString aParts;

        // because GetPath() returns "" when we're at root, we must understand
        // empty string as "/"
        if ( strPath.IsEmpty() || (strPath[0] == wxCONFIG_PATH_SEPARATOR) ) {
            // absolute path
            wxSplitPath(aParts, strPath);
        }
        else {
            // relative path, combine with current one
            wxString strFullPath = GetPath();
            strFullPath << wxCONFIG_PATH_SEPARATOR << strPath;
            wxSplitPath(aParts, strFullPath);
        }

        // recombine path parts in one variable
        wxString strRegPath;
        m_strPathAlt.Empty();
        for ( size_t n = 0; n < aParts.Count(); n++ ) {
            strRegPath << '\\' << aParts[n];
            m_strPathAlt << wxCONFIG_PATH_SEPARATOR << aParts[n];
        }
    }
#endif // 0

    // check for the most common case first
    if ( strPath.empty() )
    {
        m_strPath = wxCONFIG_PATH_SEPARATOR;
    }
    else // not root
    {
        // construct the full path
        wxString strFullPath;
        if ( strPath[0u] == wxCONFIG_PATH_SEPARATOR )
        {
            // absolute path
            strFullPath = strPath;
        }
        else // relative path
        {
            strFullPath.reserve(2*m_strPath.length());

            strFullPath << m_strPath;
            if ( strFullPath.Len() == 0 ||
                 strFullPath.Last() != wxCONFIG_PATH_SEPARATOR )
                strFullPath << wxCONFIG_PATH_SEPARATOR;
            strFullPath << strPath;
        }

        // simplify it: we need to handle ".." here

        // count the total number of slashes we have to know if we can go upper
        size_t totalSlashes = 0;

        // position of the last slash to be able to backtrack to it quickly if
        // needed, but we set it to -1 if we don't have a valid position
        //
        // we only remember the last position which means that we handle ".."
        // quite efficiently but not "../.." - however the latter should be
        // much more rare, so it is probably ok
        int posLastSlash = -1;

        const wxChar *src = strFullPath.c_str();
        size_t len = strFullPath.length();
        const wxChar *end = src + len;

        wxStringBufferLength buf(m_strPath, len);
        wxChar *dst = buf;
        wxChar *start = dst;

        for ( ; src < end; src++, dst++ )
        {
            if ( *src == wxCONFIG_PATH_SEPARATOR )
            {
                // check for "/.."

                // note that we don't have to check for src < end here as
                // *end == 0 so can't be '.'
                if ( src[1] == _T('.') && src[2] == _T('.') &&
                     (src + 3 == end || src[3] == wxCONFIG_PATH_SEPARATOR) )
                {
                    if ( !totalSlashes )
                    {
                        wxLogWarning(_("'%s' has extra '..', ignored."),
                                     strFullPath.c_str());
                    }
                    else // return to the previous path component
                    {
                        // do we already have its position?
                        if ( posLastSlash == -1 )
                        {
                            // no, find it: note that we are sure to have one
                            // because totalSlashes > 0 so we don't have to
                            // check the boundary condition below

                            // this is more efficient than strrchr()
                            dst--;
                            while ( *dst != wxCONFIG_PATH_SEPARATOR )
                            {
                                dst--;
                            }
                        }
                        else // the position of last slash was stored
                        {
                            // go directly there
                            dst = start + posLastSlash;

                            // invalidate posLastSlash
                            posLastSlash = -1;
                        }

                        // we must have found a slash one way or another!
                        wxASSERT_MSG( *dst == wxCONFIG_PATH_SEPARATOR,
                                      _T("error in wxRegConfig::SetPath") );

                        // stay at the same position
                        dst--;

                        // we killed one
                        totalSlashes--;
                    }

                    // skip both dots
                    src += 2;
                }
                else // not "/.."
                {
                    if ( (dst == start) || (dst[-1] != wxCONFIG_PATH_SEPARATOR) )
                    {
                        *dst = wxCONFIG_PATH_SEPARATOR;

                        posLastSlash = dst - start;

                        totalSlashes++;
                    }
                    else // previous char was a slash too
                    {
                        // squeeze several subsequent slashes into one: i.e.
                        // just ignore this one
                        dst--;
                    }
                }
            }
            else // normal character
            {
                // just copy
                *dst = *src;
            }
        }

        // NUL terminate the string
        if ( dst[-1] == wxCONFIG_PATH_SEPARATOR && (dst != start + 1) )
        {
            // if it has a trailing slash we remove it unless it is the only
            // string character
            dst--;
        }

        *dst = _T('\0');
        buf.SetLength(dst - start);
    }

#ifdef WX_DEBUG_SET_PATH
    wxASSERT( m_strPath == m_strPathAlt );
#endif

    if ( m_strPath == strOldPath )
        return;

    // registry APIs want backslashes instead of slashes
    wxString strRegPath;
    if ( !m_strPath.empty() )
    {
        size_t len = m_strPath.length();

        const wxChar *src = m_strPath.c_str();
        wxStringBufferLength buf(strRegPath, len);
        wxChar *dst = buf;

        const wxChar *end = src + len;
        for ( ; src < end; src++, dst++ )
        {
            if ( *src == wxCONFIG_PATH_SEPARATOR )
                *dst = _T('\\');
            else
                *dst = *src;
        }

        buf.SetLength(len);
    }

    // this is not needed any longer as we don't create keys unnecessarily any
    // more (now it is done on demand, i.e. only when they're going to contain
    // something)
#if 0
    // as we create the registry key when SetPath(key) is done, we can be left
    // with plenty of empty keys if this was only done to try to read some
    // value which, in fact, doesn't exist - to prevent this from happening we
    // automatically delete the old key if it was empty
    if ( m_keyLocal.Exists() && LocalKey().IsEmpty() )
    {
        m_keyLocal.DeleteSelf();
    }
#endif // 0

    // change current key(s)
    m_keyLocal.SetName(m_keyLocalRoot, strRegPath);

    if ( GetStyle() & wxCONFIG_USE_GLOBAL_FILE )
    {
      m_keyGlobal.SetName(m_keyGlobalRoot, strRegPath);

      wxLogNull nolog;
      m_keyGlobal.Open(wxRegKey::Read);
    }
}