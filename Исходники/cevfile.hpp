    ///////////////////////////////////////////////////////////////////////
    // Function: GetIsTextMode
    //
    //   Author: $author$
    //     Date: 9/24/2009
    ///////////////////////////////////////////////////////////////////////
    virtual int GetIsTextMode() const 
    {
        int isTextMode = 0;

        if (INVALID_FILE == (*this).m_attached)
            return -EV_ERROR_NOT_ATTACHED;

#if defined(WIN32) 
// Windows
        int fileMode;
        errno_t err;
        if ((err = _get_fmode(&fileMode)))
            return -EV_ERROR_FAILED;
        isTextMode = (_O_TEXT == fileMode);
#else // defined(WIN32) 
// Unix
#endif // defined(WIN32)
        return isTextMode;
    }