// the default child constructor...
CPushPinDesktop::CPushPinDesktop(HRESULT *phr, CPushSourceDesktop *pFilter)
        : CSourceStream(NAME("Push Source CPushPinDesktop child/pin"), phr, pFilter, L"Capture"),
        m_FramesWritten(0),
		m_bReReadRegistry(0),
		m_bDeDupe(0),
        m_iFrameNumber(0),
		pOldData(NULL),
		m_bConvertToI420(false),
        //m_nCurrentBitDepth(32), // negotiated later...
		m_pParent(pFilter),
		m_bFormatAlreadySet(false),
		hRawBitmap(NULL)
{

    // Get the device context of the main display, just to get some metrics for it...
	globalStart = GetTickCount();

	m_iHwndToTrack = (HWND) read_config_setting(TEXT("hwnd_to_track"), NULL);
    hScrDc = GetDC(m_iHwndToTrack);
	m_iScreenBitDepth = GetTrueScreenDepth(hScrDc);
	ASSERT(hScrDc != 0);
	
	GdiSetBatchLimit(1); // disable any GDI...just in case this helps anybody...

    // Get the dimensions of the main desktop window as the default
    m_rScreen.left   = m_rScreen.top = 0;
    m_rScreen.right  = GetDeviceCaps(hScrDc, HORZRES); // NB this *fails* for dual monitor support currently... but we just get the wrong width by default, at least with aero windows 7 both can capture both monitors
    m_rScreen.bottom = GetDeviceCaps(hScrDc, VERTRES);

	// now read some custom settings...
	WarmupCounter();
    reReadCurrentPosition(0);

	int config_width = read_config_setting(TEXT("capture_width"), 0);
	ASSERT(config_width >= 0); // negatives not allowed...
	int config_height = read_config_setting(TEXT("capture_height"), 0);
	ASSERT(config_height >= 0); // negatives not allowed, if it's set :)

	if(config_width > 0) {
		int desired = m_rScreen.left + config_width;
		//int max_possible = m_rScreen.right; // disabled check until I get dual monitor working. or should I allow off screen captures anyway?
		//if(desired < max_possible)
			m_rScreen.right = desired;
		//else
		//	m_rScreen.right = max_possible;
	} else {
		// leave full screen
	}

	m_iCaptureConfigWidth = m_rScreen.right - m_rScreen.left;
	ASSERT(m_iCaptureConfigWidth  > 0);

	if(config_height > 0) {
		int desired = m_rScreen.top + config_height;
		//int max_possible = m_rScreen.bottom; // disabled, see above.
		//if(desired < max_possible)
			m_rScreen.bottom = desired;
		//else
		//	m_rScreen.bottom = max_possible;
	} else {
		// leave full screen
	}
	m_iCaptureConfigHeight = m_rScreen.bottom - m_rScreen.top;
	ASSERT(m_iCaptureConfigHeight > 0);	

	m_iStretchToThisConfigWidth = read_config_setting(TEXT("stretch_to_width"), 0);
	m_iStretchToThisConfigHeight = read_config_setting(TEXT("stretch_to_height"), 0);
	m_iStretchMode = read_config_setting(TEXT("stretch_mode_high_quality_if_1"), 0);
	ASSERT(m_iStretchToThisConfigWidth >= 0 && m_iStretchToThisConfigHeight >= 0 && m_iStretchMode >= 0); // sanity checks

	// default 30 fps...hmm...
	int config_max_fps = read_config_setting(TEXT("default_max_fps"), 30); // TODO allow floats [?] when ever requested
	ASSERT(config_max_fps >= 0);	

	// m_rtFrameLength is also re-negotiated later...
  	m_rtFrameLength = UNITS / config_max_fps; 

	if(is_config_set_to_1(TEXT("track_new_x_y_coords_each_frame_if_1"))) {
		m_bReReadRegistry = 1; // takes 0.416880ms, but I thought it took more when I made it off by default :P
	}
	if(is_config_set_to_1(TEXT("dedup_if_1"))) {
		m_bDeDupe = 1; // takes 10 or 20ms...but useful to me! :)
	}
	m_millisToSleepBeforePollForChanges = read_config_setting(TEXT("millis_to_sleep_between_poll_for_dedupe_changes"), 10);


    wchar_t out[1000];
	swprintf(out, 1000, L"default/from reg read config as: %dx%d -> %dx%d (%dtop %db %dl %dr) %dfps, dedupe? %d, millis between dedupe polling %d, m_bReReadRegistry? %d \n", 
	  m_iCaptureConfigHeight, m_iCaptureConfigWidth, getCaptureDesiredFinalHeight(), getCaptureDesiredFinalWidth(), m_rScreen.top, m_rScreen.bottom, m_rScreen.left, m_rScreen.right, config_max_fps, m_bDeDupe, m_millisToSleepBeforePollForChanges, m_bReReadRegistry);

	LocalOutput(out); // warmup for the below debug :)
	__int64 measureDebugOutputSpeed = StartCounter();
	LocalOutput(out);
	LocalOutput("writing a large-ish debug itself took: %.0Lf ms", GetCounterSinceStartMillis(measureDebugOutputSpeed));
	// does this work with flash?
	set_config_string_setting(L"last_init_config_was", out);
}