GPInfoDialog::GPInfoDialog(const std::string& gpIdent, const float w, const float h) : ModalDialog(w, h)
{
    doInit();
    m_curr_time = 0.0f;

    const int y1 = m_area.getHeight()/7;
    const int y2 = m_area.getHeight()*6/7;

    m_gp_ident = gpIdent;

    const GrandPrixData* gp = grand_prix_manager->getGrandPrix(gpIdent);
    if (gp == NULL)
    {
        assert(false);
        std::cerr << "ERROR at " << __FILE__ << " : " << __LINE__ << "; trying to continue\n";
        ModalDialog::dismiss();
        return;
    }

    // ---- GP Name
    core::rect< s32 > area_top(0, 0, m_area.getWidth(), y1);
    IGUIStaticText* title = GUIEngine::getGUIEnv()->addStaticText( translations->fribidize(gp->getName()),
                                                               area_top, false, true, // border, word wrap
                                                               m_irrlicht_window);
    title->setTabStop(false);
    title->setTextAlignment(EGUIA_CENTER, EGUIA_CENTER);


    // ---- Track listings
    const std::vector<std::string>& tracks = gp->getTrackNames();
    const int trackAmount = tracks.size();

    int height_of_one_line = (y2 - y1)/(trackAmount+1);
    const int textHeight = GUIEngine::getFontHeight();
    if (height_of_one_line > (int)(textHeight*1.5f)) height_of_one_line = (int)(textHeight*1.5f);

    bool gp_ok = true;

    for (int t=0; t<trackAmount; t++)
    {
        const int from_y = y1 + height_of_one_line*(t+1);

        Track* track = track_manager->getTrack(tracks[t]);
        stringw lineText;
        if (track == NULL)
        {
            lineText = L"MISSING : ";
            lineText.append( stringw(tracks[t].c_str()) );
            gp_ok = false;
        }
        else
        {
            lineText = track->getName();
        }

        LabelWidget* widget = new LabelWidget();
        widget->setText(translations->fribidize(lineText), false);
        widget->m_x = 20;
        widget->m_y = from_y;
        widget->m_w = m_area.getWidth()/2 - 20;
        widget->m_h = height_of_one_line;
        widget->setParent(m_irrlicht_window);

        m_widgets.push_back(widget);
        widget->add();

        // IGUIStaticText* line = GUIEngine::getGUIEnv()->addStaticText( lineText.c_str(),
        //                                       entry_area, false , true , // border, word wrap
        //                                       m_irrlicht_window);
    }

    // ---- Track screenshot

    m_screenshot_widget = new IconButtonWidget(IconButtonWidget::SCALE_MODE_KEEP_CUSTOM_ASPECT_RATIO,
                                               false /* tab stop */, false /* focusable */,
                                               IconButtonWidget::ICON_PATH_TYPE_ABSOLUTE /* Track gives us absolute paths */);
    // images are saved squared, but must be stretched to 4:3
    m_screenshot_widget->setCustomAspectRatio(4.0f / 3.0f);

    m_screenshot_widget->m_x = m_area.getWidth()/2;
    m_screenshot_widget->m_y = y1;
    m_screenshot_widget->m_w = m_area.getWidth()/2;
    m_screenshot_widget->m_h = y2 - y1 - 10;

    Track* track = track_manager->getTrack(tracks[0]);

    m_screenshot_widget->m_properties[PROP_ICON] = (track  != NULL ?
                                                    track->getScreenshotFile().c_str() :
                                                    file_manager->getAsset(FileManager::GUI,"main_help.png"));
    m_screenshot_widget->setParent(m_irrlicht_window);
    m_screenshot_widget->add();
    m_widgets.push_back(m_screenshot_widget);


    // ---- Start button
    ButtonWidget* okBtn = new ButtonWidget();
    ButtonWidget* continueBtn = new ButtonWidget();

    SavedGrandPrix* saved_gp = SavedGrandPrix::getSavedGP( StateManager::get()
                                               ->getActivePlayerProfile(0)
                                               ->getUniqueID(),
                                               gpIdent,
                                               race_manager->getDifficulty(),
                                               race_manager->getNumberOfKarts(),
                                               race_manager->getNumLocalPlayers());

    if (gp_ok)
    {
        okBtn->m_properties[PROP_ID] = "start";
        okBtn->setText(_("Start Grand Prix"));

        continueBtn->m_properties[PROP_ID] = "continue";
        continueBtn->setText(_("Continue"));
    }
    else
    {
        okBtn->m_properties[PROP_ID] = "cannot_start";
        okBtn->setText(_("This Grand Prix is broken!"));
        okBtn->setBadge(BAD_BADGE);
    }

    if (saved_gp && gp_ok)
    {
        continueBtn->m_x = m_area.getWidth()/2 + 110;
        continueBtn->m_y = y2;
        continueBtn->m_w = 200;
        continueBtn->m_h = m_area.getHeight() - y2 - 15;
        continueBtn->setParent(m_irrlicht_window);
        m_widgets.push_back(continueBtn);
        continueBtn->add();
        continueBtn->getIrrlichtElement()->setTabStop(true);
        continueBtn->getIrrlichtElement()->setTabGroup(false);
        
        okBtn->m_x = m_area.getWidth()/2 - 310;
    }
    else
    {
        okBtn->m_x = m_area.getWidth()/2 - 200;
    }
    
    okBtn->m_y = y2;
    okBtn->m_w = 400;
    okBtn->m_h = m_area.getHeight() - y2 - 15;
    okBtn->setParent(m_irrlicht_window);
    m_widgets.push_back(okBtn);
    okBtn->add();
    okBtn->getIrrlichtElement()->setTabStop(true);
    okBtn->getIrrlichtElement()->setTabGroup(false);

    okBtn->setFocusForPlayer( PLAYER_ID_GAME_MASTER );
    
}