bool Announcer::ToMirc(wstring service, wstring channels, wstring data, int mode, BOOL use_action, BOOL multi_server) {
  if (!FindWindow(L"mIRC", NULL)) return FALSE;
  if (service.empty() || channels.empty() || data.empty()) return FALSE;

  // Initialize
  DynamicDataExchange DDE;
  if (!DDE.Initialize(/*APPCLASS_STANDARD | APPCMD_CLIENTONLY, TRUE*/)) {
    win32::TaskDialog dlg(L"Announce to mIRC", TD_ICON_ERROR);
    dlg.SetMainInstruction(L"DDE initialization failed.");
    dlg.AddButton(L"OK", IDOK);
    dlg.Show(g_hMain);
    return false;
  }

  // List channels
  if (mode != MIRC_CHANNELMODE_CUSTOM) {
    if (DDE.Connect(service, L"CHANNELS")) {
      DDE.ClientTransaction(L" ", L"", &channels, XTYP_REQUEST);
      DDE.Disconnect();
    }
  }
  vector<wstring> channel_list;
  Tokenize(channels, L" ,;", channel_list);
  for (size_t i = 0; i < channel_list.size(); i++) {
    Trim(channel_list[i]);
    if (channel_list[i].empty()) {
      continue;
    }
    if (channel_list[i].at(0) == '*') {
      channel_list[i] = channel_list[i].substr(1);
      if (mode == MIRC_CHANNELMODE_ACTIVE) {
        wstring temp = channel_list[i];
        channel_list.clear();
        channel_list.push_back(temp);
        break;
      }
    }
    if (channel_list[i].at(0) != '#') {
      channel_list[i].insert(channel_list[i].begin(), '#');
    }
  }

  // Connect
  if (!DDE.Connect(service, L"COMMAND")) {
    win32::TaskDialog dlg(L"Announce to mIRC", TD_ICON_ERROR);
    dlg.SetMainInstruction(L"DDE connection failed.");
    dlg.SetContent(L"Please enable DDE server from mIRC Options > Other > DDE.");
    dlg.AddButton(L"OK", IDOK);
    dlg.Show(g_hMain);
    DDE.UnInitialize();
    return false;
  }
  
  // Send message to channels
  for (size_t i = 0; i < channel_list.size(); i++) {
    wstring message;
    message += multi_server ? L"/scon -a " : L"";
    message += use_action ? L"/describe " : L"/msg ";
    message += channel_list[i] + L" " + data;
    DDE.ClientTransaction(L" ", message, NULL, XTYP_POKE);
  }

  // Clean up
  DDE.Disconnect();
  DDE.UnInitialize();
  return true;
}