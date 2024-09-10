void MarketMakerDlg::FillLevel1()
{
    CString str;
    char num[33];
    switch(B_GetBidTickStatus(m_level1))
    {
        case NOTICK:
        str = "NO";
        break;

        case UPTICK:
        str = "UP";
        break;

        case DOWNTICK:
        str = "DOWN";
        break;
    }
	m_l1BidTick.SetWindowText(str);

	_i64toa_s(B_GetVolume(m_level1), num, sizeof(num), 10);
	m_l1Volume.SetWindowText(num);
    
    CTime t(B_GetLastTradeTime(m_level1));
    m_l1Time.SetWindowText(t.Format("%H:%M:%S"));
	
	_ultoa_s(B_GetLastTrade(m_level1).GetSize(), num, sizeof(num), 10);
    m_l1Size.SetWindowText(num);

    str = "";
    ExtFrame::FormatMoney(str, B_GetOpenPrice(m_level1));
	m_l1Open.SetWindowText(str);

    str = "";
    ExtFrame::FormatMoney(str, B_GetNetChange(m_level1));
	m_l1Net.SetWindowText(str);

    str = "";
    ExtFrame::FormatMoney(str, B_GetIntraDayLow(m_level1));
	m_l1Lo.SetWindowText(str);

    str = "";
    ExtFrame::FormatMoney(str, B_GetLastTrade(m_level1));
	m_l1Last.SetWindowText(str);

    str = "";
    ExtFrame::FormatMoney(str, B_GetIntraDayHigh(m_level1));
	m_l1Hi.SetWindowText(str);

    str = "";
    ExtFrame::FormatMoney(str, B_GetClosePrice(m_level1));
	m_l1Close.SetWindowText(str);

	_ultoa_s(B_GetBid(m_level1).GetSize(), num, sizeof(num), 10);
    str = num;
    str += "x";
	_ultoa_s(B_GetAsk(m_level1).GetSize(), num, sizeof(num), 10);
    str += num;
    m_l1BXA.SetWindowText(str);
}