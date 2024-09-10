void PDUCommunityCard::execute(Base::GameState*)
{
  // Note: the StateDealCommunity is not used since
  // if a new community card pdu is received while a
  // StateDealCommunity is active then the previous
  // community card is lost. Instead, this PDU puts
  // the card directly to the community player.
    
  CTableView* pView = CTableView::Instance();
  ASSERT_VALID(pView);

  if (pView)
  {

    // Tell the current state to quit animations if any
    GameState* state = GameLogic::Instance().currentState();
    if (state)
      state->onCommand(MAKEWPARAM(ID_STOPANIMATION, 0), 0);

    pView->endBettingRound();

    // Update the screen now to make sure whatever we
    // were doing becomes visible
    pView->UpdateWindow();

    Player* pCommunity = pView->getCommunity();
    ASSERT(pCommunity);

    if (pCommunity)
    { // Add card directly to community's deck
      Card card(suit_, card_);
      pCommunity->addCard(card);

      SndMan::Instance()->playSound(SndMan::SM_Card2);

      if (msecs_ > 0)
      {
        // Do the "flip" animation to show the card
        CPoint pos = pCommunity->getCardPos(Player::LastCard);
        Cards::Instance().startFlip(card, pos);
        CDC* pDC = pView->GetDC();
        if (pDC)
        {
          Cards::Instance().flip(pDC, card, pos);
          pView->ReleaseDC(pDC);
        }
      }
      else
      {
        // Just repaint it once
        pView->InvalidateRect(pCommunity->getCardPaintArea(Player::LastCard));
      }

      ShowCommunityCardMessage(pCommunity);
    }
  }  
}