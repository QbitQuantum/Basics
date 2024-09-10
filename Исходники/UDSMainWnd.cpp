CString CUDSMainWnd::initialEval(CString Data2Send )
{
    int CService;
    CService = strtol(CurrentService, NULL, 16);
    if ( CService==0x10 || CService==0x11 ||CService==0x28 ||CService==0x31 ||CService==0x3E ||CService==0x85 ||CService==0xA0)
    {
        CString SendingData = Data2Send;
        //SendingData.Replace(" ",""); //added by Alejandra - not working
        SendingData.Remove(' '); // added in adition to previos function not working
        SendingData = Data2Send.Right(Data2Send.GetLength() - NO_OF_CHAR_IN_BYTE);

        int pos;

        pos = SendingData.Find('8', 0);

        //CString SecondByte = SendingData.Left(1);         //added by Alejandra - not working
        if(pos == 1) //initial if(SecondByte == '8')
        {
            Font_Color = RGB(0,255,0 );
            return "     No Response Required";
        }
    }
    Font_Color = RGB(184,134,11 );
    return "     No Response Received";        // If it's the case of  No Positive Response Required return the default value
}