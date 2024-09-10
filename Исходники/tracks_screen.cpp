void TracksScreen::init()
{
    DynamicRibbonWidget* gps_widget = this->getWidget<DynamicRibbonWidget>("gps");
    assert( gps_widget != NULL );
    
    DynamicRibbonWidget* tracks_widget = this->getWidget<DynamicRibbonWidget>("tracks");
    assert( tracks_widget != NULL );
    
    // Reset GP list everytime (accounts for locking changes, etc.)
    gps_widget->clearItems();
    
    // Build GP list
    const int gpAmount = grand_prix_manager->getNumberOfGrandPrix();
    for (int n=0; n<gpAmount; n++)
    {
        const GrandPrixData* gp = grand_prix_manager->getGrandPrix(n);
        
        std::vector<std::string> tracks = gp->getTracks();
        
        std::vector<std::string> sshot_files;
        for (unsigned int t=0; t<tracks.size(); t++)
        {
            Track* curr = track_manager->getTrack(tracks[t]);
            if (curr == NULL)
            {
                std::cerr << "/!\\ WARNING: Grand Prix '" << gp->getId() << "' refers to track '"
                          << tracks[t] << "', which does not exist.\n";
            }
            else
            {
                sshot_files.push_back(curr->getScreenshotFile());
            }
        }
        if (sshot_files.size() == 0)
        {
            std::cerr << "/!\\ WARNING: Grand Prix '" << gp->getId()
                      << "' does not contain any valid track.\n";
            sshot_files.push_back("gui/main_help.png");
        }
        
        if (unlock_manager->getCurrentSlot()->isLocked(gp->getId()))
        {
            gps_widget->addAnimatedItem(_("Locked!"),
                                        "locked", sshot_files, 1.5f, LOCKED_BADGE | TROPHY_BADGE,
                                        IconButtonWidget::ICON_PATH_TYPE_ABSOLUTE);
        }
        else
        {
            gps_widget->addAnimatedItem(translations->fribidize(gp->getName()), gp->getId(),
                                        sshot_files, 1.5f, TROPHY_BADGE,
                                        IconButtonWidget::ICON_PATH_TYPE_ABSOLUTE );
        }
    }
    gps_widget->updateItemDisplay();
    
    
    RibbonWidget* tabs = this->getWidget<RibbonWidget>("trackgroups");
    assert( tabs != NULL );
    tabs->select(UserConfigParams::m_last_used_track_group, PLAYER_ID_GAME_MASTER);

    
    buildTrackList();
    
    // select something for the game master
    // FIXME: 'setSelection' will not scroll up to the passed track, so if given track
    //         is not visible with current scrolling this fails
    if (!tracks_widget->setSelection(UserConfigParams::m_last_track,
                                     PLAYER_ID_GAME_MASTER, true))
    {
        tracks_widget->setSelection(0, PLAYER_ID_GAME_MASTER, true);
    }
}