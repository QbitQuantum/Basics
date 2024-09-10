	SetupDisplay_Impl::SetupDisplay_Impl()
	{
		instance = this;
#if defined(WIN32) && !defined(__MINGW32__) // FIXME: Broken on MinGW (does not link)
		SetProcessDPIAware();
#endif

#if !defined __ANDROID__ && ! defined __APPLE__ && ! defined WIN32
		// The XInitThreads() function initializes Xlib support for concurrent threads.
		// This function must be the first Xlib function a multi-threaded program calls, and it must complete before any other Xlib call is made.
		XInitThreads();
#endif
		jpeg_provider = new ProviderType_Register<JPEGProvider>("jpeg");
		jpg_provider = new ProviderType_Register<JPEGProvider>("jpg");
		png_provider = new ProviderType_Register<PNGProvider>("png");
		targa_provider = new ProviderType_Register<TargaProvider>("targa");
		tga_provider = new ProviderType_Register<TargaProvider>("tga");

		FileResourceManager::add_cache_factory(std::function<void(ResourceManager &, const FileResourceDocument &)>(&SetupDisplay_Impl::add_cache_factory_file));
	}