w32_thread_t w32_thread_open( uint32_t   desired_access,
                              gboolean   inherit_handle,
                              uint32_t   thread_id
                              )
{
    w32_thread_t    ret_handle;

    if ( thread_id != 0 )
        return INVALID_HANDLE_VALUE;

    /*
     * desired_access には少なくとも STANDARD_RIGHTS_REQUIRED が含まれていなければならない。
     */
    ret_handle  = OpenThread( desired_access,
                              inherit_handle,
                              thread_id
                              );
    if ( ret_handle == NULL )
        return INVALID_HANDLE_VALUE;

    return ret_handle;
}