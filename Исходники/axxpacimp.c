extern Err vfsVolumeGetLabel(UInt16 volRefNum, Char *labelP, UInt16 bufLen)
{
    axxPacCardInfo cardinfo;
    Int32 ret;

    /* If the label was already retrieved, return it directly */
    if ( StrLen( label ) != 0 ) {
        StrNCopy( labelP, label, min( bufLen, 32 ) );
        return errNone;
    }

    ret = axxPacGetCardInfo(LibRef, &cardinfo);

    if ( ret == 0 ) {
        StrNCopy(labelP, cardinfo.vendor_name, min(bufLen, 16));
        StrNCat (labelP, cardinfo.device_name, bufLen) ;
        /* Keep the value for faster future accesses */
        StrNCat (label, labelP, min(bufLen, 32));
        return errNone;
    }
    else {
        return vfsErrVolumeBadRef;  
    }
}