      /// <summary>Creates the console</summary>
      ConsoleWnd::ConsoleWnd() : Handle(nullptr)
      {
         // Create console
         if (AllocConsole())
         {
            // Get handle
            SetConsoleTitle(L"Debug Console");
            Handle = GetStdHandle(STD_OUTPUT_HANDLE);

            // Increase buffer size
            COORD buf { 200, 6*1000 };
            SetConsoleScreenBufferSize(Handle, buf);

            // Increate window size
            //SMALL_RECT wnd { 0, 0, buf.X-2, buf.Y-2};
            //SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &wnd);

            // Disable close button
            DeleteMenu(GetSystemMenu(GetConsoleWindow(), 0), SC_CLOSE, MF_BYCOMMAND);

            // Maximize
            ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);

#ifdef OFFICIAL_RELEASE
            // Initially hide
            Visible = false;
#endif
         }
      }