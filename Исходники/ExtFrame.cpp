void ExtFrame::OnLevel1()
{
    const StockBase* stockHandle = B_GetStockHandle("AMD");
    CString str;
    if(B_IsStockValid(stockHandle))
    {
        char num[33];
        Observable* level1 = B_GetLevel1(stockHandle);
        str += "BidTick ";
        switch(B_GetBidTickStatus(level1))
        {
            case NOTICK:
            str += "NO";
            break;

            case UPTICK:
            str += "UP";
            break;

            case DOWNTICK:
            str += "DOWN";
            break;
        }

        str += "\nBid ";
        FormatMoneySize(str, B_GetBid(level1));

        str += "\nAsk ";
        FormatMoneySize(str, B_GetAsk(level1));
        
        str += "\nLastTrade ";
        FormatMoneySize(str, B_GetLastTrade(level1));
        
        str += "\nLastTradeTime ";
        CTime t(B_GetLastTradeTime(level1));
        str += t.Format("%H:%M:%S");
        
        str += "\nVolume ";
		_i64toa_s(B_GetVolume(level1), num, sizeof(num), 10);
        str += num;
        
        str += "\nOpen Price ";
        FormatMoney(str, B_GetOpenPrice(level1));

        str += "\nClose Price ";
        FormatMoney(str, B_GetClosePrice(level1));

        str += "\nHi Price ";
        FormatMoney(str, B_GetIntraDayHigh(level1));

        str += "\nLo Price ";
        FormatMoney(str, B_GetIntraDayLow(level1));

        str += "\nNet Change ";
        FormatMoney(str, B_GetNetChange(level1));
    }	
	else
    {
        str += "Stock is not loaded yet. Try again";
    }
    AfxGetMainWnd()->MessageBox(str, "INTC Level 1", MB_OK);
}