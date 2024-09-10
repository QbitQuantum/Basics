void bsodFatal(const char *component)
{
	/* show no more than one bsod while shutting down/crashing */
	if (bsodhandled) return;
	bsodhandled = true;

	std::string lines = getLogBuffer();

		/* find python-tracebacks, and extract "  File "-strings */
	size_t start = 0;

	std::string crash_emailaddr = CRASH_EMAILADDR;
	std::string crash_component = "enigma2";

	if (component)
		crash_component = component;
	else
	{
		while ((start = lines.find("\n  File \"", start)) != std::string::npos)
		{
			start += 9;
			size_t end = lines.find("\"", start);
			if (end == std::string::npos)
				break;
			end = lines.rfind("/", end);
				/* skip a potential prefix to the path */
			unsigned int path_prefix = lines.find("/usr/", start);
			if (path_prefix != std::string::npos && path_prefix < end)
				start = path_prefix;

			if (end == std::string::npos)
				break;

			std::string filename(lines.substr(start, end - start) + INFOFILE);
			std::ifstream in(filename.c_str());
			if (in.good()) {
				std::getline(in, crash_emailaddr) && std::getline(in, crash_component);
				in.close();
			}
		}
	}

	FILE *f;
	std::string crashlog_name;
	std::ostringstream os;
	os << "/media/hdd/enigma2_crash_";
	os << time(0);
	os << ".log";
	crashlog_name = os.str();
	f = fopen(crashlog_name.c_str(), "wb");

	if (f == NULL)
	{
		/* No hardisk. If there is a crash log in /home/root, leave it
		 * alone because we may be in a crash loop and writing this file
		 * all night long may damage the flash. Also, usually the first
		 * crash log is the most interesting one. */
		crashlog_name = "/home/root/enigma2_crash.log";
		if ((access(crashlog_name.c_str(), F_OK) == 0) ||
		    ((f = fopen(crashlog_name.c_str(), "wb")) == NULL))
		{
			/* Re-write the same file in /tmp/ because it's expected to
			 * be in RAM. So the first crash log will end up in /home
			 * and the last in /tmp */
			crashlog_name = "/tmp/enigma2_crash.log";
			f = fopen(crashlog_name.c_str(), "wb");
		}
	}

	if (f)
	{
		time_t t = time(0);
		struct tm tm;
		char tm_str[32];

		localtime_r(&t, &tm);
		strftime(tm_str, sizeof(tm_str), "%a %b %_d %T %Y", &tm);

		XmlGenerator xml(f);

		xml.open("BlakHole");

		xml.open("enigma2");
		xml.string("crashdate", tm_str);
		xml.string("compiledate", __DATE__);
		xml.string("contactemail", crash_emailaddr);
		xml.comment("Please email this crashlog to above address");

		xml.string("skin", getConfigString("config.skin.primary_skin", "Default Skin"));
		xml.string("sourcedate", enigma2_date);
		xml.string("branch", enigma2_branch);
		xml.string("rev", enigma2_rev);
		xml.string("version", PACKAGE_VERSION);
		xml.close();

		xml.open("image");
		if(access("/proc/stb/info/boxtype", F_OK) != -1) {
			xml.stringFromFile("stbmodel", "/proc/stb/info/boxtype");
		}
		else if (access("/proc/stb/info/vumodel", F_OK) != -1) {
			xml.stringFromFile("stbmodel", "/proc/stb/info/vumodel");
		}
		else if (access("/proc/stb/info/model", F_OK) != -1) {
			xml.stringFromFile("stbmodel", "/proc/stb/info/model");
		}
		xml.cDataFromCmd("kernelversion", "uname -a");
		xml.stringFromFile("kernelcmdline", "/proc/cmdline");
		xml.stringFromFile("nimsockets", "/proc/bus/nim_sockets");
		xml.cDataFromFile("imageversion", "/etc/image-version");
		xml.cDataFromFile("imageissue", "/etc/issue.net");
		xml.close();

		xml.open("crashlogs");
		xml.cDataFromString("enigma2crashlog", getLogBuffer());
		xml.close();

		xml.close();

		fclose(f);
	}

	ePtr<gMainDC> my_dc;
	gMainDC::getInstance(my_dc);

	gPainter p(my_dc);
	p.resetOffset();
	p.resetClip(eRect(ePoint(0, 0), my_dc->size()));
	p.setBackgroundColor(gRGB(0x008000));
	p.setForegroundColor(gRGB(0xFFFFFF));

	int hd =  my_dc->size().width() == 1920;
	ePtr<gFont> font = new gFont("Regular", hd ? 30 : 20);
	p.setFont(font);
	p.clear();

	eRect usable_area = eRect(hd ? 30 : 100, hd ? 30 : 70, my_dc->size().width() - (hd ? 60 : 150), hd ? 150 : 100);

	os.str("");
	os.clear();
	os << "We are really sorry. Your STB encountered "
		"a software problem, and needs to be restarted.\n"
		"Please send the logfile " << crashlog_name << " to " << crash_emailaddr << ".\n"
		"Your STB restarts in 10 seconds!\n"
		"Component: " << crash_component;

	p.renderText(usable_area, os.str().c_str(), gPainter::RT_WRAP|gPainter::RT_HALIGN_LEFT);

	usable_area = eRect(hd ? 30 : 100, hd ? 180 : 170, my_dc->size().width() - (hd ? 60 : 180), my_dc->size().height() - (hd ? 30 : 20));

	int i;

	start = std::string::npos + 1;
	for (i=0; i<20; ++i)
	{
		start = lines.rfind('\n', start - 1);
		if (start == std::string::npos)
		{
			start = 0;
			break;
		}
	}

	font = new gFont("Regular", hd ? 21 : 14);
	p.setFont(font);

	p.renderText(usable_area,
		lines.substr(start), gPainter::RT_HALIGN_LEFT);
	sleep(10);

	/*
	 * When 'component' is NULL, we are called because of a python exception.
	 * In that case, we'd prefer to to a clean shutdown of the C++ objects,
	 * and this should be safe, because the crash did not occur in the
	 * C++ part.
	 * However, when we got here for some other reason, a segfault probably,
	 * we prefer to stop immediately instead of performing a clean shutdown.
	 * We'd risk destroying things with every additional instruction we're
	 * executing here.
	 */
	if (component) raise(SIGKILL);
}