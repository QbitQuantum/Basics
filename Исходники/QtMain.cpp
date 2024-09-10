Q_DECL_EXPORT int main(int argc, char *argv[])
{
#ifdef Q_WS_X11
	QApplication::setAttribute(Qt::AA_X11InitThreads, true);
#endif
	QApplication a(argc, argv);
	QSize res = QApplication::desktop()->screenGeometry().size();
	if (res.width() < res.height())
		res.transpose();
	pixel_xres = res.width();
	pixel_yres = res.height();

	g_dpi_scale = CalculateDPIScale();
	dp_xres = (int)(pixel_xres * g_dpi_scale); dp_yres = (int)(pixel_yres * g_dpi_scale);
	net::Init();
#ifdef __SYMBIAN32__
	char* savegame_dir = "E:/PPSSPP/";
	char* assets_dir = "E:/PPSSPP/";
#elif defined(BLACKBERRY)
	char* savegame_dir = "/accounts/1000/shared/misc/";
	char* assets_dir = "app/native/assets/";
#elif defined(MEEGO_EDITION_HARMATTAN)
	char* savegame_dir = "/home/user/MyDocs/PPSSPP/";
	QDir myDocs("/home/user/MyDocs/");
	if (!myDocs.exists("PPSSPP"))
		myDocs.mkdir("PPSSPP");
	char* assets_dir = "/opt/PPSSPP/";
#else
	char* savegame_dir = "./";
	char* assets_dir = "./";
#endif
	NativeInit(argc, (const char **)argv, savegame_dir, assets_dir, "BADCOFFEE");

#if !defined(Q_WS_X11) || defined(ARM)
	MainUI w;
	w.resize(pixel_xres, pixel_yres);
	w.showFullScreen();
#endif
#ifdef __SYMBIAN32__
	// Set RunFast hardware mode for VFPv2.
	User::SetFloatingPointMode(EFpModeRunFast);
	// Disable screensaver
	QSystemScreenSaver *ssObject = new QSystemScreenSaver(&w);
	ssObject->setScreenSaverInhibit();
#endif

	MainAudio *audio = new MainAudio();

	int ret = a.exec();
	delete audio;
	NativeShutdown();
	net::Shutdown();
	return ret;
}