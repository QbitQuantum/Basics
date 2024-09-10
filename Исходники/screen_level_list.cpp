void CScreenLevelList::CreateInterface()
{
    CWindow*        pw;
    CEdit*          pe;
    CLabel*         pl;
    CButton*        pb;
    CCheck*         pc;
    CList*          pli;
    Math::Point     pos, ddim;
    int             res;
    std::string     name;

    if ( m_category == LevelCategory::FreeGame )
    {
        m_accessChap = m_main->GetPlayerProfile()->GetChapPassed(LevelCategory::Missions);
    }

    pos.x = 0.10f;
    pos.y = 0.10f;
    ddim.x = 0.80f;
    ddim.y = 0.80f;
    pw = m_interface->CreateWindows(pos, ddim, 12, EVENT_WINDOW5);
    pw->SetClosable(true);
    if ( m_category == LevelCategory::Exercises    )  res = RT_TITLE_TRAINER;
    if ( m_category == LevelCategory::Challenges   )  res = RT_TITLE_DEFI;
    if ( m_category == LevelCategory::Missions     )  res = RT_TITLE_MISSION;
    if ( m_category == LevelCategory::FreeGame     )  res = RT_TITLE_FREE;
    if ( m_category == LevelCategory::CodeBattles  )  res = RT_TITLE_CODE_BATTLES;
    if ( m_category == LevelCategory::CustomLevels )  res = RT_TITLE_USER;
    GetResource(RES_TEXT, res, name);
    pw->SetName(name);

    pos.x  = 0.10f;
    pos.y  = 0.40f;
    ddim.x = 0.50f;
    ddim.y = 0.50f;
    pw->CreateGroup(pos, ddim, 5, EVENT_INTERFACE_GLINTl);  // orange corner
    pos.x  = 0.40f;
    pos.y  = 0.10f;
    ddim.x = 0.50f;
    ddim.y = 0.50f;
    pw->CreateGroup(pos, ddim, 4, EVENT_INTERFACE_GLINTr);  // blue corner

    // Displays a list of chapters:
    pos.x = ox+sx*3;
    pos.y = oy+sy*10.5f;
    ddim.x = dim.x*7.5f;
    ddim.y = dim.y*0.6f;
    res = RT_PLAY_CHAP_CHAPTERS;
    if ( m_category == LevelCategory::Missions     )  res = RT_PLAY_CHAP_PLANETS;
    if ( m_category == LevelCategory::FreeGame     )  res = RT_PLAY_CHAP_PLANETS;
    if ( m_category == LevelCategory::CustomLevels )  res = RT_PLAY_CHAP_USERLVL;
    GetResource(RES_TEXT, res, name);
    pl = pw->CreateLabel(pos, ddim, 0, EVENT_LABEL11, name);
    pl->SetTextAlign(Gfx::TEXT_ALIGN_LEFT);

    pos.y = oy+sy*6.7f;
    ddim.y = dim.y*4.5f;
    ddim.x = dim.x*6.5f;
    pli = pw->CreateList(pos, ddim, 0, EVENT_INTERFACE_CHAP);
    pli->SetState(STATE_SHADOW);
    m_chap[m_category] = m_main->GetPlayerProfile()->GetSelectedChap(m_category)-1;
    UpdateSceneChap(m_chap[m_category]);
    if ( m_category != LevelCategory::FreeGame &&
         m_category != LevelCategory::CodeBattles &&
         m_category != LevelCategory::CustomLevels ) // Don't show completion marks in free game, code battles and userlevels
    {
        pli->SetState(STATE_EXTEND);
    }

    // Displays a list of missions:
    pos.x = ox+sx*9.5f;
    pos.y = oy+sy*10.5f;
    ddim.x = dim.x*7.5f;
    ddim.y = dim.y*0.6f;
    res = RT_PLAY_LIST_LEVELS;
    if ( m_category == LevelCategory::Exercises    )  res = RT_PLAY_LIST_EXERCISES;
    if ( m_category == LevelCategory::Challenges   )  res = RT_PLAY_LIST_CHALLENGES;
    if ( m_category == LevelCategory::Missions     )  res = RT_PLAY_LIST_MISSIONS;
    if ( m_category == LevelCategory::FreeGame     )  res = RT_PLAY_LIST_FREEGAME;
    GetResource(RES_TEXT, res, name);
    pl = pw->CreateLabel(pos, ddim, 0, EVENT_LABEL12, name);
    pl->SetTextAlign(Gfx::TEXT_ALIGN_LEFT);

    pos.y = oy+sy*6.7f;
    ddim.y = dim.y*4.5f;
    ddim.x = dim.x*6.5f;
    pli = pw->CreateList(pos, ddim, 0, EVENT_INTERFACE_LIST);
    pli->SetState(STATE_SHADOW);
    m_sel[m_category] = m_main->GetPlayerProfile()->GetSelectedRank(m_category)-1;
    UpdateSceneList(m_chap[m_category], m_sel[m_category]);
    if ( m_category != LevelCategory::FreeGame &&
         m_category != LevelCategory::CodeBattles &&
         m_category != LevelCategory::CustomLevels ) // Don't show completion marks in free game, code battles and userlevels
    {
        pli->SetState(STATE_EXTEND);
    }
    pos = pli->GetPos();
    ddim = pli->GetDim();

    // Displays the summary:
    pos.x = ox+sx*3;
    pos.y = oy+sy*5.4f;
    ddim.x = dim.x*6.5f;
    ddim.y = dim.y*0.6f;
    GetResource(RES_TEXT, RT_PLAY_RESUME, name);
    pl = pw->CreateLabel(pos, ddim, 0, EVENT_LABEL13, name);
    pl->SetTextAlign(Gfx::TEXT_ALIGN_LEFT);

    pos.x = ox+sx*3;
    pos.y = oy+sy*3.6f;
    ddim.x = dim.x*13.4f;
    ddim.y = dim.y*1.9f;
    pe = pw->CreateEdit(pos, ddim, 0, EVENT_INTERFACE_RESUME);
    pe->SetState(STATE_SHADOW);
    pe->SetMaxChar(500);
    pe->SetEditCap(false);  // just to see
    pe->SetHighlightCap(false);

    // Button displays the "soluce":
    if ( m_category != LevelCategory::Exercises &&
         m_category != LevelCategory::FreeGame   )
    {
        pos.x = ox+sx*9.5f;
        pos.y = oy+sy*5.8f;
        ddim.x = dim.x*6.5f;
        ddim.y = dim.y*0.5f;
        pc = pw->CreateCheck(pos, ddim, -1, EVENT_INTERFACE_SOLUCE);
        pc->SetState(STATE_SHADOW);
        pc->ClearState(STATE_CHECK);
    }
    m_sceneSoluce = false;

    UpdateSceneResume(m_chap[m_category]+1, m_sel[m_category]+1);

    if ( m_category == LevelCategory::Missions    ||
         m_category == LevelCategory::FreeGame    ||
         m_category == LevelCategory::CustomLevels )
    {
        pos.x = ox+sx*9.5f;
        pos.y = oy+sy*2;
        ddim.x = dim.x*3.7f;
        ddim.y = dim.y*1;
        pb = pw->CreateButton(pos, ddim, -1, EVENT_INTERFACE_PLAY);
        pb->SetState(STATE_SHADOW);
        if ( m_maxList == 0 )
        {
            pb->ClearState(STATE_ENABLE);
        }

        pos.x += dim.x*4.0f;
        ddim.x = dim.x*2.5f;
        pb = pw->CreateButton(pos, ddim, -1, EVENT_INTERFACE_READ);
        pb->SetState(STATE_SHADOW);
        if ( !m_main->GetPlayerProfile()->HasAnySavedScene() )  // no file to read?
        {
            pb->ClearState(STATE_ENABLE);
        }
    }
    else
    {
        pos.x = ox+sx*9.5f;
        pos.y = oy+sy*2;
        ddim.x = dim.x*6.5f;
        ddim.y = dim.y*1;
        pb = pw->CreateButton(pos, ddim, -1, EVENT_INTERFACE_PLAY);
        pb->SetState(STATE_SHADOW);
        if ( m_maxList == 0 )
        {
            pb->ClearState(STATE_ENABLE);
        }
    }

    pos.x = ox+sx*3;
    ddim.x = dim.x*4;
    pb = pw->CreateButton(pos, ddim, -1, EVENT_INTERFACE_BACK);
    pb->SetState(STATE_SHADOW);

    SetBackground("textures/interface/interface.png");
    CreateVersionDisplay();

    if (m_category == LevelCategory::CustomLevels)
    {
        if(m_customLevelList.size() == 0)
        {
            m_main->ChangePhase(PHASE_MAIN_MENU);
            std::string title, text;
            GetResource(RES_TEXT, RT_DIALOG_NOUSRLVL_TITLE, title);
            GetResource(RES_TEXT, RT_DIALOG_NOUSRLVL_TEXT, text);
            m_dialog->StartInformation(title, title, text);
        }
    }
}