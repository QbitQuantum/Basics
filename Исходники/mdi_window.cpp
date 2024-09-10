WPARAM mdi_window::messageLoop()
{
  MSG	msg;  
  
  bool done = false;
  while (!done)
  {     
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))	               
    {
      if (msg.message == WM_QUIT)
        done = true;					
      else							
      {
        if (!TranslateMDISysAccel(&msg))
        {
          TranslateMessage(&msg);				// Translate The Message
          DispatchMessage(&msg);				// Dispatch The Message
        }
        
        switch (msg.message)
        {
          case WM_KEYDOWN: keys[msg.wParam] =  true; break;
          case WM_KEYUP:   keys[msg.wParam] = false; break;
        }
      }
    }
  }
  
  return msg.wParam;
}