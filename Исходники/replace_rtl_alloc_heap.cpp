void ImageLoad (IMG img, void *context)
{
    fprintf (stderr, "Notified of load of %s at [%p,%p]\n",
             IMG_Name(img).c_str(),
             (char *)IMG_LowAddress(img), (char *)IMG_HighAddress(img));
    
    // See if this is ntdll.dll
    
    char szName[_MAX_FNAME];
    char szExt[_MAX_EXT];
    
    _splitpath_s (IMG_Name(img).c_str(),
                  NULL, 0,
                  NULL, 0,
                  szName, _MAX_FNAME,
                  szExt, _MAX_EXT);
    strcat_s (szName, _MAX_FNAME, szExt);
    
    if (0 != _stricmp ("ntdll.dll", szName))
        return;
    
    RTN rtn = RTN_FindByName (img, "RtlAllocateHeap");	
    
    if (RTN_Invalid() == rtn)
    {
        fprintf (stderr, "Failed to find RtlAllocateHeap in %s\n",
                 IMG_Name(img).c_str());
        return;
    }
    fprintf(stderr,"Replacing\n");
    PROTO protoRtlAllocateHeap =
        PROTO_Allocate (PIN_PARG(void *), 
                        CALLINGSTD_STDCALL, 
                        "RtlAllocateHeap", 
                        PIN_PARG(WINDOWS::PVOID), // HeapHandle
                        PIN_PARG(WINDOWS::ULONG), // Flags
                        PIN_PARG(WINDOWS::SIZE_T), // Size
                        PIN_PARG_END());
    
    
    RTN_ReplaceSignature (rtn, (AFUNPTR)replacement_RtlAllocateHeap,
                          IARG_PROTOTYPE, protoRtlAllocateHeap,
                          IARG_ORIG_FUNCPTR,
                          IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
                          IARG_FUNCARG_ENTRYPOINT_VALUE, 1,
                          IARG_FUNCARG_ENTRYPOINT_VALUE, 2,
                          IARG_CONTEXT,
                          IARG_END);
    
    
    PROTO_Free (protoRtlAllocateHeap);
}