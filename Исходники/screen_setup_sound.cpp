void CScreenSetupSound::CreateInterface()
{
    CWindow*        pw;
    CLabel*         pl;
    CSlider*        psl;
    CButton*        pb;
    Math::Point     pos, ddim;
    std::string     name;

    CScreenSetup::CreateInterface();
    pw = static_cast<CWindow*>(m_interface->SearchControl(EVENT_WINDOW5));
    if ( pw == nullptr )  return;

    pos.x = ox+sx*3;
    pos.y = 0.55f;
    ddim.x = dim.x*4.0f;
    ddim.y = 18.0f/480.0f;
    psl = pw->CreateSlider(pos, ddim, 0, EVENT_INTERFACE_VOLSOUND);
    psl->SetState(STATE_SHADOW);
    psl->SetLimit(0.0f, MAXVOLUME);
    psl->SetArrowStep(1.0f);
    pos.y += ddim.y;
    GetResource(RES_EVENT, EVENT_INTERFACE_VOLSOUND, name);
    pl = pw->CreateLabel(pos, ddim, 0, EVENT_LABEL1, name);
    pl->SetTextAlign(Gfx::TEXT_ALIGN_LEFT);

    pos.x = ox+sx*3;
    pos.y = 0.40f;
    ddim.x = dim.x*4.0f;
    ddim.y = 18.0f/480.0f;
    psl = pw->CreateSlider(pos, ddim, 0, EVENT_INTERFACE_VOLMUSIC);
    psl->SetState(STATE_SHADOW);
    psl->SetLimit(0.0f, MAXVOLUME);
    psl->SetArrowStep(1.0f);
    pos.y += ddim.y;
    GetResource(RES_EVENT, EVENT_INTERFACE_VOLMUSIC, name);
    pl = pw->CreateLabel(pos, ddim, 0, EVENT_LABEL2, name);
    pl->SetTextAlign(Gfx::TEXT_ALIGN_LEFT);

    ddim.x = dim.x*3;
    ddim.y = dim.y*1;
    pos.x = ox+sx*10;
    pos.y = oy+sy*2;
    pb = pw->CreateButton(pos, ddim, -1, EVENT_INTERFACE_SILENT);
    pb->SetState(STATE_SHADOW);
    pos.x += ddim.x;
    pb = pw->CreateButton(pos, ddim, -1, EVENT_INTERFACE_NOISY);
    pb->SetState(STATE_SHADOW);

    UpdateSetupButtons();
}