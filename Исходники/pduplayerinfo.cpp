void PDUPlayerInfo::execute(GameState*)
{
  CString msg;
  CTableView* pTable = CTableView::Instance();
  ASSERT(pTable);
  CChatView* pChat = CChatView::Instance();
  int num_players_b4_pdu = pTable->numPlayers();

  if (pTable)
  {
    int num_players = num_players_b4_pdu;

    PlayerInfo* pP = pPlayers_;
    if (pP != NULL)
    {
      for (int i = 0; i < num_players_; i++)
      {
        CString namesz = MakeString(pP->username_);
        Player* p = pTable->getPlayer(pP->slot_);
        bool wasThere = false;
        if (p && p->getName() == namesz)
          wasThere = true;

        pTable->addPlayer(namesz, CChips_n(pP->chips_).ntohl(), pP->slot_);

        // Set initial player state
        if (pP->state_ & PLAYER_STATE_ACTIVE)
          pTable->setState(pP->slot_, Base::SitIn);
        else
          pTable->setState(pP->slot_, Base::SitOut);

        Player* pPlayer = pTable->getPlayer(pP->slot_);

        ASSERT(pPlayer);
        if (pPlayer)
        {
          if (pP->state_ & PLAYER_STATE_ZOMBIE)
            pPlayer->setState(Base::Zombie);

          CString citysz = MakeString(pP->city_);
          pPlayer->setHomeCity(citysz);
          pTable->InvalidateRect(&pPlayer->getArea());  
        }

        if (pChat && !wasThere)
        {
          CString msg;
          msg.Format(g_szPlayerJoined, (LPCSTR)namesz, pP->slot_ + 1);
          pChat->addDealerMessage(msg, CChatView::CF_GameNormal);
        }
        
        pP++;
      }
    }

    // make a full redraw if original player
    // count was 0
    if (num_players == 0)
      pTable->Invalidate();
  }

  if (num_players_b4_pdu == 0)
  {
    // Send initial sit in status
    BOOL b = GameLogic::SitOut();
    if (Global::TableServer())
    {
      if (b)
        Global::TableServer()->sendPlaySitOutPDU();
      else
        Global::TableServer()->sendPlaySitInPDU();
    }

    // Send initial muck hand status
    b = GameLogic::HideHand();
    if (Global::TableServer())
    {
      if (b)
        Global::TableServer()->sendPlayHideCardsPDU();
      else
        Global::TableServer()->sendPlayShowCardsPDU();
    }

    // Done, start waiting for new hand to start
    GameLogic::Instance().setNextState(new StateWait());
  }
}