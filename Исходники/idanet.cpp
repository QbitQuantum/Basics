/////////////////////////////////////////////////////////////////////////////////////////
//cleanup(bool warn)
//
//cancel all notifications, close the socket and destroy the hook notification window.
//
//arguments: warn true displays a warning that cleanup is being called, false no warning
//returns:   none.
//
void cleanup(bool warn) {
   //cancel all notifications. if we don't do this ida will crash on exit.
   msg(PLUGIN_NAME": cleanup called.\n");
   if (conn != INVALID_SOCKET) {
      if (msg_hwnd) {
         WSAAsyncSelect(conn, msg_hwnd, 0, 0);
         dispatch = NULL;
      }
      closesocket(conn);
      conn = INVALID_SOCKET;
      if (warn) {
         warning("Connection to collabREate server has been closed.\n"
                 "You should reconnect to the server before sending\n"
                 "additional updates.");
      }
   }
}