static void opal_process_handle_destruct( opal_object_t* obj )
{
    opal_process_handle_t* handle = (opal_process_handle_t*)obj;

    if( INVALID_HANDLE_VALUE != handle->registered_handle ) {
        if( 0 == UnregisterWait( handle->registered_handle ) ) {
            int error = GetLastError();
        }
        if( 0 == CloseHandle( handle->registered_handle ) ) {
            int error = GetLastError();
        }
        handle->registered_handle = INVALID_HANDLE_VALUE;
    }
}