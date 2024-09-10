void CGameState::CaptureState() {
	bool				    playing = true;
	unsigned char		card = CARD_NOCARD;

	// figure out if I am playing
	int sym_chair = p_symbol_engine_userchair->userchair();
	if (!p_symbol_engine_userchair->userchair_confirmed()) 	{
		playing = false;
	}
	else if (!p_table_state->User()->HasKnownCards())	{
		playing = false;
	}

	// Poker window title
	char title[MAX_WINDOW_TITLE];
	GetWindowText(p_autoconnector->attached_hwnd(), title, MAX_WINDOW_TITLE);

	strncpy_s(state[state_index&0xff].m_title, 64, title, _TRUNCATE);
	state[state_index&0xff].m_title[63] = '\0';

	// Pot information
	for (int i=0; i<kMaxNumberOfPlayers; i++) {
		state[state_index&0xff].m_pot[i] = p_table_state->Pot(i);
  }
	// Common cards
	for (int i=0; i<kNumberOfCommunityCards; i++)	{
    int common_card = p_table_state->CommonCards(i)->GetValue();
    write_log(preferences.debug_dll_extension(), 
      "[CGameState] Common card %i = %i\n", i, common_card);
		state[state_index&0xff].m_cards[i] = common_card;
	}

	// playing, posting, dealerchair
	int sym_dealerchair = p_symbol_engine_dealerchair->dealerchair();
	bool sym_isautopost = p_symbol_engine_autoplayer->isautopost();
	state[state_index&0xff].m_is_playing = playing;
	state[state_index&0xff].m_is_posting = sym_isautopost;
	state[state_index&0xff].m_fillerbits = 0;
	state[state_index&0xff].m_fillerbyte = 0;
	state[state_index&0xff].m_dealer_chair = sym_dealerchair;

	// loop through all 10 player chairs
	for (int i=0; i<kMaxNumberOfPlayers; i++) {
    // player name, balance, currentbet
    strncpy_s(state[state_index&0xff].m_player[i].m_name, 16, p_table_state->Player(i)->name().GetString(), _TRUNCATE);
    state[state_index&0xff].m_player[i].m_balance = p_table_state->Player(i)->balance();
		state[state_index&0xff].m_player[i].m_currentbet = p_table_state->Player(i)->bet();

		// player cards
		for (int j=0; j<kNumberOfCardsPerPlayer; j++) {
      Card* player_card = p_table_state->Player(i)->hole_cards(j);
      int card = player_card->GetValue();
      write_log(preferences.debug_dll_extension(),
        "[CGameState] Player card [%i][%i] = %i\n", i, j, card);
			//!!!!!state[state_index&0xff].m_player[i].m_cards[j] = card;
		}

		// player name known, balance known
		state[state_index&0xff].m_player[i].m_name_known = p_scraper_access->IsGoodPlayername(i);
		state[state_index&0xff].m_player[i].m_balance_known = true;
		state[state_index&0xff].m_player[i].m_fillerbits = 0;
		state[state_index&0xff].m_player[i].m_fillerbyte = 0;
	}
  state_index++;
}