// -----------------------------------------------------------------------------
void EditTrackScreen::init()
{
    RibbonWidget* tabs = getWidget<RibbonWidget>("trackgroups");
    assert (tabs != NULL);
    SpinnerWidget* laps = getWidget<SpinnerWidget>("laps");
    assert(laps != NULL);
    CheckBoxWidget* reverse = getWidget<CheckBoxWidget>("reverse");
    assert(reverse != NULL);

    if (m_track_group.empty())
        tabs->select (ALL_TRACKS_GROUP_ID, PLAYER_ID_GAME_MASTER);
    else
        tabs->select (m_track_group, PLAYER_ID_GAME_MASTER);
    laps->setValue(m_laps);
    reverse->setState(m_reverse);

    loadTrackList();
    if (m_track == NULL)
        selectTrack("");
    else
        selectTrack(m_track->getIdent());
}