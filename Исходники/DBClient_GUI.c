DWORD   GUI_Listener ()
{
  BYTE          _receive_buffer [BUFFER_SIZE];
  MICROBUFFER   * p_message_received = (MICROBUFFER *) _receive_buffer;
  HWND          _requesters_list [MAX_MESSAGE_REQUESTERS];
  ULONG         _requesters_num;
  BYTE          _i;
  WORD          _gui_msg_id;
  WORD          _get_order;

  InitRequesters ();

  // non stop receiving messages loop
  for (;;)
  {
    if ( ShutdownFlag )
    {
      return DB_SUCCESS;
    }

    // Wait for message
    if ( ! ReceiveMessage (GUIAdmRouteId,
                           p_message_received,
                           BUFFER_SIZE,
                           100 ) ) 
    {
      Sleep (15);

      continue;
    }

    /*WCG. 02-02-1999 Check for different types of messages*/
    switch ( p_message_received->Command )
    {
      case GUIMSG_SESSION_CLOSE :
        /*ToDo We must find a nicer way to show this close
               session message to the user and reconnect*/
        MessageBox (GetActiveWindow(),
                    "Session Closed By DBService  Run The GUI again",
                    "Multigame System Message",
                    MB_OK | MB_ICONERROR);
      break;

      default :

//        if (   p_message_received->Command == GUIMSG_CALC_WINNDIVS
//            || p_message_received->Command == GUIMSG_CREATE_WINNINGS )
//        {
//          Beep (400, 500);
//        }

        // XID on 11-NOV-1999
        // Added loop to get several gui_msg_id from a message command.
        // Needed to handle draw progress message in provisional and definitive draws
        for (_get_order = 0; ; _get_order++)
        {
          _gui_msg_id = TranslateMsgToGUI (p_message_received->Command, _get_order);
          if (_gui_msg_id == (WORD) -1)
            break;

          _requesters_num = MAX_MESSAGE_REQUESTERS;
          GetAllRequestersByMessage (_gui_msg_id,
                                     _requesters_list,
                                     &_requesters_num);

          for ( _i = 0 ; _i < _requesters_num ; _i++ ) 
          {
            // Sends the message and waits for its processing. The we can reuse 
            // the buffer for other receives
            SendMessage (_requesters_list[_i],
                         WM_GUIMSG,
                         (WPARAM) p_message_received->ByteCount,
                         (LPARAM) p_message_received);
          }
        }
 
      break;
    }
  }

  return DB_SUCCESS;
}