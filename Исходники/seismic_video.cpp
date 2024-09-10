SeismicVideo::SeismicVideo(    Universe &u, int number_of_frames, int threads_high, bool init_is_parallel)
    :numberOfFrames_(number_of_frames),initIsParallel(init_is_parallel),u_(u),threadsHigh(threads_high)
{
    title = initIsParallel?titles[1]:titles[0];
#ifdef _WINDOWS
    gVideo = this;
    LoadStringA(video::win_hInstance, IDC_SEISMICSIMULATION, szWindowClass, MAX_LOADSTRING);
    memset(&wcex, 0, sizeof(wcex));
    wcex.lpfnWndProc    = (WNDPROC)WndProc;
    wcex.hIcon          = LoadIcon(video::win_hInstance, MAKEINTRESOURCE(IDI_SEISMICSIMULATION));
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = LPCTSTR(IDC_SEISMICSIMULATION);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(video::win_hInstance, MAKEINTRESOURCE(IDI_SMALL));
    win_set_class(wcex); // ascii convention here
    win_load_accelerators(IDC_SEISMICSIMULATION);
#endif

}