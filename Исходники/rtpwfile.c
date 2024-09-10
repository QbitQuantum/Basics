/*----------------------------------------------------------------------*
                             rtp_wfile_rename
 *----------------------------------------------------------------------*/
int rtp_wfile_rename (unsigned short * name, unsigned short * newname)
{
#if (_WIN32_WINNT) >= 0x0400
#ifdef RTP_DEBUG
    int result;
    /* ----------------------------------- */
    /*  Clear the error state by setting   */
    /*  to 0.                              */
    /* ----------------------------------- */
    SetLastError (0);
#endif

    name    = _rtp_unicode_name_to_winname (name);
    newname = _rtp_unicode_name_to_winname (newname);

    if (_wrename ((const unsigned short *)name, (const unsigned short *)newname) != 0)
    {
#ifdef RTP_DEBUG
        result = GetLastError();
        RTP_DEBUG_OUTPUT_STR("rtp_wfile_rename: error returned ");
        RTP_DEBUG_OUTPUT_INT(result);
        RTP_DEBUG_OUTPUT_STR(".\n");
#endif
        return (-1);
    }
    return (0);
#endif
	return (-1);
}