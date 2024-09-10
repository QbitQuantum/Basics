// Default constructor
LLFloaterAbout::LLFloaterAbout()
    :	LLFloater(std::string("floater_about"), std::string("FloaterAboutRect"), LLStringUtil::null)
{
    LLUICtrlFactory::getInstance()->buildFloater(this, "floater_about.xml");

    // Support for changing product name.
    std::string title("About ");
    title += LLAppViewer::instance()->getSecondLifeTitle();
    setTitle(title);

    LLViewerTextEditor *support_widget =
        getChild<LLViewerTextEditor>("support_editor", true);

    LLViewerTextEditor *credits_widget =
        getChild<LLViewerTextEditor>("credits_editor", true);


    if (!support_widget || !credits_widget)
    {
        return;
    }

    // For some reason, adding style doesn't work unless this is true.
    support_widget->setParseHTML(TRUE);

    // Text styles for release notes hyperlinks
    LLStyleSP viewer_link_style(new LLStyle);
    viewer_link_style->setVisible(true);
    viewer_link_style->setFontName(LLStringUtil::null);
    viewer_link_style->setLinkHREF(get_viewer_release_notes_url());
    viewer_link_style->setColor(gSavedSettings.getColor4("HTMLLinkColor"));

    // Version string
    std::string version = llformat(
                              "%s %d.%d.%d %s / %s %d.%d.%d (%d), %s %s\n",
                              IMP_VIEWER_NAME,
                              IMP_VERSION_MAJOR, IMP_VERSION_MINOR, IMP_VERSION_PATCH, IMP_VERSION_TEST,
                              LL_VIEWER_NAME,
                              LL_VERSION_MAJOR, LL_VERSION_MINOR, LL_VERSION_PATCH, LL_VIEWER_BUILD,
                              __DATE__, __TIME__);

    support_widget->appendColoredText(version, FALSE, FALSE, gColors.getColor("TextFgReadOnlyColor"));
    support_widget->appendStyledText(LLTrans::getString("ReleaseNotes"), false, false, viewer_link_style);

    std::string support;
    support.append("\n\n");

#if LL_MSVC
    support.append(llformat("Built with MSVC version %d\n\n", _MSC_VER));
#endif

#if LL_GNUC
    support.append(llformat("Built with GCC version %d\n\n", GCC_VERSION));
#endif

    // Position
    LLViewerRegion* region = gAgent.getRegion();
// [RLVa:KB] - Version: 1.22.11 | Checked: 2009-07-04 (RLVa-1.0.0a)
    if (gRlvHandler.hasBehaviour(RLV_BHVR_SHOWLOC))
    {
        support.append(rlv_handler_t::cstrHidden);
        support.append("\n\n");
    }
    else if (region)
// [/RLVa:KB]
//	if (region)
    {
        LLStyleSP server_link_style(new LLStyle);
        server_link_style->setVisible(true);
        server_link_style->setFontName(LLStringUtil::null);
        server_link_style->setLinkHREF(region->getCapability("ServerReleaseNotes"));
        server_link_style->setColor(gSavedSettings.getColor4("HTMLLinkColor"));

        const LLVector3d &pos = gAgent.getPositionGlobal();
        LLUIString pos_text = getString("you_are_at");
        pos_text.setArg("[POSITION]",
                        llformat("%.1f, %.1f, %.1f ", pos.mdV[VX], pos.mdV[VY], pos.mdV[VZ]));
        support.append(pos_text);

        std::string region_text = llformat("in %s located at ",
                                           gAgent.getRegion()->getName().c_str());
        support.append(region_text);

        std::string buffer;
        buffer = gAgent.getRegion()->getHost().getHostName();
        support.append(buffer);
        support.append(" (");
        buffer = gAgent.getRegion()->getHost().getString();
        support.append(buffer);
        support.append(")\n");
        support.append(gLastVersionChannel);
        support.append("\n");

        support_widget->appendColoredText(support, FALSE, FALSE, gColors.getColor("TextFgReadOnlyColor"));
        support_widget->appendStyledText(LLTrans::getString("ReleaseNotes"), false, false, server_link_style);

        support = "\n\n";
    }

    // *NOTE: Do not translate text like GPU, Graphics Card, etc -
    //  Most PC users that know what these mean will be used to the english versions,
    //  and this info sometimes gets sent to support

    // CPU
    support.append("CPU: ");
    support.append( gSysCPU.getCPUString() );
    support.append("\n");

    U32 memory = gSysMemory.getPhysicalMemoryKB() / 1024;
    // Moved hack adjustment to Windows memory size into llsys.cpp

    std::string mem_text = llformat("Memory: %u MB\n", memory );
    support.append(mem_text);

    support.append("OS Version: ");
    support.append( LLAppViewer::instance()->getOSInfo().getOSString() );
    support.append("\n");

    support.append("Graphics Card Vendor: ");
    support.append( (const char*) glGetString(GL_VENDOR) );
    support.append("\n");

    support.append("Graphics Card: ");
    support.append( (const char*) glGetString(GL_RENDERER) );
    support.append("\n");

#if LL_WINDOWS
    getWindow()->incBusyCount();
    getWindow()->setCursor(UI_CURSOR_ARROW);
    support.append("Windows Graphics Driver Version: ");
    LLSD driver_info = gDXHardware.getDisplayInfo();
    if (driver_info.has("DriverVersion"))
    {
        support.append(driver_info["DriverVersion"]);
    }
    support.append("\n");
    getWindow()->decBusyCount();
    getWindow()->setCursor(UI_CURSOR_ARROW);
#endif

    support.append("OpenGL Version: ");
    support.append( (const char*) glGetString(GL_VERSION) );
    support.append("\n");

    support.append("\n");

    support.append("libcurl Version: ");
    support.append( LLCurl::getVersionString() );
    support.append("\n");

    support.append("J2C Decoder Version: ");
    support.append( LLImageJ2C::getEngineInfo() );
    support.append("\n");

    support.append("Audio Driver Version: ");
    bool want_fullname = true;
    support.append( gAudiop ? gAudiop->getDriverName(want_fullname) : "(none)" );

    support.append("\n");

    LLMediaManager *mgr = LLMediaManager::getInstance();
    if (mgr)
    {
        LLMediaBase *gstreamer = mgr->createSourceFromMimeType("http", "audio/mpeg");
        if (gstreamer)
        {
            support.append("GStreamer Version: ");
            support.append( gstreamer->getVersion() );
            support.append("\n");
        }

        LLMediaBase *media_source = mgr->createSourceFromMimeType("http", "text/html");
        if (media_source)
        {
            support.append("LLMozLib Version: ");
            support.append(media_source->getVersion());
            support.append("\n");
            mgr->destroySource(media_source);
        }
    }

    if (gPacketsIn > 0)
    {
        std::string packet_loss = llformat("Packets Lost: %.0f/%.0f (%.1f%%)",
                                           LLViewerStats::getInstance()->mPacketsLostStat.getCurrent(),
                                           F32(gPacketsIn),
                                           100.f*LLViewerStats::getInstance()->mPacketsLostStat.getCurrent() / F32(gPacketsIn) );
        support.append(packet_loss);
        support.append("\n");
    }

    support_widget->appendColoredText(support, FALSE, FALSE, gColors.getColor("TextFgReadOnlyColor"));

    // Fix views
    support_widget->setCursorPos(0);
    support_widget->setEnabled(FALSE);
    support_widget->setTakesFocus(TRUE);
    support_widget->setHandleEditKeysDirectly(TRUE);

    credits_widget->setCursorPos(0);
    credits_widget->setEnabled(FALSE);
    credits_widget->setTakesFocus(TRUE);
    credits_widget->setHandleEditKeysDirectly(TRUE);

    center();

    sInstance = this;
}