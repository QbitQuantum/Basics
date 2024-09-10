void EasterEggScreen::init()
{
    DynamicRibbonWidget* tracks_widget = this->getWidget<DynamicRibbonWidget>("tracks");
    assert( tracks_widget != NULL );

    RibbonWidget* tabs = this->getWidget<RibbonWidget>("trackgroups");
    assert( tabs != NULL );
    tabs->select(UserConfigParams::m_last_used_track_group, PLAYER_ID_GAME_MASTER);


    buildTrackList();

    // select old track for the game master (if found)
    irr_driver->setTextureErrorMessage(
              "While loading screenshot in track screen for last track '%s':",
              UserConfigParams::m_last_track);
    if (!tracks_widget->setSelection(UserConfigParams::m_last_track,
                                     PLAYER_ID_GAME_MASTER, true))
    {
        tracks_widget->setSelection(0, PLAYER_ID_GAME_MASTER, true);
    }
    irr_driver->unsetTextureErrorMessage();
}