void OptionsScreenAudio::init()
{
    Screen::init();
    RibbonWidget* ribbon = this->getWidget<RibbonWidget>("options_choice");
    if (ribbon != NULL)  ribbon->select( "tab_audio", PLAYER_ID_GAME_MASTER );

    ribbon->getRibbonChildren()[0].setTooltip( _("Graphics") );
    ribbon->getRibbonChildren()[2].setTooltip( _("User Interface") );
    ribbon->getRibbonChildren()[3].setTooltip( _("Players") );
    ribbon->getRibbonChildren()[4].setTooltip( _("Controls") );

    // ---- sfx volume
    SpinnerWidget* gauge = this->getWidget<SpinnerWidget>("sfx_volume");
    assert(gauge != NULL);

    gauge->setValue( (int)(sfx_manager->getMasterSFXVolume()*10.0f) );


    gauge = this->getWidget<SpinnerWidget>("music_volume");
    assert(gauge != NULL);
    gauge->setValue( (int)(music_manager->getMasterMusicVolume()*10.f) );

    // ---- music volume
    CheckBoxWidget* sfx = this->getWidget<CheckBoxWidget>("sfx_enabled");

    CheckBoxWidget* music = this->getWidget<CheckBoxWidget>("music_enabled");

    // ---- audio enables/disables
    sfx->setState( UserConfigParams::m_sfx );
    music->setState( UserConfigParams::m_music );

}   // init