 void message_loop()
 {
     MSG msg;
     while (GetMessage(&msg, 0, 0, 0))
     {
         DispatchMessageA(&msg);
         TranslateMessage(&msg);
     }
 }