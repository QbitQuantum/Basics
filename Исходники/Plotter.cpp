Error Cut(QList<QPolygonF> cuts, double mediawidth, double mediaheight, int media, int speed, int pressure, bool trackenhancing,
		  bool regmark, bool regsearch, double regwidth, double reglength)
{
	VENDOR_ID = ProgramOptions::Instance().getVendorUSB_ID();
	PRODUCT_ID = ProgramOptions::Instance().getProductUSB_ID();
	
	cout << "Cutting... VENDOR_ID : " << VENDOR_ID << " PRODUCT_ID: " << PRODUCT_ID
		 << " mediawidth: " << mediawidth << " mediaheight: " << mediaheight
		 << "media: " << media << " speed: " << speed << " pressure: " << pressure
		 << " trackenhancing: " << trackenhancing << " regmark: " <<  regmark
		 << " regsearch:" <<  regsearch <<" regwidth:" <<  regwidth << " reglength: " << reglength << endl;

	if (media < 100 || media > 300)
		media = 300;
	if (speed < 1)
		speed = 1;
	if (speed > 10)
		speed = 10;
	if (pressure < 1)
		pressure = 1;
	if (pressure > 33)
		pressure = 33;

	// how can VENDOR_ID / PRODUCT_ID report the correct values abve???
	struct cutter_id id = { "?", 0, 0 };
	libusb_device_handle* handle = UsbInit(&id);
	if (id.usb_vendor_id == VENDOR_ID_GRAPHTEC &&
	   id.usb_product_id == PRODUCT_ID_SILHOUETTE_CAMEO)
	  {
	    // should this also transform the regwidth regheigth or not?
	    cuts = Transform_Silhouette_Cameo(cuts, &mediawidth, &mediaheight);
	  }

	// TODO: Use exceptions.

	Error e = Success;
	string resp;

	// Initialise plotter.
	e = UsbSend(handle, "\x1b\x04");
	if (!e) goto error;

	// Status request.
	e = UsbSend(handle, "\x1b\x05");
	if (!e) goto error;

	e = UsbReceive(handle, resp, 5000);
	if (!e) goto error;

	if (resp != "0\x03") // 0 = Ready. 1 = Moving. 2 = Nothing loaded. "  " = ??
	{
		if (resp == "1\x03")
		  e = Error("Moving, please try again.");
		else if (resp == "2\x03")
		  e = Error("Empty tray, please load media.");	// Silhouette Cameo
		else
		  e = Error("Invalid response from plotter: " + resp);
		goto error;
	}

	// Home the cutter.
	e = UsbSend(handle, "TT\x03");
	if (!e) goto error;

	// Query version.
	e = UsbSend(handle, "FG\x03");
	if (!e) goto error;

	// Receive the firmware version.
	e = UsbReceive(handle, resp, 10000); // Large timeout because the plotter moves.
	if (!e) goto error;
	// Don't really care about this.
//	if (resp.length() != 10)
//	{
//		e = Error("Version error: " + version);
//		goto error;
//	}

	e = UsbSend(handle, "FW" + ItoS(media) + "\x03");
	if (!e) goto error;

	e = UsbSend(handle, "!" + ItoS(speed) + "\x03");
	if (!e) goto error;

	e = UsbSend(handle, "FX" + ItoS(pressure) + "\x03");
	if (!e) goto error;

	// I think this sets the distance from the position of the plotter
	// head to the actual cutting point, maybe in 0.1 mms (todo: Measure blade).
	// It is 0 for the pen, 18 for cutting.
	// C possible stands for curvature. Not that any of the other letters make sense...
	e = UsbSend(handle, "FC" + ItoS(media == 113 ? 0 : 18) + "\x03");
	if (!e) goto error;

	e = UsbSend(handle, "FY" + ItoS(trackenhancing ? 0 : 1) + "\x03");
	if (!e) goto error;

	// Set to portrait. FN1 does landscape but it's easier just to rotate the image.
	e = UsbSend(handle, "FN0\x03");
	if (!e) goto error;

	e = UsbSend(handle, "FE0\x03"); // No idea what this does.
	if (!e) goto error;

	e = UsbSend(handle, "TB71\x03"); // Again, no idea. Maybe something to do with registration marks?
	if (!e) goto error;

	e = UsbReceive(handle, resp, 10000); // Allow 10s. Seems reasonable.
	if (!e) goto error;

	if (resp != "    0,    0\x03")
	{
		e = Error("Invalid response from plotter.");
		goto error;
	}


	// Begin page definition.
	e = UsbSend(handle, "FA\x03");
	if (!e) goto error;


	// Block for all the "jump to error crosses initialization" errors. Really need to use exceptions!
	{

		// Page size: height,width in 20ths of a mm minus a margin. This is for A4. TODO: Find maximum and use that.
		stringstream page;

		int width = lroundl(mediawidth * 20.0);
		int height = lroundl(mediaheight * 20.0);

		int margintop = ProgramOptions::Instance().getMarginTop();
		int marginright = ProgramOptions::Instance().getMarginRight();

		e = UsbSend(handle, "FU" + ItoS(height - margintop) + "," + ItoS(width - marginright) + "\x03");
		if (!e) goto error;
		e = UsbSend(handle, "FM1\x03"); // ?
		if (!e) goto error;

		if (regmark)
		{
			stringstream regmarkstr;
			regmarkstr.precision(0);
			string searchregchar = "23,";
			int regw = lroundl(regwidth * 20.0);
			int regl = lroundl(reglength * 20.0);
			e = UsbSend(handle, "TB50,381\x03"); //only with registration (it was TB50,1) ???
			if (!e) goto error;
			
			if (regsearch)
				searchregchar ="123,";
			
			regmarkstr <<  "TB99\x03TB55,1\x03TB" + searchregchar + ItoS(regw) + "," + ItoS(regl) + "\x03";
			
			cout << "Registration mark string: " << regmarkstr.str() << endl;
			
			e = UsbSend(handle, regmarkstr.str()); //registration mark test /1-2: 180.0mm / 1-3: 230.0mm (origin 15mmx20mm)
			if (!e) goto error;
			
			e = UsbSend(handle, "FQ5\x03"); // only with registration ???
			if (!e) goto error; 

			e = UsbReceive(handle, resp, 40000); // Allow 20s for reply...
						if (!e) goto error;
			if (resp != "    0,    0\x03")
			{
				cout << resp << endl;
				e = Error("Couldn't find registration marks.");
				goto error;
			}
// Looks like if the reg marks work it gets 3 messages back (if it fails it times out because it only gets the first message)
			e = UsbReceive(handle, resp, 40000); // Allow 20s for reply...
			if (!e) goto error;
			if (resp != "    0\x03")
			{
				cout << resp << endl;
				e = Error("Couldn't find registration marks.");
				goto error;
			}

			e = UsbReceive(handle, resp, 40000); // Allow 20s for reply...
			if (!e) goto error;
			if (resp != "    1\x03")
			{
				cout << resp << endl;
				e = Error("Couldn't find registration marks.");
				goto error;
			}
		}
		else
		{
			e = UsbSend(handle, "TB50,1\x03"); // ???
			if (!e) goto error;
		}

		if (!e) goto error;
		// I think this is the feed command. Sometimes it is 5588 - maybe a maximum?
		e = UsbSend(handle, "FO" + ItoS(height - margintop) + "\x03");
		if (!e) goto error;

		page.flags(ios::fixed);
		page.precision(0);
		page << "&100,100,100,\\0,0,Z" << ItoS(width) << "," << ItoS(height) << ",L0";
		for (int i = 0; i < cuts.size(); ++i)
		{
			if (cuts[i].size() < 2)
				continue;

			double x = cuts[i][0].x()*20.0;
			double y = cuts[i][0].y()*20.0;

			double xorigin = ProgramOptions::Instance().getRegOriginWidthMM();
			double yorigin = ProgramOptions::Instance().getRegOriginHeightMM();

			if (regmark)
			{
				x = x - (xorigin*20.0);
				y = y + (yorigin*20.0);
			}

			// TODO: Also do this in the UI and warn the user about it.
			if (x < 0.0) x = 0.0;
			if (x > width) x = width;

			if (y < 0.0) y = 0.0;
			if (y > height) y = height;

			page << ",M" << x << "," << height-y;
			for (int j = 1; j < cuts[i].size(); ++j)
			{
				x = cuts[i][j].x()*20.0;
				y = cuts[i][j].y()*20.0;

				if (regmark)
				{
					x = x - (xorigin*20.0);
					y = y + (yorigin*20.0);
				}
				
				bool draw = true;
				if (x <= 0.0) 
				{
					x = 0.0;
					draw = false;
				}
				if (x >= width)
				{
					x = width;
					draw = false;
				}
				if (y <= 0.0)
				{ 
					y = 0.0;
					draw = false;
				}
				if (y >= height) 
				{
					y = height;
					draw = false;
				}
				
				if (draw) page << ",D" << x << "," << height-y;
				else page << ",M" << x << "," << height-y; // if outside the range just move
			}
		}


		page << "&1,1,1,TB50,0\x03"; // TB maybe .. ah I dunno. Need to experiment. No idea what &1,1,1 does either.

		// cout << page.str() << endl;

		e = UsbSend(handle, page.str());
		if (!e) goto error;
	}

	// Feed the page out.
	e = UsbSend(handle, "FO0\x03");
	if (!e) goto error;

	// Halt?
	e = UsbSend(handle, "H,");
	if (!e) goto error;


	// Don't really care about the results of these!
	libusb_release_interface(handle, 0);
	libusb_close(handle);

	return Success;

error: // Hey, this is basically C and I can't be bothered to properly C++-ify it. TODO: Use exceptions.
        cout << "Error: " << e << endl;
	libusb_release_interface(handle, 0);
	libusb_close(handle);
	return e;

}