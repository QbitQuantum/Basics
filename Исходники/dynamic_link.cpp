 bool dynamic_link( const char*  library, const dynamic_link_descriptor descriptors[], size_t required, dynamic_link_handle*, int flags ) {
     dynamic_link_handle tmp_handle = NULL;
     TCHAR wlibrary[256];
     if ( MultiByteToWideChar(CP_UTF8, 0, library, -1, wlibrary, 255) == 0 ) return false;
     if ( flags & DYNAMIC_LINK_LOAD )
         tmp_handle = LoadPackagedLibrary( wlibrary, 0 );
     if (tmp_handle != NULL){
         return resolve_symbols(tmp_handle, descriptors, required);
     }else{
         return false;
     }
 }