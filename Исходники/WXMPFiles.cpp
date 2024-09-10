void WXMPFiles_SetAbortProc_1 ( XMPFilesRef   xmpFilesRef,
                         	    XMP_AbortProc abortProc,
							    void *        abortArg,
							    WXMP_Result * wResult )
{
	XMP_ENTER_WRAPPER ( "WXMPFiles_SetAbortProc_1" )
	
		XMPFiles * thiz = (XMPFiles*)xmpFilesRef;
		thiz->SetAbortProc ( abortProc, abortArg );
	
	XMP_EXIT_WRAPPER
}