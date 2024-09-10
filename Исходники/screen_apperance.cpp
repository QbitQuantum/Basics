void CScreenApperance::CreateInterface()
{
    CWindow*        pw;
    CLabel*         pl;
    CButton*        pb;
    CColor*         pco;
    CSlider*        psl;
    Math::Point     pos, ddim;
    std::string     name;

    pos.x = 0.10f;
    pos.y = 0.10f;
    ddim.x = 0.80f;
    ddim.y = 0.80f;
    pw = m_interface->CreateWindows(pos, ddim, 12, EVENT_WINDOW5);
    GetResource(RES_TEXT, RT_TITLE_PERSO, name);
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

    pos.x  =  95.0f/640.0f;
    pos.y  = 108.0f/480.0f;
    ddim.x = 220.0f/640.0f;
    ddim.y = 274.0f/480.0f;
    pw->CreateGroup(pos, ddim, 17, EVENT_NULL);  // frame

    pos.x  = 100.0f/640.0f;
    pos.y  = 364.0f/480.0f;
    ddim.x = 210.0f/640.0f;
    ddim.y =  14.0f/480.0f;
    pw->CreateGroup(pos, ddim, 3, EVENT_NULL);  // transparent -> gray

    pos.x  = 120.0f/640.0f;
    pos.y  = 364.0f/480.0f;
    ddim.x =  80.0f/640.0f;
    ddim.y =  28.0f/480.0f;
    pb = pw->CreateButton(pos, ddim, -1, EVENT_INTERFACE_PHEAD);
    pb->SetState(STATE_SHADOW);
    pb->SetState(STATE_CARD);

    pos.x  = 210.0f/640.0f;
    pos.y  = 364.0f/480.0f;
    ddim.x =  80.0f/640.0f;
    ddim.y =  28.0f/480.0f;
    pb = pw->CreateButton(pos, ddim, -1, EVENT_INTERFACE_PBODY);
    pb->SetState(STATE_SHADOW);
    pb->SetState(STATE_CARD);

    pos.x  = 100.0f/640.0f;
    pos.y  = 354.0f/480.0f;
    ddim.x = 210.0f/640.0f;
    ddim.y =  10.0f/480.0f;
    pw->CreateGroup(pos, ddim, 1, EVENT_INTERFACE_GLINTb);  // orange bar
    pos.x  = 100.0f/640.0f;
    pos.y  = 154.0f/480.0f;
    ddim.x = 210.0f/640.0f;
    ddim.y = 200.0f/480.0f;
    pw->CreateGroup(pos, ddim, 2, EVENT_INTERFACE_GLINTu);  // orange -> transparent

    // Face
    pos.x  = 340.0f/640.0f;
    pos.y  = 356.0f/480.0f;
    ddim.x = 200.0f/640.0f;
    ddim.y =  16.0f/480.0f;
    pl = pw->CreateLabel(pos, ddim, 0, EVENT_LABEL11, "");
    pl->SetTextAlign(Gfx::TEXT_ALIGN_LEFT);

    pos.x  = 340.0f/640.0f;
    pos.y  = 312.0f/480.0f;
    ddim.x =  44.0f/640.0f;
    ddim.y =  44.0f/480.0f;
    pb = pw->CreateButton(pos, ddim, 43, EVENT_INTERFACE_PFACE1);
    pb->SetState(STATE_SHADOW);
    pos.x += 50.0f/640.0f;
    pb = pw->CreateButton(pos, ddim, 46, EVENT_INTERFACE_PFACE4);
    pb->SetState(STATE_SHADOW);
    pos.x += 50.0f/640.0f;
    pb = pw->CreateButton(pos, ddim, 45, EVENT_INTERFACE_PFACE3);
    pb->SetState(STATE_SHADOW);
    pos.x += 50.0f/640.0f;
    pb = pw->CreateButton(pos, ddim, 44, EVENT_INTERFACE_PFACE2);
    pb->SetState(STATE_SHADOW);

    // Glasses
    pos.x  = 340.0f/640.0f;
    pos.y  = 270.0f/480.0f;
    ddim.x = 200.0f/640.0f;
    ddim.y =  16.0f/480.0f;
    pl = pw->CreateLabel(pos, ddim, 0, EVENT_LABEL12, "");
    pl->SetTextAlign(Gfx::TEXT_ALIGN_LEFT);

    pos.x  = 340.0f/640.0f;
    pos.y  = 240.0f/480.0f;
    ddim.x =  30.0f/640.0f;
    ddim.y =  30.0f/480.0f;
    for ( int i=0 ; i<6 ; i++ )
    {
        int ti[6] = {11, 179, 180, 181, 182, 183};
        pb = pw->CreateButton(pos, ddim, ti[i], static_cast<EventType>(EVENT_INTERFACE_PGLASS0+i));
        pb->SetState(STATE_SHADOW);
        pos.x += (30.0f+2.8f)/640.0f;
    }

    // Color A
    pos.x  = 340.0f/640.0f;
    pos.y  = 300.0f/480.0f;
    ddim.x = 200.0f/640.0f;
    ddim.y =  16.0f/480.0f;
    pl = pw->CreateLabel(pos, ddim, 0, EVENT_LABEL14, "");
    pl->SetTextAlign(Gfx::TEXT_ALIGN_LEFT);

    pos.y  = 282.0f/480.0f;
    ddim.x =  18.0f/640.0f;
    ddim.y =  18.0f/480.0f;
    for ( int j=0 ; j<3 ; j++ )
    {
        pos.x  = 340.0f/640.0f;
        for ( int i=0 ; i<3 ; i++ )
        {
            pco = pw->CreateColor(pos, ddim, -1, static_cast<EventType>(EVENT_INTERFACE_PC0a+j*3+i));
            pco->SetState(STATE_SHADOW);
            pos.x += 20.0f/640.0f;
        }
        pos.y -= 20.0f/480.0f;
    }

    pos.x  = 420.0f/640.0f;
    pos.y  = 282.0f/480.0f;
    ddim.x = 100.0f/640.0f;
    ddim.y =  18.0f/480.0f;
    for ( int i=0 ; i<3 ; i++ )
    {
        psl = pw->CreateSlider(pos, ddim, 0, static_cast<EventType>(EVENT_INTERFACE_PCRa+i));
        psl->SetState(STATE_SHADOW);
        psl->SetLimit(0.0f, 255.0f);
        psl->SetArrowStep(16.0f);
        pos.y -= 20.0f/480.0f;
    }

    // Color B
    pos.x  = 340.0f/640.0f;
    pos.y  = 192.0f/480.0f;
    ddim.x = 200.0f/640.0f;
    ddim.y =  16.0f/480.0f;
    pl = pw->CreateLabel(pos, ddim, 0, EVENT_LABEL13, "");
    pl->SetTextAlign(Gfx::TEXT_ALIGN_LEFT);

    pos.y  = 174.0f/480.0f;
    ddim.x =  18.0f/640.0f;
    ddim.y =  18.0f/480.0f;
    for ( int j=0 ; j<3 ; j++ )
    {
        pos.x  = 340.0f/640.0f;
        for ( int i=0 ; i<3 ; i++ )
        {
            pco = pw->CreateColor(pos, ddim, -1, static_cast<EventType>(EVENT_INTERFACE_PC0b+j*3+i));
            pco->SetState(STATE_SHADOW);
            pos.x += 20.0f/640.0f;
        }
        pos.y -= 20.0f/480.0f;
    }

    pos.x  = 420.0f/640.0f;
    pos.y  = 174.0f/480.0f;
    ddim.x = 100.0f/640.0f;
    ddim.y =  18.0f/480.0f;
    for ( int i=0 ; i<3 ; i++ )
    {
        psl = pw->CreateSlider(pos, ddim, 0, static_cast<EventType>(EVENT_INTERFACE_PCRb+i));
        psl->SetState(STATE_SHADOW);
        psl->SetLimit(0.0f, 255.0f);
        psl->SetArrowStep(16.0f);
        pos.y -= 20.0f/480.0f;
    }

    // Rotation
    pos.x  = 100.0f/640.0f;
    pos.y  = 113.0f/480.0f;
    ddim.x =  20.0f/640.0f;
    ddim.y =  20.0f/480.0f;
    pb = pw->CreateButton(pos, ddim, 55, EVENT_INTERFACE_PLROT);  // <
    pb->SetState(STATE_SHADOW);
    pb->SetRepeat(true);

    pos.x  = 290.0f/640.0f;
    pos.y  = 113.0f/480.0f;
    ddim.x =  20.0f/640.0f;
    ddim.y =  20.0f/480.0f;
    pb = pw->CreateButton(pos, ddim, 48, EVENT_INTERFACE_PRROT);  // >
    pb->SetState(STATE_SHADOW);
    pb->SetRepeat(true);

    pos.x  = 100.0f/640.0f;
    pos.y  =  70.0f/480.0f;
    ddim.x = 100.0f/640.0f;
    ddim.y =  32.0f/480.0f;
    pb = pw->CreateButton(pos, ddim, -1, EVENT_INTERFACE_POK);
    pb->SetState(STATE_SHADOW);

    pos.x = 210.0f/640.0f;
    pos.y =  70.0f/480.0f;
    ddim.x =100.0f/640.0f;
    ddim.y = 32.0f/480.0f;
    pb = pw->CreateButton(pos, ddim, -1, EVENT_INTERFACE_PCANCEL);
    pb->SetState(STATE_SHADOW);

    pos.x = 340.0f/640.0f;
    pos.y =  70.0f/480.0f;
    ddim.x =194.0f/640.0f;
    ddim.y = 32.0f/480.0f;
    pb = pw->CreateButton(pos, ddim, -1, EVENT_INTERFACE_PDEF);
    pb->SetState(STATE_SHADOW);

    m_apperanceTab = 0;
    m_apperanceAngle = -0.6f;
    m_main->GetPlayerProfile()->LoadApperance();
    UpdatePerso();
    m_main->ScenePerso();
    CameraPerso();
}