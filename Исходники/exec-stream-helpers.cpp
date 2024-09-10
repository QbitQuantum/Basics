// wait functions
wait_result_t wait( HANDLE h, DWORD timeout )
{
    return wait_result_t( WaitForSingleObject( h, timeout ), 1, &h );
}