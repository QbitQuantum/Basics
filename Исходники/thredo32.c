static void APIENTRY begin_thread_helper( thread_args *td )
/*********************************************************/
{
    thread_fn                   *rtn;
    void                        *arg;
    EXCEPTIONREGISTRATIONRECORD xcpt;
    thread_data                 *tdata;

    rtn = td->rtn;
    arg = td->argument;

    tdata = __alloca( __ThreadDataSize );
    memset( tdata, 0, __ThreadDataSize );
    // tdata->__allocated = 0;
    tdata->__data_size = __ThreadDataSize;
    if( !__Is_DLL ) {
        if( !__OS2AddThread( *_threadid, tdata ) ) return;
    }

    DosPostEventSem( td->event );
    _fpreset();
    __XCPTHANDLER = &xcpt;
    __sig_init_rtn();
    (*rtn)( arg );
    _endthread();
}