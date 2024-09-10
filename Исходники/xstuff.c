//======================================
// ScanXStuff: hw scan of StuffData
//--------------------------------------
void ScanXStuff::Scan (void) {
	MsgDetect display;
	unsigned VBEmem;
	ScanServer server(question,withx,card,cardopt);
	XF86ConfigFile srvmsg;
	map<int,ParseData>  parse;
	map<int,ServerData> graphics;
	map<int,StuffData>  stuff;
	str fbstring = "";
	int mapnr    = 0;
	int precard  = 0;
	int card     = 0;
 
	display = MonitorGetData();
	VBEmem  = MemorySize();

	srvmsg.SetFile(SERVER_STUFF_DATA);
	server.SetFile(SERVER_DATA);
	// ...
	// if no server scan data is present, scan it
	// -------------------------------------------
	if (server.Read() < 0) {
		server.Scan();
	}
	// ...
	// read the server scan data and save it
	// to graphics...
	// ---------------
	for (int i = server.Count(); i > 0; i--) {
		graphics[card] = server.Pop();
		card++;
	}
	precard = card;

	// ...
	// it is not sure to get any server message data
	// this depend on some items which you can see in the
	// server.c code. If no server message data is present
	// we had to run a server and parse the messages. If
	// there is only one card in the system we will obtain
	// the information from the libhd without starting an
	// X-Server...
	// ------------
	if ((graphics.size() == 1) && (graphics[0].module != "vmware")) {
		parse[0].dtype = display.displaytype;
		parse[0].model = display.model;
		parse[0].bus   = graphics[0].bus;
		parse[0].slot  = graphics[0].slot;
		parse[0].func  = graphics[0].func;
		parse[0].pbus  = graphics[0].bus;
		parse[0].pslot = graphics[0].slot;
		parse[0].pfunc = graphics[0].func;
		parse[0].ddc   = "<undefined>";
		if (VBEmem > 0) {
			parse[0].videoram = VBEmem;
		} else {
			parse[0].videoram = 4096;
		}
		// ...
		// the following values could not be detected via libhd
		// without starting an X-Server. Some defaults are set
		// now
		parse[0].dacspeed = 220;
		parse[0].hsmax    = 33;
		parse[0].vsmax    = 72;
		parse[0].chipset  = "<undefined>";
		parse[0].dpix     = 0;
		parse[0].dpiy     = 0;
		parse[0].vmdepth  = 0;

	} else {

		if (srvmsg.Read() < 0) {
			str config;
			sprintf(config,"%s-%d",TMP_CONFIG,getpid());
			map<int,string> section;
			ScanMouse mouse;
			ofstream handle(config);

			// open startup config...
			// -----------------------
			if (! handle) {
				cout << "ScanXStuff: could not create file: ";
				cout << TMP_CONFIG << endl;
				return;
			}
 
			// scan the mouse...
			// -------------------
			mouse.Scan(); MouseData mdata = mouse.Pop();
			srvmsg.SetMouseProperties(mdata.protocol,mdata.device);

			// create base sections...
			// ------------------------
			section[0] = srvmsg.DoFilesSection();
			section[1] = srvmsg.DoModuleSection();
			section[2] = srvmsg.DoInputDeviceSection();

			srvmsg.SetSectionID(card);
			section[3] = srvmsg.DoServerLayoutSection();

			// create dynamic sections...
			// ---------------------------
			for (int n=0;n<card;n++) {
			srvmsg.SetSectionID(n);
			if ((srvmsg.SetDriver(graphics[n].module)) == 1) {
				cout << "SaX: sorry could not open /dev/fb0... abort" << endl;
				exit(1);
			}
			srvmsg.SetBus (graphics[n].bus,graphics[n].slot,graphics[n].func);
			srvmsg.SetDeviceOption (graphics[n].option);

			section[4] = section[4] + "\n" + srvmsg.DoMonitorSection();
			section[5] = section[5] + "\n" + srvmsg.DoScreenSection();
			section[6] = section[6] + "\n" + srvmsg.DoDeviceSection();
			section[7] = section[7] + "\n" + srvmsg.DoServerFlagsSection();
			}

			// write sections to file...
			// ---------------------------
			handle << section[0] << endl;
			handle << section[1] << endl;
			handle << section[7] << endl;
			handle << section[2] << endl;
			handle << section[4] << endl;
			handle << section[5] << endl;
			handle << section[6] << endl;
			handle << section[3] << endl;

			handle.close();
			srvmsg.CallXF86Loader(config); 
			unlink(config);
		}
	}
	// ...
	// read the parse data from the XFree86 log
	// and save it to parse...
	// -------------------------
	if ((graphics.size() > 1) || (graphics[0].module == "vmware")) {
	card = 0;
	for (int i = srvmsg.Count(); i > 0; i--) {
		parse[card] = srvmsg.Pop();
		card++;
	}
	}
	if (precard > card) {
		cout << "SaX: ups lost card during probing... abort" << endl;
		exit(1);
	}
	// ...
	// lookup framebuffer timing for primary device
	// ---------------------------------------------
	ifstream handle(FB_DEV);
	FbData *fb = NULL;
	if (handle) {
		handle.close();
		fb = FbGetData();
		sprintf(fbstring,"\"%dx%d\" %.2f %s %s %s",
			fb->x,fb->y,fb->clock,fb->ht,fb->vt,fb->flags
		);
	}
	// ...
	// merge all the data. If only one card is detected
	// we will call the MonitorGetData() function to use
	// the VBE interface for getting more information 
	// via DDC[1/2]...
	// ----------------
	str current = "";
	str primary = "";
	for (int i=0;i<card;i++) {
		mapnr = FindParseData(parse,
			graphics[i].bus,graphics[i].slot,graphics[i].func
		); 
		sprintf(current,"%02d-%02d-%d",
		graphics[i].bus,graphics[i].slot,graphics[i].func);
		sprintf(primary,"%02d-%02d-%d",
		parse[mapnr].pbus,parse[mapnr].pslot,parse[mapnr].pfunc);  

		stuff[i].model = "<undefined>";
		if (parse[mapnr].model != "") {
			stuff[i].model = parse[mapnr].model;
		}
		stuff[i].vmdepth   = parse[mapnr].vmdepth;
		stuff[i].ddc       = parse[mapnr].ddc;
		stuff[i].dtype     = parse[mapnr].dtype;
		stuff[i].primary   = primary;
		stuff[i].chipset   = parse[mapnr].chipset;
		stuff[i].hsync     = parse[mapnr].hsmax; 
		stuff[i].vsync     = parse[mapnr].vsmax;
		stuff[i].dacspeed  = parse[mapnr].dacspeed;
		stuff[i].videoram  = parse[mapnr].videoram;
		stuff[i].current   = current; 
		stuff[i].raw       = graphics[i].raw;
		stuff[i].option    = graphics[i].option;
		stuff[i].extension = graphics[i].extension;
		if (TvSupport()) {
		if (stuff[i].extension == "") {
			stuff[i].extension = "v4l";
		} else {
			stuff[i].extension += ",v4l";
		}
		}
		stuff[i].driver    = graphics[i].module;
		stuff[i].dpix      = parse[mapnr].dpix;
		stuff[i].dpiy      = parse[mapnr].dpiy;

		if (
		(ddc == 1) && (
			(string(parse[i].ddc) != "<undefined>") || 
			(string(display.ddc)  != "00000000")
		)
		) {
			stuff[i].vesacount = parse[mapnr].modecount;
			stuff[i].vesa      = parse[mapnr].modes;
		} else {
			stuff[i].vesacount = -1;
			stuff[i].vesa[0].x = 640;
			stuff[i].vesa[0].y = 480;
			stuff[i].vesa[0].hsync = 25;
			stuff[i].vesa[0].vsync = 60;
		}

		// save fbtiming only for primary device...
		// -----------------------------------------
		if ((i==0) && (stuff[0].dtype == "CRT")) {
		if ((stuff[i].vesacount == -1) && (fb != NULL) && (ddc == 1)) {
			stuff[i].fbtiming  = fbstring;
			stuff[i].vesacount = 1;
			stuff[i].hsync     = (int)fb->hsync + 1;
			stuff[i].vsync     = (int)fb->vsync + 1;
			stuff[i].vesa[0].x = fb->x;
			stuff[i].vesa[0].y = fb->y;
			stuff[i].vesa[0].hsync = (int)fb->hsync;
			stuff[i].vesa[0].vsync = (int)fb->vsync;
			ddc = 0;
		} else if ((stuff[i].vesacount == -1) && (fb == NULL)) {
			stuff[i].vesacount = 1;
			stuff[i].vesa[0].x = 640;
			stuff[i].vesa[0].y = 480;
			stuff[i].vesa[0].hsync = 25;
			stuff[i].vesa[0].vsync = 60;
		}
		}
	}
	// ...
	// set the VBE DDC probed values if valid
	// --------------------------------------
	if (ddc == 1) {
	if (graphics.size() == 1) {
	if ((string(display.ddc) != "") && (string(display.ddc) != "00000000")) {
		stuff[0].ddc = display.ddc;
	}
	if (display.hsync_max > 0) { 
		stuff[0].hsync = display.hsync_max; 
	}
	if (display.vsync_max > 0) { 
		stuff[0].vsync = display.vsync_max; 
	}
	if ((display.dpix > 0) && (display.dpix < 100))     { 
		stuff[0].dpix  = display.dpix; 
	}
	if ((display.dpiy > 0) && (display.dpiy < 100))     { 
		stuff[0].dpiy  = display.dpiy; 
	}
	stuff[0].vesacount = display.vesacount;
	if (display.vesacount > 0) {
		int vesaCount = 0;
		for (int n=0;n<=display.vesacount;n++) {
		if (display.vmodes[n].x <= 1600) {
			XMode mode;
			mode.x = display.vmodes[n].x;
			mode.y = display.vmodes[n].y;
			// ...
			// check if the detected resolutions are part
			// of the following list
			// ---
			XMode vesaStandard[7];
			vesaStandard[0].x = 640;  vesaStandard[0].y = 480;
			vesaStandard[1].x = 800;  vesaStandard[1].y = 600;
			vesaStandard[2].x = 1024; vesaStandard[2].y = 768;
			vesaStandard[3].x = 1152; vesaStandard[3].y = 864;
			vesaStandard[4].x = 1280; vesaStandard[4].y = 1024;
			vesaStandard[5].x = 1400; vesaStandard[5].y = 1050;
			vesaStandard[6].x = 1600; vesaStandard[6].y = 1200;
	
			int isStandard = false;
			for (int i=0;i<7;i++) {
			if ((mode.x == vesaStandard[i].x)&&(mode.y == vesaStandard[i].y)) {
				isStandard = true;
				break;
			} 
			}
			if (! isStandard) {
				continue;
			}
			mode.hsync = display.vmodes[n].hsync;
			mode.vsync = display.vmodes[n].vsync;
			// ...
			// if mode has more than 100 Hz skip it
			// ---
			if (mode.vsync > 100) {
				continue;
			}
			// ...
			// if mode has no hsync specification, estimate it
			// from the vsync value
			// ---
			if (mode.hsync <= 0) {
				mode.hsync = (int)((mode.vsync * mode.x) / 1224);
			}
			// ...
			// if mode hsync or vsync is greater than currently
			// used max hsync/vsync, overwrite it
			// ---
			if (mode.hsync > stuff[0].hsync) {
				stuff[0].hsync = mode.hsync;
			}
			if (mode.vsync > stuff[0].vsync) {
				stuff[0].vsync = mode.vsync;
			}
			stuff[0].vesa[vesaCount] = mode;
			vesaCount++;
			stuff[0].vesacount = vesaCount;
		}
		}
	}
	}
	}
	// ...
	// save the stuff result...
	// -------------------------
	for (int i=0;i<card;i++) {
		Push(stuff[i]);
	}
}