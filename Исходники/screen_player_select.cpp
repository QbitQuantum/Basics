void CScreenPlayerSelect::CreateInterface()
{
    CWindow*        pw;
    CEdit*          pe;
    CLabel*         pl;
    CButton*        pb;
    CList*          pli;
    CGroup*         pg;
    Math::Point     pos, ddim;
    std::string     name;

    pos.x = 0.10f;
    pos.y = 0.10f;
    ddim.x = 0.80f;
    ddim.y = 0.80f;
    pw = m_interface->CreateWindows(pos, ddim, 12, EVENT_WINDOW5);
    GetResource(RES_TEXT, RT_TITLE_NAME, name);
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

    pos.x =  60.0f/640.0f;
    pos.y = 313.0f/480.0f;
    ddim.x = 120.0f/640.0f;
    ddim.y =  32.0f/480.0f;
    GetResource(RES_EVENT, EVENT_INTERFACE_NLABEL, name);
    pl = pw->CreateLabel(pos, ddim, -1, EVENT_INTERFACE_NLABEL, name);
    pl->SetTextAlign(Gfx::TEXT_ALIGN_RIGHT);

    pos.x = 200.0f/640.0f;
    pos.y = 320.0f/480.0f;
    ddim.x = 160.0f/640.0f;
    ddim.y =  32.0f/480.0f;
    pg = pw->CreateGroup(pos, ddim, 7, EVENT_LABEL1);
    pg->SetState(STATE_SHADOW);

    pos.x = 207.0f/640.0f;
    pos.y = 328.0f/480.0f;
    ddim.x = 144.0f/640.0f;
    ddim.y =  18.0f/480.0f;
    pe = pw->CreateEdit(pos, ddim, 0, EVENT_INTERFACE_NEDIT);
    pe->SetMaxChar(15);
    if(m_main->GetPlayerProfile() != nullptr)
    {
        name = m_main->GetPlayerProfile()->GetName();
    }
    else
    {
        name = CPlayerProfile::GetLastName();
    }
    pe->SetText(name.c_str());
    pe->SetCursor(name.length(), 0);
    m_interface->SetFocus(pe);

    pos.x = 380.0f/640.0f;
    pos.y = 320.0f/480.0f;
    ddim.x =100.0f/640.0f;
    ddim.y = 32.0f/480.0f;
    pb = pw->CreateButton(pos, ddim, -1, EVENT_INTERFACE_NOK);
    pb->SetState(STATE_SHADOW);

    pos.x = 380.0f/640.0f;
    pos.y = 250.0f/480.0f;
    ddim.x =100.0f/640.0f;
    ddim.y = 52.0f/480.0f;
    pb = pw->CreateButton(pos, ddim, -1, EVENT_INTERFACE_PERSO);
    pb->SetState(STATE_SHADOW);

    pos.x = 200.0f/640.0f;
    pos.y = 150.0f/480.0f;
    ddim.x = 160.0f/640.0f;
    ddim.y = 160.0f/480.0f;
    pli = pw->CreateList(pos, ddim, 0, EVENT_INTERFACE_NLIST);
    pli->SetState(STATE_SHADOW);

    pos.x = 200.0f/640.0f;
    pos.y = 100.0f/480.0f;
    ddim.x = 160.0f/640.0f;
    ddim.y =  32.0f/480.0f;
    pb = pw->CreateButton(pos, ddim, -1, EVENT_INTERFACE_NDELETE);
    pb->SetState(STATE_SHADOW);

    SetBackground("textures/interface/interface.png");
    CreateVersionDisplay();

    ReadNameList();
    UpdateNameList();
    UpdateNameControl();
}