void CScreenIO::IOReadName()
{
    CWindow*    pw;
    CEdit*      pe;
    std::string resume;
    char        line[100];
    char        name[100];
    time_t      now;

    pw = static_cast<CWindow*>(m_interface->SearchControl(EVENT_WINDOW5));
    if ( pw == nullptr )  return;
    pe = static_cast<CEdit*>(pw->SearchControl(EVENT_INTERFACE_IONAME));
    if ( pe == nullptr )  return;

    resume = GetLevelCategoryDir(m_main->GetLevelCategory()) + " " + StrUtils::ToString<int>(m_main->GetLevelChap());

    CLevelParser levelParser(m_main->GetLevelCategory(), m_main->GetLevelChap(), 0);
    try
    {
        levelParser.Load();
        resume = levelParser.Get("Title")->GetParam("resume")->AsString();
    }
    catch (CLevelParserException& e)
    {
        GetLogger()->Warn("%s\n", e.what());
    }

    time(&now);
    TimeToAsciiClean(now, line);
    sprintf(name, "%s - %s %d", line, resume.c_str(), m_main->GetLevelRank());

    pe->SetText(name);
    pe->SetCursor(strlen(name), 0);
    m_interface->SetFocus(pe);
}