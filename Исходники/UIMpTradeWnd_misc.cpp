void CUIMpTradeWnd::UpdateMoneyIndicator()
{
	if(m_bIgnoreMoneyAndRank)
	{
		m_static_player_money->SetText	("---");
	}else
	{
		u32 _cost						= 0;
		string128						buff;
		sprintf_s							(buff, "%d", m_money);
		m_static_player_money->SetText	(buff);
		//update preset money
		for(u32 i=_preset_idx_last; i<=_preset_idx_3; ++i)
		{
			CUIStatic* st				= m_static_preset_money[i];
			_cost						= GetPresetCost((ETradePreset)i);
			sprintf_s						(buff, "%d", _cost);
			st->SetText					(buff);
			bool b_has_enought_money	= _cost<=GetMoneyAmount();
			u32 clr						= (b_has_enought_money)?m_text_color_money_positive:m_text_color_money_negative;
			st->SetTextColor			(clr);
			const preset_items&		v	=  GetPreset((ETradePreset)i);
			m_btns_preset[i]->Enable	(b_has_enought_money && v.size()!=0);
		}
	}

	if( !(Device.dwFrame%30) )
	{
		u32 _cost						= 0;
		string128						buff;
		StorePreset						(_preset_idx_temp, true, false, false);
		_cost							= GetPresetCost(_preset_idx_temp);
		sprintf_s							(buff, "%d", _cost);
		m_static_curr_items_money->SetText(buff);
	}
}