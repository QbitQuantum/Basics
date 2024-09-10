void MMSFBManager::applySettings() {
	DEBUGMSG("MMSGUI", "configure graphics layer");

	// get layer settings from config
	MMSConfigDataLayer videolayer_conf = this->config.getVideoLayer();
	MMSConfigDataLayer graphicslayer_conf = this->config.getGraphicsLayer();

	// get the window pixelformat
	MMSFBSurfacePixelFormat window_pixelformat = config.getGraphicsWindowPixelformat();
	switch (window_pixelformat) {
	case MMSFB_PF_ARGB:
	case MMSFB_PF_AiRGB:
	case MMSFB_PF_AYUV:
	case MMSFB_PF_ARGB4444:
	case MMSFB_PF_RGB16:
		break;
	default:
		// window pixelformat not set or unsupported, use the layer pixelformat
		window_pixelformat = graphicslayer_conf.pixelformat;
		if (!isAlphaPixelFormat(window_pixelformat)) {
			// the gui internally needs surfaces with alpha channel
			// now we have to decide if we are working in RGB or YUV color space
			if (!isRGBPixelFormat(window_pixelformat))
				// so switch all non-alpha pixelformats to AYUV
				window_pixelformat = MMSFB_PF_AYUV;
			else
				// so switch all non-alpha pixelformats to ARGB
				window_pixelformat = MMSFB_PF_ARGB;
		}
		else
		if (isIndexedPixelFormat(window_pixelformat)) {
			// the gui internally needs non-indexed surfaces
			// so switch all indexed pixelformats to ARGB
			window_pixelformat = MMSFB_PF_ARGB;
		}
		break;
	}

	// get the surface pixelformat
	MMSFBSurfacePixelFormat surface_pixelformat = config.getGraphicsSurfacePixelformat();
	switch (surface_pixelformat) {
	case MMSFB_PF_ARGB:
	case MMSFB_PF_AiRGB:
	case MMSFB_PF_AYUV:
	case MMSFB_PF_ARGB4444:
	case MMSFB_PF_RGB16:
		break;
	default:
		// surface pixelformat not set or unsupported, use the layer pixelformat
		surface_pixelformat = graphicslayer_conf.pixelformat;
		if (!isAlphaPixelFormat(surface_pixelformat)) {
			// the gui internally needs surfaces with alpha channel
			// now we have to decide if we are working in RGB or YUV color space
			if (!isRGBPixelFormat(surface_pixelformat))
				// so switch all non-alpha pixelformats to AYUV
				surface_pixelformat = MMSFB_PF_AYUV;
			else
				// so switch all non-alpha pixelformats to ARGB
				surface_pixelformat = MMSFB_PF_ARGB;
		}
		else
		if (isIndexedPixelFormat(surface_pixelformat)) {
			// the gui internally needs non-indexed surfaces
			// so switch all indexed pixelformats to ARGB
			surface_pixelformat = MMSFB_PF_ARGB;
		}
		break;
	}

	// set exclusive access to the graphics layer
	DEBUGMSG("MMSGUI", "set exclusive access");
	if (!this->graphicslayer->setExclusiveAccess())
        throw MMSFBManagerError(0, MMSFB_LastErrorString);

	DEBUGMSG("MMSGUI", "set configuration");
    if(!this->graphicslayer->setConfiguration(graphicslayer_conf.rect.w, graphicslayer_conf.rect.h,
											   graphicslayer_conf.pixelformat,
											   graphicslayer_conf.buffermode,
											   graphicslayer_conf.options,
                                               window_pixelformat,
                                               surface_pixelformat))
        throw MMSFBManagerError(0, MMSFB_LastErrorString);

#ifdef __HAVE_XRANDR__
	if(config.getBackend() == MMSFB_BE_X11 && MMSFBBase_rotate180) {
		X11_IMPL *impl = (X11_IMPL*)this->graphicslayer->getImplementation();
		
		/* check for RandR extension */
		int event_base, error_base;
		if (!XRRQueryExtension (impl->x_display, &event_base, &error_base)) {
			fprintf(stderr, "RandR extension missing: Rotation not supported\n");
		} else {
			Window root = DefaultRootWindow(impl->x_display);
			XRRScreenConfiguration *sc = XRRGetScreenInfo(impl->x_display, root);
			if(sc) {
				Rotation rot = RR_Rotate_0;
				SizeID size = XRRConfigCurrentConfiguration(sc, &rot);
				if(rot != RR_Rotate_180) {
					XRRSetScreenConfig(impl->x_display, sc, root, size, RR_Rotate_180, CurrentTime);
				}
				MMSFBBase_rotate180 = false;
			}
		}		
	}
#endif

    if (this->videolayerid != this->graphicslayerid) {
#ifdef  __HAVE_DIRECTFB__
    	if (config.getBackend() == MMSFB_BE_X11) {
			//give a little time to window routines
			usleep(300000);
        }
#endif

        // use both layers
        DEBUGMSG("MMSGUI", "configure video layer");

        DEBUGMSG("MMSGUI", "set exclusive access");
        // set exclusive access to the video layer
        if (!this->videolayer->setExclusiveAccess())
            throw MMSFBManagerError(0, MMSFB_LastErrorString);

    	DEBUGMSG("MMSGUI", "set configuration");
        // set video layer's config
        if (!this->videolayer->setConfiguration(videolayer_conf.rect.w, videolayer_conf.rect.h,
												videolayer_conf.pixelformat,
												videolayer_conf.buffermode,
												videolayer_conf.options))
            throw MMSFBManagerError(0, MMSFB_LastErrorString);
		//this->videolayer->dfblayer->SetFieldParity(this->videolayer->dfblayer,0);

        // set the full opacity of the graphics layer
        this->graphicslayer->setOpacity(0);

        if (graphicslayer_conf.outputtype == MMSFB_OT_VIAFB) {
            // set the video layer behind the graphics layer
        	DEBUGMSG("MMSGUI", "set the video layer behind the graphics layer");
            this->videolayer->setLevel(-1);
        }
        else
        if (graphicslayer_conf.outputtype == MMSFB_OT_XSHM) {
        	DEBUGMSG("MMSGUI", "set the video layer behind the graphics layer");
            this->graphicslayer->setLevel(+1);
        }
    }

    // set global surface attributes
    string buffermode = graphicslayer_conf.buffermode;
    MMSFBSurface *gls;
    if (this->graphicslayer->getSurface(&gls, this->virtual_console)) {
    	// set the static extended accel flag
		gls->setExtendedAcceleration(config.getExtendedAccel());

		// set the global alloc method (default is malloc)
		if (mmsfb->getBackend() == MMSFB_BE_DFB) {
#ifdef  __HAVE_DIRECTFB__
			string am = config.getAllocMethod();
			if (am == "MALLOC") {
				if (!config.getExtendedAccel())
					gls->setAllocMethod(MMSFBSurfaceAllocMethod_dfb);
			}
			else
				gls->setAllocMethod(MMSFBSurfaceAllocMethod_dfb);
#endif
		}
		else
		if (graphicslayer_conf.outputtype == MMSFB_OT_OGL) {
			gls->setAllocMethod(MMSFBSurfaceAllocMethod_ogl);
		}
    }

    // init the mmsfbwindowmanager
	mmsfbwindowmanager->init(this->graphicslayer, (config.getPointer()==MMSFB_PM_TRUE));

    DEBUGMSG("MMSGUI", "creating temporary surface: %dx%d, %s", graphicslayer_conf.rect.w, graphicslayer_conf.rect.h, getMMSFBPixelFormatString(surface_pixelformat).c_str());
    mmsfbsurfacemanager->createTemporarySurface(graphicslayer_conf.rect.w, graphicslayer_conf.rect.h, surface_pixelformat, (buffermode == MMSFB_BM_BACKSYSTEM));
}