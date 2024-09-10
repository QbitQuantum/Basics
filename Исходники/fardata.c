int error_proc(FMSG *errmsg, ...)
{
    char *tmp_errmsg;
    va_list marker;

#if SFX_LEVEL>=ARJ
    /* Check if the message could have a standard error code */
    if(errno!=0&&is_std_error(errmsg))
    {
        msg_cprintf(0, lf);
        error_report();
    }
#endif
#if SFX_LEVEL>=ARJSFXV
    if(quiet_mode==ARJ_SILENT)
        freopen(dev_con, m_w, stdout);
#endif
#if SFX_LEVEL>=ARJ
    file_settype(stdout, ARJT_TEXT);
#endif
    /* For SFX archives, don't forget to display our logo */
#if SFX_LEVEL==ARJSFXV
    show_sfx_logo();
#elif SFX_LEVEL==ARJSFX
    if(!logo_shown)
    {
        msg_cprintf(0, M_ARJSFX_BANNER, exe_name);
        msg_cprintf(0, M_PROCESSING_ARCHIVE, archive_name);
    }
#endif
#if SFX_LEVEL>=ARJ
    nputlf();
#elif SFX_LEVEL>=ARJSFXV
    fputc(LF, new_stdout);
#else
    fputc(LF, stdout);
#endif
    /* Format and print the error message */
    va_start(marker, errmsg);
#ifdef CUSTOM_PRINTF
    vcprintf(H_ERR, errmsg, marker);
#else
    tmp_errmsg=malloc_fmsg(errmsg);
#if SFX_LEVEL>=ARJSFXV
    vfprintf(new_stdout, (FMSG *)tmp_errmsg, marker);
#else
    vprintf(tmp_errmsg, marker);
#endif
    free_fmsg(tmp_errmsg);
#endif
    va_end(marker);
#if SFX_LEVEL>=ARJ
    nputlf();
#elif SFX_LEVEL>=ARJSFXV
    fputc(LF, new_stdout);
#else
    fputc(LF, stdout);
#endif
    /* Terminate the execution with a specific errorlevel */
#if SFX_LEVEL>=ARJSFXV
    /* If there's no errorlevel yet, select errorlevel by message class */
    if(errorlevel==0)
        errorlevel=subclass_errors(errmsg);
    /* If the error was the lack of memory, display final memory statistics to
       find memory leaks */
#if SFX_LEVEL>=ARJ
    if(errorlevel==ARJ_ERL_NO_MEMORY)
        mem_stats();
#endif
    error_occured=1;
    exit(errorlevel);
#elif defined(REARJ)
    exit(REARJ_ERL_WARNING);
#elif defined(REGISTER)
    exit(REGISTER_ERL_ERROR);
#elif SFX_LEVEL>=ARJSFX
    exit(ARJSFX_ERL_ERROR);
#else
    exit(1);
#endif
    return(0);
}