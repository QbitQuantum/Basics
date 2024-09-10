void JoinNetworkGame(void)
{
  //  _pGame->gm_MenuSplitScreenCfg = (enum CGame::SplitScreenCfg) mgSplitScreenCfg.mg_iSelected;
  _pGame->gm_StartSplitScreenCfg = _pGame->gm_MenuSplitScreenCfg;

  _pGame->gm_aiStartLocalPlayers[0] = _pGame->gm_aiMenuLocalPlayers[0];
  _pGame->gm_aiStartLocalPlayers[1] = _pGame->gm_aiMenuLocalPlayers[1];
  _pGame->gm_aiStartLocalPlayers[2] = _pGame->gm_aiMenuLocalPlayers[2];
  _pGame->gm_aiStartLocalPlayers[3] = _pGame->gm_aiMenuLocalPlayers[3];

  _pGame->gm_strNetworkProvider = "TCP/IP Client";
  if (_pGame->JoinGame(CNetworkSession(_pGame->gam_strJoinAddress)))
  {
    StopMenus();
    _gmRunningGameMode = GM_NETWORK;
  } else {
    if (_pNetwork->ga_strRequiredMod != "") {
      extern CTFileName _fnmModToLoad;
      extern CTString _strModServerJoin;
      char strModName[256] = { 0 };
      char strModURL[256] = { 0 };
      _pNetwork->ga_strRequiredMod.ScanF("%250[^\\]\\%s", &strModName, &strModURL);
      _fnmModSelected = CTString(strModName);
      _strModURLSelected = strModURL;
      if (_strModURLSelected = "") {
        _strModURLSelected = "http://www.croteam.com/mods/Old";
      }
      _strModServerSelected.PrintF("%s:%s", _pGame->gam_strJoinAddress, _pShell->GetValue("net_iPort"));
      extern void ModConnectConfirm(void);
      ModConnectConfirm();
    }
    _gmRunningGameMode = GM_NONE;
  }
}