int _tmain (int argc, char** argv)
	{
	
	//FreeConsole();
	//AllocConsole();
	//freopen( "CONOUT$", "wb", stdout);


	///// SETUP FILE WRITE
	
	const char* datafile = "data.txt";
	ofstream outfile;
	outfile.open (datafile);//, std::ofstream::out | std::ofstream::trunc);
	
	//// Setup bluetooth
	
	const char* portLeft = "COM9";
	const char* portRight = "COM6";
	
	HANDLE* hSerialLeft = setupBluetooth(portLeft);
	HANDLE* hSerialRight = setupBluetooth(portRight);


	char szBuff[2 + 1] = {0}; // Not sure about the second 1
	

	//////////////////////////////////////////
	
	/////////////// SETUP MIDI ////////////////
	RtMidiOut *midiout = new RtMidiOut();


	// Check available ports.
	unsigned int nPorts = midiout->getPortCount();
	if ( nPorts == 0 ) {
		std::cout << "No ports available!\n";
		//goto cleanup;
	}

	// Open first available port.
	midiout->openPort( PORT );
	
	/////////////////////////////////////
	
	
	
	SetConsoleTitle(_T("IR LEDs to GUI Integration Test - Demo"));
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	// write the title
	PrintTitle(console);

	// create a wiimote object
	wiimote remote;
	
	// in this demo we use a state-change callback to get notified of
	//  extension-related events, and polling for everything else
	// (note you don't have to use both, use whatever suits your app):
	remote.ChangedCallback		= on_state_change;
	//  notify us only when the wiimote connected sucessfully, or something
	//   related to extensions changes
	remote.CallbackTriggerFlags = (state_change_flags)(CONNECTED |
													   EXTENSION_CHANGED |
													   MOTIONPLUS_CHANGED);
reconnect:
	COORD pos = { 0, 6 };
	SetConsoleCursorPosition(console, pos);

	// try to connect the first available wiimote in the system
	//  (available means 'installed, and currently Bluetooth-connected'):
	WHITE; _tprintf(_T("  Looking for a Wiimote     "));
	   
	static const TCHAR* wait_str[] = { _T(".  "), _T(".. "), _T("...") };
	unsigned count = 0;
	while(!remote.Connect(wiimote::FIRST_AVAILABLE)) {
		_tprintf(_T("\b\b\b\b%s "), wait_str[count%3]);
		count++;
		}

	// connected - light all LEDs
	remote.SetLEDs(0x0f);
	BRIGHT_CYAN; _tprintf(_T("\b\b\b\b... connected!"));

	COORD cursor_pos = { 0, 6 };
	

	/////////////// Wiimote Variables ///////////////
	float positions [2][2];   // First array is left hand, second array is right. First element of array is x, second is y
	int quads[2]; // First element is left hand, second element is right
	
	PositionHistory* posHistoryL = setupPosHistory(1000, 30); // Left hand
	PositionHistory* posHistoryR = setupPosHistory(1000, 30); // Left hand
	
	positions[0][0] = 0.67; // These give our starting points!!!!
	positions[0][1] = 0.5; // Very important
	positions[1][0] = 0.33; // Must calibrate these
	positions[1][1] = 0.5; // Don't forget!!
	
	int writeTimerCount = 0;
	//////////////////////////////////////////////////
	
	
	// display the wiimote state data until 'Home' is pressed:
	while(!remote.Button.Home()){ // && !GetAsyncKeyState(VK_ESCAPE))
		// IMPORTANT: the wiimote state needs to be refreshed each pass
		while(remote.RefreshState() == NO_CHANGE)
			Sleep(1); // // don't hog the CPU if nothing changed

		cursor_pos.Y = 8;
		SetConsoleCursorPosition(console, cursor_pos);

		// did we loose the connection?
		if(remote.ConnectionLost()){
			BRIGHT_RED; _tprintf(
				_T("   *** connection lost! ***                                          \n")
				BLANK_LINE BLANK_LINE BLANK_LINE BLANK_LINE BLANK_LINE BLANK_LINE
				BLANK_LINE BLANK_LINE BLANK_LINE BLANK_LINE BLANK_LINE BLANK_LINE
				BLANK_LINE BLANK_LINE BLANK_LINE);
			Beep(100, 1000);
			Sleep(2000);
			COORD pos = { 0, 6 };
			SetConsoleCursorPosition(console, pos);
			_tprintf(BLANK_LINE BLANK_LINE BLANK_LINE);
			goto reconnect;
		}

		// Battery level:
		CYAN; _tprintf(_T("  Battery: "));
		// (the green/yellow colour ranges are rough guesses - my wiimote
		//  with rechargeable battery pack fails at around 15%)
		(remote.bBatteryDrained	    )? BRIGHT_RED   :
		(remote.BatteryPercent >= 30)? BRIGHT_GREEN : BRIGHT_YELLOW;
		_tprintf(_T("%3u%%   "), remote.BatteryPercent);
			
		// IR:
		CYAN ; _tprintf(_T("\n       IR:"));
		_tprintf(_T("  Mode %s  "),
			((remote.IR.Mode == wiimote_state::ir::OFF     )? _T("OFF  ") :
			 (remote.IR.Mode == wiimote_state::ir::BASIC   )? _T("BASIC") :
			 (remote.IR.Mode == wiimote_state::ir::EXTENDED)? _T("EXT. ") :
															  _T("FULL ")));
		// IR dot sizes are only reported in EXTENDED IR mode (FULL isn't supported yet)
		bool dot_sizes = (remote.IR.Mode == wiimote_state::ir::EXTENDED);

		for(unsigned index=0; index<4; index++){
			wiimote_state::ir::dot &dot = remote.IR.Dot[index];
			
			if(!remote.IsBalanceBoard()) WHITE;
			_tprintf(_T("%u: "), index);

			if(dot.bVisible) {
				WHITE; _tprintf(_T("Seen       "));
				}
			else{
				RED; _tprintf(_T("Not seen   "));
				}

			_tprintf(_T("Size"));
			if(dot_sizes)
				 _tprintf(_T("%3d "), dot.Size);
			else{
				RED; _tprintf(_T(" n/a"));
				if(dot.bVisible) WHITE;
			}

			//_tprintf(_T("  X %.3f Y %.3f\n"), 133.9*(dot.X-0.470),  88.7*(dot.Y-0.575)); // Changed stuff here!
			_tprintf(_T("  X %.3f Y %.3f\n"), dot.X, dot.Y); 
			
			if(index < 3)
				_tprintf(_T("                        "));
		}
		BRIGHT_WHITE;
			
		determineQuadrant(remote.IR.Dot, quads, positions);
		
	
		cout << quads[0] << endl;
		cout << quads[1] << endl;
		cout << "Left Hand - X = " << positions[0][0] << "   Y = " << positions[0][1] << endl;
		cout << "Right Hand - X = " << positions[1][0] << "   Y = " << positions[1][1] << endl;
		if (writeTimerCount == 3){
			outfile << positions[0][0] << " " << positions[0][1] << " " << "1" << endl; // write to file
			outfile << positions[1][0] << " " << positions[1][1] << " " << "0" << endl;
			writeTimerCount = 0;
		}
		else {
			writeTimerCount++;
		}

		
		posHistoryL->oldest_point = (posHistoryL->oldest_point + 1) % posHistoryL->size; // Move circular buffer forward
		posHistoryL->velo_point = (posHistoryL->velo_point + 1) % posHistoryL->size; // Move circular buffer forward
		
		posHistoryL->positionsX[posHistoryL->oldest_point] = positions[0][0]; // Update left hand X position
		posHistoryL->positionsY[posHistoryL->oldest_point] = positions[0][1]; // Update left hand Y position
		
		cout << (posHistoryL->positionsX[posHistoryL->oldest_point] - posHistoryL->positionsX[posHistoryL->velo_point])/posHistoryL->dis << endl; // Print left hand x velocity

		cout << posHistoryL->oldest_point << endl; // For debugging
		
		
		/// Read Bluetooth and send MIDI signals /// 	
		readBluetooth(*hSerialRight, szBuff, quads, midiout, 0);
		readBluetooth(*hSerialLeft, szBuff, quads, midiout, 40);
		
  	}

	outfile.close();
	remove (datafile);
	// disconnect (auto-happens on wiimote destruction anyway, but let's play nice)
	remote.Disconnect();
	Beep(1000, 200);

	BRIGHT_WHITE; // for automatic 'press any key to continue' msg

	
	
	
	
	/////////////////////////////
	CloseHandle(*hSerialLeft);
	CloseHandle(*hSerialRight);

	// Clean up
	//cleanup:
	//delete midiout;
	CloseHandle(console);
	//system("exit");
	
	return 0;
	}