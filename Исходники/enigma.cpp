int main(int argc, char **argv)
{
#ifdef MEMLEAK_CHECK
	atexit(DumpUnfreed);
#endif

#ifdef OBJECT_DEBUG
	atexit(object_dump);
#endif

	gst_init(&argc, &argv);

	// set pythonpath if unset
	setenv("PYTHONPATH", eEnv::resolve("${libdir}/enigma2/python").c_str(), 0);
	printf("PYTHONPATH: %s\n", getenv("PYTHONPATH"));
	printf("DVB_API_VERSION %d DVB_API_VERSION_MINOR %d\n", DVB_API_VERSION, DVB_API_VERSION_MINOR);

	bsodLogInit();

	ePython python;
	eMain main;

#if 1
	ePtr<gMainDC> my_dc;
	gMainDC::getInstance(my_dc);

	//int double_buffer = my_dc->haveDoubleBuffering();

	ePtr<gLCDDC> my_lcd_dc;
	gLCDDC::getInstance(my_lcd_dc);


		/* ok, this is currently hardcoded for arabic. */
			/* some characters are wrong in the regular font, force them to use the replacement font */
	for (int i = 0x60c; i <= 0x66d; ++i)
		eTextPara::forceReplacementGlyph(i);
	eTextPara::forceReplacementGlyph(0xfdf2);
	for (int i = 0xfe80; i < 0xff00; ++i)
		eTextPara::forceReplacementGlyph(i);

	eWidgetDesktop dsk(my_dc->size());
	eWidgetDesktop dsk_lcd(my_lcd_dc->size());

	dsk.setStyleID(0);
	dsk_lcd.setStyleID(my_lcd_dc->size().width() == 96 ? 2 : 1);

/*	if (double_buffer)
	{
		eDebug("[MAIN] - double buffering found, enable buffered graphics mode.");
		dsk.setCompositionMode(eWidgetDesktop::cmBuffered);
	} */

	wdsk = &dsk;
	lcddsk = &dsk_lcd;

	dsk.setDC(my_dc);
	dsk_lcd.setDC(my_lcd_dc);

	dsk.setBackgroundColor(gRGB(0,0,0,0xFF));
#endif

		/* redrawing is done in an idle-timer, so we have to set the context */
	dsk.setRedrawTask(main);
	dsk_lcd.setRedrawTask(main);

	eDebug("Checking box...");
	
	FILE *infile;
	char line[100];
	char command[64];

	if((infile = fopen("/proc/stb/info/boxtype", "r")) != NULL)
	{
		fgets(line, sizeof(line), infile);
	    
		if(strcmp(line, "ini-5000sv\n") == 0) 
		{
			eDebug("Miraclebox Premium Twin detected");
		}
		else if(strcmp(line, "ini-1000sv\n") == 0) 
		{
			eDebug("Miraclebox PremiumMini detected");
		}
		else if(strcmp(line, "ini-2000sv\n") == 0) 
		{
			eDebug("Miraclebox Premium Mini Plus detected");
		}		
		else if(strcmp(line, "ini-8000sv\n") == 0) 
		{
			eDebug("Miraclebox Premium Ultra detected");
		}
		else if(strcmp(line, "g300\n") == 0) 
		{
			eDebug("Miraclebox Premium XXXXX detected");
		}
		else if(strcmp(line, "7000S\n") == 0) 
		{
			eDebug("Miraclebox Premium Micro detected");
		}
		else
		{
			eDebug("Wrong HW, this image can be only run on Miraclbox Premium Series");
			sprintf(command, "showiframe /usr/share/enigma2/box.mvi > /dev/null");
			system(command);
			sprintf(command, "flash_erase /dev/mtd/2 0 0");
			system(command);
			sprintf(command, "flash_erase /dev/mtd/4 0 0");
			system(command);
			sprintf(command, "flash_erase /dev/mtd/3 0 0");
			system(command);
			sprintf(command, "sleep 5;reboot -f");
		}
		fclose(infile);
	}
	
	eDebug("[MAIN] Loading spinners...");

	{
		int i;
#define MAX_SPINNER 64
		ePtr<gPixmap> wait[MAX_SPINNER];
		for (i=0; i<MAX_SPINNER; ++i)
		{
			char filename[64];
			std::string rfilename;
			snprintf(filename, sizeof(filename), "${datadir}/enigma2/skin_default/spinner/wait%d.png", i + 1);
			rfilename = eEnv::resolve(filename);
			loadPNG(wait[i], rfilename.c_str());

			if (!wait[i])
			{
				if (!i)
					eDebug("[MAIN] failed to load %s: %m", rfilename.c_str());
				else
					eDebug("[MAIN] found %d spinner!\n", i);
				break;
			}
		}
		if (i)
			my_dc->setSpinner(eRect(ePoint(100, 100), wait[0]->size()), wait, i);
		else
			my_dc->setSpinner(eRect(100, 100, 0, 0), wait, 1);
	}

	gRC::getInstance()->setSpinnerDC(my_dc);

	eRCInput::getInstance()->keyEvent.connect(slot(keyEvent));

	printf("[MAIN] executing main\n");

	bsodCatchSignals();
	catchTermSignal();

	setIoPrio(IOPRIO_CLASS_BE, 3);

	/* start at full size */
	eVideoWidget::setFullsize(true);

//	python.execute("mytest", "__main__");
	python.execFile(eEnv::resolve("${libdir}/enigma2/python/mytest.py").c_str());

	/* restore both decoders to full size */
	eVideoWidget::setFullsize(true);

	if (exit_code == 5) /* python crash */
	{
		eDebug("[MAIN] (exit code 5)");
		bsodFatal(0);
	}

	dsk.paint();
	dsk_lcd.paint();

	{
		gPainter p(my_lcd_dc);
		p.resetClip(eRect(ePoint(0, 0), my_lcd_dc->size()));
		p.clear();
		p.flush();
	}

	return exit_code;
}