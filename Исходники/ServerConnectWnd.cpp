ServerConnectWnd::ServerConnectWnd() : 
    CUIWnd(UserString("SCONNECT_WINDOW_TITLE"),
           (GG::GUI::GetGUI()->AppWidth() - WINDOW_WIDTH) / 2, (GG::GUI::GetGUI()->AppHeight() - WINDOW_HEIGHT) / 2,
           WINDOW_WIDTH, WINDOW_HEIGHT, GG::INTERACTIVE | GG::MODAL),
    m_host_or_join_radio_group(0),
    m_LAN_game_label(0),
    m_servers_lb(0),
    m_find_LAN_servers_bn(0),
    m_internet_game_label(0),
    m_IP_address_edit(0),
    m_player_name_edit(0),
    m_ok_bn(0),
    m_cancel_bn(0)
{
    Sound::TempUISoundDisabler sound_disabler;

    boost::shared_ptr<GG::Font> font = ClientUI::GetFont();
    GG::TextControl* player_name_label = new GG::TextControl(GG::X0, GG::Y0, GG::X1, GG::Y1, UserString("PLAYER_NAME_LABEL"), font, ClientUI::TextColor(), GG::FORMAT_LEFT);
    m_player_name_edit = new CUIEdit(GG::X0, GG::Y0, GG::X1, GetOptionsDB().Get<std::string>("multiplayersetup.player-name"));
    m_host_or_join_radio_group = new GG::RadioButtonGroup(GG::X0, GG::Y0, GG::X1, GG::Y1, GG::VERTICAL);
    m_host_or_join_radio_group->AddButton(new CUIStateButton(UserString("HOST_GAME_BN"), GG::X0, GG::Y0, GG::X1, GG::Y1, GG::FORMAT_LEFT, GG::SBSTYLE_3D_RADIO));
    m_host_or_join_radio_group->AddButton(new CUIStateButton(UserString("JOIN_GAME_BN"), GG::X0, GG::Y0, GG::X1, GG::Y1, GG::FORMAT_LEFT, GG::SBSTYLE_3D_RADIO));
    m_LAN_game_label = new GG::TextControl(GG::X0, GG::Y0, UserString("LAN_GAME_LABEL"), font, ClientUI::TextColor(), GG::FORMAT_LEFT);
    m_servers_lb = new CUIListBox(GG::X0, GG::Y0, GG::X1, GG::Y1);
    m_servers_lb->SetStyle(GG::LIST_NOSORT | GG::LIST_SINGLESEL);
    m_find_LAN_servers_bn = new CUIButton(UserString("REFRESH_LIST_BN"));
    m_internet_game_label = new GG::TextControl(GG::X0, GG::Y0, UserString("INTERNET_GAME_LABEL"), font, ClientUI::TextColor(), GG::FORMAT_LEFT);
    m_IP_address_edit = new CUIEdit(GG::X0, GG::Y0, GG::X1, GetOptionsDB().Get<std::string>("multiplayersetup.host-address"));
    m_ok_bn = new CUIButton(UserString("OK"));
    m_cancel_bn = new CUIButton(UserString("CANCEL"));

    const GG::X OK_CANCEL_BUTTON_WIDTH(80);
    const int CONTROL_MARGIN = 5;

    GG::Layout* layout = new GG::Layout(GG::X0, GG::Y0, GG::X1, GG::Y1, 8, 4, CONTROL_MARGIN);
    layout->SetMinimumColumnWidth(0, player_name_label->MinUsableSize().x + CONTROL_MARGIN);
    layout->SetColumnStretch(1, 1.0);
    layout->SetMinimumColumnWidth(2, OK_CANCEL_BUTTON_WIDTH + CONTROL_MARGIN);
    layout->SetMinimumColumnWidth(3, OK_CANCEL_BUTTON_WIDTH + CONTROL_MARGIN);
    layout->SetMinimumRowHeight(0, m_player_name_edit->Height() + CONTROL_MARGIN);
    layout->SetMinimumRowHeight(1, m_host_or_join_radio_group->MinUsableSize().y);
    layout->SetMinimumRowHeight(2, m_LAN_game_label->Height() + (2 * CONTROL_MARGIN));
    layout->SetRowStretch(3, 1.0);
    layout->SetMinimumRowHeight(4, m_find_LAN_servers_bn->Height() + CONTROL_MARGIN);
    layout->SetMinimumRowHeight(5, m_internet_game_label->Height() + CONTROL_MARGIN);
    layout->SetMinimumRowHeight(6, m_IP_address_edit->Height() + CONTROL_MARGIN);
    layout->SetMinimumRowHeight(7, m_ok_bn->Height() + CONTROL_MARGIN);

    layout->Add(player_name_label, 0, 0, 1, 1, GG::ALIGN_VCENTER);
    layout->Add(m_player_name_edit, 0, 1, 1, 3, GG::ALIGN_VCENTER);
    layout->Add(m_host_or_join_radio_group, 1, 0, 1, 4);
    layout->Add(m_LAN_game_label, 2, 0, 1, 4, GG::ALIGN_BOTTOM);
    layout->Add(m_servers_lb, 3, 0, 1, 4);
    layout->Add(m_find_LAN_servers_bn, 4, 3);
    layout->Add(m_internet_game_label, 5, 0, 1, 4);
    layout->Add(m_IP_address_edit, 6, 0, 1, 4);
    layout->Add(m_ok_bn, 7, 2);
    layout->Add(m_cancel_bn, 7, 3);

    SetLayout(layout);

    m_LAN_servers = HumanClientApp::GetApp()->Networking().DiscoverLANServers();
    Init();
}