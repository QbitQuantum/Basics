UBOOL AfoDetectResize
    (LPAFODETECT_STR lpafoDetectStr)

{
    // If there is no more room, ...
    if (lpafoDetectStr->uLineStrCnt EQ lpafoDetectStr->uLineStrNxt)
    {
        HGLOBAL hGlbLineStr;

        // Unlock the global memory handle so we may resize it
        GlobalUnlock (lpafoDetectStr->hGlbLineStr);

        // Reallocate the AFOLINE_STR
        //   moving the old data to the new location, and
        //   freeing the old global memory
        hGlbLineStr =
          GlobalReAlloc (lpafoDetectStr->hGlbLineStr,
                          (lpafoDetectStr->uLineStrCnt + AFOLINESTR_INCR) * sizeof (AFOLINE_STR),
                          GMEM_MOVEABLE);
        // Check for error
        if (hGlbLineStr EQ NULL)
            return FALSE;

        // Save (possibly new) handle
        lpafoDetectStr->hGlbLineStr  = hGlbLineStr;
        lpafoDetectStr->lpafoLineStr = GlobalLock (hGlbLineStr);

        return TRUE;
    } else
        return TRUE;
} // End AfoDetectResize