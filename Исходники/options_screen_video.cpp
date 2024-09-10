void OptionsScreenVideo::init()
{
    Screen::init();
    RibbonWidget* ribbon = getWidget<RibbonWidget>("options_choice");
    assert(ribbon != NULL);
    ribbon->select( "tab_video", PLAYER_ID_GAME_MASTER );

    ribbon->getRibbonChildren()[1].setTooltip( _("Audio") );
    ribbon->getRibbonChildren()[2].setTooltip( _("User Interface") );
    ribbon->getRibbonChildren()[3].setTooltip( _("Players") );
    ribbon->getRibbonChildren()[4].setTooltip( _("Controls") );

    GUIEngine::ButtonWidget* applyBtn =
        getWidget<GUIEngine::ButtonWidget>("apply_resolution");
    assert( applyBtn != NULL );

    GUIEngine::SpinnerWidget* gfx =
        getWidget<GUIEngine::SpinnerWidget>("gfx_level");
    assert( gfx != NULL );

    GUIEngine::CheckBoxWidget* vsync =
        getWidget<GUIEngine::CheckBoxWidget>("vsync");
    assert( vsync != NULL );
    vsync->setState( UserConfigParams::m_vsync );


    // ---- video modes
    DynamicRibbonWidget* res = getWidget<DynamicRibbonWidget>("resolutions");
    assert( res != NULL );


    CheckBoxWidget* full = getWidget<CheckBoxWidget>("fullscreen");
    assert( full != NULL );
    full->setState( UserConfigParams::m_fullscreen );

    CheckBoxWidget* rememberWinpos = getWidget<CheckBoxWidget>("rememberWinpos");
    rememberWinpos->setState(UserConfigParams::m_remember_window_location);

    rememberWinpos->setActive(UserConfigParams::m_fullscreen);

    // --- get resolution list from irrlicht the first time
    if (!m_inited)
    {
        res->clearItems();

        const std::vector<IrrDriver::VideoMode>& modes =
            irr_driver->getVideoModes();
        const int amount = (int)modes.size();

        std::vector<Resolution> resolutions;
        Resolution r;

        bool found_config_res = false;

        // for some odd reason, irrlicht sometimes fails to report the good
        // old standard resolutions
        // those are always useful for windowed mode
        bool found_1024_768 = false;

        for (int n=0; n<amount; n++)
        {
            r.width  = modes[n].getWidth();
            r.height = modes[n].getHeight();
            resolutions.push_back(r);

            if (r.width  == UserConfigParams::m_width &&
                    r.height == UserConfigParams::m_height)
            {
                found_config_res = true;
            }

            if (r.width == 1024 && r.height == 768)
            {
                found_1024_768 = true;
            }
        }

        if (!found_config_res)
        {
            r.width  = UserConfigParams::m_width;
            r.height = UserConfigParams::m_height;
            resolutions.push_back(r);

            if (r.width == 1024 && r.height == 768)
            {
                found_1024_768 = true;
            }
        } // next found resolution

        // Add default resolutions that were not found by irrlicht
        if (!found_1024_768)
        {
            r.width  = 1024;
            r.height = 768;
            resolutions.push_back(r);
        }

        // Sort resolutions by size
        std::sort(resolutions.begin(), resolutions.end());

        // Add resolutions list
        for(std::vector<Resolution>::iterator it = resolutions.begin();
                it != resolutions.end(); it++)
        {
            const float ratio = it->getRatio();
            char name[32];
            sprintf(name, "%ix%i", it->width, it->height);

            core::stringw label;
            label += it->width;
            label += L"\u00D7";
            label += it->height;

#define ABOUT_EQUAL(a , b) (fabsf( a - b ) < 0.01)

            if      (ABOUT_EQUAL( ratio, (5.0f/4.0f) ))
                res->addItem(label, name, "/gui/screen54.png");
            else if (ABOUT_EQUAL( ratio, (4.0f/3.0f) ))
                res->addItem(label, name, "/gui/screen43.png");
            else if (ABOUT_EQUAL( ratio, (16.0f/10.0f)))
                res->addItem(label, name, "/gui/screen1610.png");
            else if (ABOUT_EQUAL( ratio, (5.0f/3.0f) ))
                res->addItem(label, name, "/gui/screen53.png");
            else if (ABOUT_EQUAL( ratio, (3.0f/2.0f) ))
                res->addItem(label, name, "/gui/screen32.png");
            else if (ABOUT_EQUAL( ratio, (16.0f/9.0f) ))
                res->addItem(label, name, "/gui/screen169.png");
            else
                res->addItem(label, name, "/gui/screen_other.png");
#undef ABOUT_EQUAL
        } // add next resolution
    } // end if not inited

    res->updateItemDisplay();

    // ---- select current resolution every time
    char searching_for[32];
    snprintf(searching_for, 32, "%ix%i", (int)UserConfigParams::m_width,
             (int)UserConfigParams::m_height);


    if (!res->setSelection(searching_for, PLAYER_ID_GAME_MASTER,
                           false /* focus it */, true /* even if deactivated*/))
    {
        Log::error("OptionsScreenVideo", "Cannot find resolution %s", searching_for);
    }


    // --- set gfx settings values
    updateGfxSlider();

    // ---- forbid changing resolution or animation settings from in-game
    // (we need to disable them last because some items can't be edited when
    // disabled)
    bool in_game = StateManager::get()->getGameState() == GUIEngine::INGAME_MENU;

    res->setActive(!in_game);
    full->setActive(!in_game);
    applyBtn->setActive(!in_game);
    gfx->setActive(!in_game);
    getWidget<ButtonWidget>("custom")->setActive(!in_game);
}   // init