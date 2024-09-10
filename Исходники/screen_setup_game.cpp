void CScreenSetupGame::CreateInterface()
{
    CWindow*        pw;
    CLabel*         pl;
    CCheck*         pc;
    CSlider*        psl;
    CList*          pli;
    Math::Point     pos, ddim;
    std::string     name;

    CScreenSetup::CreateInterface();
    pw = static_cast<CWindow*>(m_interface->SearchControl(EVENT_WINDOW5));
    if ( pw == nullptr )  return;

    ddim.x = dim.x*6;
    ddim.y = dim.y*0.5f;
    pos.x = ox+sx*3;
    pos.y = 0.65f;

    pc = pw->CreateCheck(pos, ddim, -1, EVENT_INTERFACE_MOVIES);
    pc->SetState(STATE_SHADOW);
    pos.y -= 0.048f;
    pc = pw->CreateCheck(pos, ddim, -1, EVENT_INTERFACE_SCROLL);
    pc->SetState(STATE_SHADOW);
    pos.y -= 0.048f;
    pc = pw->CreateCheck(pos, ddim, -1, EVENT_INTERFACE_INVERTX);
    pc->SetState(STATE_SHADOW);
    pos.y -= 0.048f;
    pc = pw->CreateCheck(pos, ddim, -1, EVENT_INTERFACE_INVERTY);
    pc->SetState(STATE_SHADOW);
    pos.y -= 0.048f;
    pc = pw->CreateCheck(pos, ddim, -1, EVENT_INTERFACE_EFFECT);
    pc->SetState(STATE_SHADOW);
    pos.y -= 0.048f;
    pc = pw->CreateCheck(pos, ddim, -1, EVENT_INTERFACE_BLOOD);
    pc->SetState(STATE_SHADOW);
    pos.y -= 0.048f;
    pc = pw->CreateCheck(pos, ddim, -1, EVENT_INTERFACE_AUTOSAVE_ENABLE);
    pc->SetState(STATE_SHADOW);
    pos.y -= 0.048f;

    pos.y -= ddim.y;
    ddim.x = dim.x*2.5f;
    psl = pw->CreateSlider(pos, ddim, -1, EVENT_INTERFACE_AUTOSAVE_INTERVAL);
    psl->SetState(STATE_SHADOW);
    psl->SetLimit(1.0f, 30.0f);
    psl->SetArrowStep(1.0f);
    pos.y += ddim.y/2;
    GetResource(RES_EVENT, EVENT_INTERFACE_AUTOSAVE_INTERVAL, name);
    pl = pw->CreateLabel(pos, ddim, 0, EVENT_LABEL1, name);
    pl->SetTextAlign(Gfx::TEXT_ALIGN_LEFT);
    pos.y -= ddim.y/2;
    pos.x = ox+sx*3+dim.x*4.0f;
    psl = pw->CreateSlider(pos, ddim, -1, EVENT_INTERFACE_AUTOSAVE_SLOTS);
    psl->SetState(STATE_SHADOW);
    psl->SetLimit(1.0f, 10.0f);
    psl->SetArrowStep(1.0f);
    pos.y += ddim.y/2;
    GetResource(RES_EVENT, EVENT_INTERFACE_AUTOSAVE_SLOTS, name);
    pl = pw->CreateLabel(pos, ddim, 0, EVENT_LABEL1, name);
    pl->SetTextAlign(Gfx::TEXT_ALIGN_LEFT);
    pos.y -= ddim.y/2;

    ddim.x = dim.x*6;
    ddim.y = dim.y*0.5f;
    pos.x = ox+sx*10;
    pos.y = 0.65f;
    pc = pw->CreateCheck(pos, ddim, -1, EVENT_INTERFACE_TOOLTIP);
    pc->SetState(STATE_SHADOW);
    pos.y -= 0.048f;
    pc = pw->CreateCheck(pos, ddim, -1, EVENT_INTERFACE_GLINT);
    pc->SetState(STATE_SHADOW);
    pos.y -= 0.048f;
    pc = pw->CreateCheck(pos, ddim, -1, EVENT_INTERFACE_RAIN);
    pc->SetState(STATE_SHADOW);
    pos.y -= 0.048f;
    pc = pw->CreateCheck(pos, ddim, -1, EVENT_INTERFACE_BGPAUSE);
    pc->SetState(STATE_SHADOW);
    pos.y -= 0.048f;
    pos.y -= 0.048f;
    pc = pw->CreateCheck(pos, ddim, -1, EVENT_INTERFACE_EDITMODE);
    pc->SetState(STATE_SHADOW);
    if ( m_simulationSetup )
    {
        pc->SetState(STATE_DEAD);
    }
    pos.y -= 0.048f;
    pc = pw->CreateCheck(pos, ddim, -1, EVENT_INTERFACE_EDITVALUE);
    pc->SetState(STATE_SHADOW);

    ddim.y = dim.y*3.0f;
    pos.y -= ddim.y;
    pli = pw->CreateList(pos, ddim, 0, EVENT_INTERFACE_LANGUAGE);
    pli->SetState(STATE_SHADOW);
    // TODO: Add something like GetSupportedLanguages() and GetLanguageFriendlyName() for this
    pli->SetItemName(1+LANGUAGE_ENV, "[System default]");
    pli->SetItemName(1+LANGUAGE_ENGLISH, "English");
    pli->SetItemName(1+LANGUAGE_FRENCH, "French");
    pli->SetItemName(1+LANGUAGE_GERMAN, "German");
    pli->SetItemName(1+LANGUAGE_POLISH, "Polish");
    pli->SetItemName(1+LANGUAGE_RUSSIAN, "Russian");

    UpdateSetupButtons();
}