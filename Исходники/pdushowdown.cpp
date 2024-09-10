void PDUShowdown::execute(Base::GameState*)
{
  CTableView* pView = CTableView::Instance();

  if (pView)
  {
    Player* pPlayer = pView->getPlayer(player_);
    if (pPlayer)
    {
      if (num_cards_ == 0)
      { //
        // Player mucks hand - do muck hand animation
        // unless its the local player
        //
        if (!pView->isLocalPlayer(player_))
        {
          pView->InvalidateRect(pPlayer->getCardPaintArea(Player::AllCards));
          pPlayer->empty();
          GameLogic::Instance().setNextState(
              new StateShowdown(player_, pPlayer->numCards()));
        }
      }
      else
      { //
        // Show player's cards
        //
        pView->InvalidateRect(pPlayer->getCardPaintArea(Player::AllCards));
        CardEntry* pC = pCards_;
        for (int i = 0; i < num_cards_; i++, pC++)
          pPlayer->setCard(i, Card((Base::Suit)pC->suit_, pC->value_));
        pPlayer->setShowAll(TRUE);
      }

      pView->InvalidateRect(
        pPlayer->getCardPaintArea(Player::AllCards));

      if (message_)
        pPlayer->setActionText(message_);
      else
        pPlayer->setActionText("");
    }
  }
}