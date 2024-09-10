   void __os2_finddata_cvt( FF_BUFFER *ffb, struct _finddata_t *fileinfo )
  #endif
 #endif
/******************************************************************************/
{
    /*** Handle the timestamps ***/
    fileinfo->time_create = _d2ttime( TODDATE( ffb->fdateCreation ),
                                        TODTIME( ffb->ftimeCreation ) );
    fileinfo->time_access = _d2ttime( TODDATE( ffb->fdateLastAccess ),
                                        TODTIME( ffb->ftimeLastAccess ) );
    fileinfo->time_write  = _d2ttime( TODDATE( ffb->fdateLastWrite ),
                                        TODTIME( ffb->ftimeLastWrite ) );

  #if defined( __INT64__ ) && !defined( _M_I86 )
    if( _FILEAPI64() ) {
  #endif
        fileinfo->attrib = ffb->attrFile;
        fileinfo->size = ffb->cbFile;
    #ifdef __WIDECHAR__
        mbstowcs( fileinfo->name, ffb->achName, _mbslen( ffb->achName ) + 1 );
    #else
        strcpy( fileinfo->name, ffb->achName );
    #endif
  #if defined( __INT64__ ) && !defined( _M_I86 )
    } else {
        fileinfo->attrib = ((FF_BUFFER_32 *)ffb)->attrFile;
        fileinfo->size = ((FF_BUFFER_32 *)ffb)->cbFile;
    #ifdef __WIDECHAR__
        mbstowcs( fileinfo->name, ((FF_BUFFER_32 *)ffb)->achName, _mbslen( ((FF_BUFFER_32 *)ffb)->achName ) + 1 );
    #else
        strcpy( fileinfo->name, ((FF_BUFFER_32 *)ffb)->achName );
    #endif
    }
  #endif
}