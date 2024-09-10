void far pascal zMapDialogRect( HWND pp1, LPRECT pp2 )
{

    SaveRegs();
    /*
    ** Log IN Parameters (No Create/Destroy Checking Yet!)
    */
    LogIn( (LPSTR)"APICALL:MapDialogRect HWND+LPRECT+",
        pp1, pp2 );

    /*
    ** Call the API!
    */
    RestoreRegs();
    GrovelDS();
    MapDialogRect(pp1,pp2);
    UnGrovelDS();
    SaveRegs();
    /*
    ** Log Return Code & OUT Parameters (No Create/Destroy Checking Yet!)
    */
    LogOut( (LPSTR)"APIRET:MapDialogRect +LPRECT+",
        (short)0, pp2 );

    RestoreRegs();
    return;
}