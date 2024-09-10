//
// Main Program
//
int WINAPI WinMain(
  HINSTANCE Instance,
  HINSTANCE /* Previous_Instance */,
  LPSTR     Command_Line,
  int       Command_Show
  )
  {
    HWND    Frame_Window;  // Handle to the main application window.
    HWND    Client_Window; // Handle to the MDI client window (the workspace).
    MSG     Message;

    try {

      // Initialize global data as needed.
      Global::Set_Instance(Instance);
      Global::Set_CommandLine(Command_Line);
      Global::Set_CommandShow(Command_Show);

      // These strings are initialized here to be sure the "Big String Lock"
      // has been initialized before these Strings are constructed. Also for
      // the destructor (actually these strings are currently not destoryed.
      //
      Version_Number = new spica::String("1.0");
      Full_Name      = new spica::String;
      Email_Address  = new spica::String;

      Tracer(1, "NBread initializing...");

      // Read the registry to see how we are configured (or dialog with the user).
      Check_Configuration();

      string *Top_Path = spica::lookup_parameter("Noticeboard_Root");
      if (Top_Path == 0)
        throw spica::Win32::API_Error("Can't locate the noticeboard directory tree");

      // This object manages the read notice database (the "history").
      // It must be created before any topic is created because the
      // topic's constructor will reference this database. Similarly
      // this object must persist after all topics have been destroyed
      // to insure that the most up to date history file will be written
      // back to disk.
      // 
      History Read_Notices;
      History_Database = &Read_Notices;

      // This object represents the top level topic. All the subtopics
      // and notices are contained in this object. When this object is
      // destroyed all the contained objects and subobects will also be
      // destroyed.
      //
      NB_Topic Top_Level(Top_Path->c_str());
      Current_Topic = &Top_Level;

      // Set up the various window classes that we'll need.
      Set_Classes();
      InitCommonControls();

      // Create a main window and display it.
      Frame_Window = CreateWindow(
        Frame_ClassName,
        "VTC Noticeboard Reader",
        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        0,
        0,
        Instance,
        0
      );
      if (Frame_Window == 0)
        throw spica::Win32::API_Error("Can't create the frame window");

      Tracer(1, "Finished creating the MDI frame window.");
	
      // Get the MDI client window's handle.
      Client_Window = GetWindow(Frame_Window, GW_CHILD);

      ShowWindow(Frame_Window, Command_Show);
      UpdateWindow(Frame_Window);

      Tracer(1, "Entering main message dispatching loop...");

      // Get the next message from the application's message queue.
      while (GetMessage(&Message, 0, 0, 0)) {

        if (!TranslateMDISysAccel(Client_Window, &Message)) {
          TranslateMessage(&Message);
          DispatchMessage(&Message);
        }
      }

    }
    catch (spica::Win32::API_Error We) {
      spica::Win32::notifystream Error_Message;

      Error_Message << "Exception caught in WinMain\r" << We.what() << ends;
      Error_Message.say();
      return FALSE;
    }
    catch (...) {
      spica::Win32::notifystream Error_Message;

      Error_Message << "Unknown exception caught in WinMain" << ends;
      Error_Message.say();
      return FALSE;
    }

    return Message.wParam;
  }