static INT_PTR CALLBACK _MsgWindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  MyWinMsg *winmsg = (MyWinMsg*)LongToPtr(GetWindowLongPtr(hwnd, GWLP_USERDATA));

  if(winmsg)
  {
    switch(msg)
    {
      case WM_COPYDATA:
      {
        COPYDATASTRUCT *data = (COPYDATASTRUCT*) lparam;

        if(data && data->lpData)
        {
            const char *msg = (const char *)data->lpData;
            if ( strncmp(msg,"WinMsg",6) == 0 )
            {
                msg+=6;
                if ( strncmp(msg,"Blob",4) == 0 )
                {
                    msg+=5;
                    const char *blobType = msg;
                    while ( *msg )
                    {
                        msg++;
                    }
                    msg++;
                    const NxU32 *dlen = (const NxU32 *)msg;
                    msg+=sizeof(NxU32);
	                winmsg->queueMessageBlob(blobType,msg,dlen[0]);
                }
                else
                {
					msg++;
                    while ( *msg )
                    {
                        msg++;
                    }
                    msg++;
                    const NxU32 *dlen = (const NxU32 *)msg;
                    msg+=sizeof(NxU32);
	                winmsg->queueMessage(msg);
                }
            }
        }

        return 0;
        break;
      }
    }
  }

  return DefWindowProc(hwnd, msg, wparam, lparam);
}