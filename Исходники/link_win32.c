static DirectResult
WaitForData( VoodooLink *link,
             int         timeout_ms )
{
     Link  *l = link->priv;
     DWORD  wait_result;

     WSAEventSelect( l->socket, l->event, FD_READ );

     wait_result = WSAWaitForMultipleEvents( 1, &l->event, FALSE, timeout_ms, FALSE );
     switch (wait_result) {
          case WSA_WAIT_EVENT_0:
               return DR_OK;

          case WSA_WAIT_TIMEOUT:
               return DR_TIMEOUT;

          default:
               D_ERROR( "Voodoo/Link: WaitForMultipleObjects() failed!\n" );
     }

     return DR_FAILURE;
}