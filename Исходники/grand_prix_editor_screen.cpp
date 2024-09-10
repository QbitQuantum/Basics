// -----------------------------------------------------------------------------
void GrandPrixEditorScreen::init()
{
    RibbonWidget* tabs = getWidget<RibbonWidget>("gpgroups");
    assert (tabs != NULL);

    tabs->select (StringUtils::toString(m_gpgroup), PLAYER_ID_GAME_MASTER);
    loadGPList();
    setSelection(m_selection);
}