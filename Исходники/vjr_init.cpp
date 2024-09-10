//////////
//
// Creates the message window used for communicating actions
//
//////
	void iVjr_init_createMessageWindow(void)
	{
		ATOM			atom;
		WNDCLASSEXA		classa;


		//////////
		// Register the classes if need be
		//////
			while (1)
			{
				if (!GetClassInfoExA(ghInstance, (cs8*)cgcMessageWindowClass, &classa))
				{
					// Initialize
					memset(&classa, 0, sizeof(classa));

					// Populate
					classa.cbSize				= sizeof(WNDCLASSEXA);
					classa.hInstance			= ghInstance;
					classa.lpszClassName		= (cs8*)cgcMessageWindowClass;
					classa.lpfnWndProc			= &iWindow_wndProcMessage;

					// Register
					atom = RegisterClassExA(&classa);
					if (!atom)
						break;
				}



			//////////
			// Create the message window
			//////
				ghwndMsg = CreateWindowA((cs8*)cgcMessageWindowClass, (cs8*)cgcMessageWindowClass, 0, 0, 0, 0, 0, HWND_MESSAGE, null0, ghInstance, 0);
				if (ghwndMsg)
				{
					// Create a timer for the message window firing 20x per second
					SetTimer(ghwndMsg, 0, 50, null0);

					// Read events
					CreateThread(NULL, 0, &iReadEvents_messageWindow, 0, 0, 0);
					return;
				}
				break;
			}
			// We should never get here
			MessageBoxA(null0, "Error creating Visual FreePro Jr's message window.", "VJr - Fatal Error", MB_OK);
	}