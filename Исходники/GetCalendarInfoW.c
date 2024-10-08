int __cdecl main(int argc, char *argv[])
{
    int err;
    int index = 0;
    LCID Locale = LOCALE_USER_DEFAULT;
    CALID Calendar;
    CALTYPE CalType = CAL_ITWODIGITYEARMAX|CAL_RETURN_NUMBER;
    DWORD dwValue;
    char *CalendarID[]={"CAL_GREGORIAN",
                        "CAL_GREGORIAN_US",
                        "CAL_JAPAN",
                        "CAL_TAIWAN",
                        "CAL_KOREA",
                        "CAL_HIJRI",
                        "CAL_THAI",
                        "CAL_HEBREW",
                        "CAL_GREGORIAN_ME_FRENCH",
                        "CAL_GREGORIAN_ARABIC",
                        "CAL_GREGORIAN_XLIT_ENGLISH",
                        "CAL_GREGORIAN_XLIT_FRENCH",
                        "CAL_JULIAN"};
        
    char errBuffer[1024];               


    /*Initialize the PAL environment*/
    err = PAL_Initialize(argc, argv);
    if(0 != err)
    {
        return FAIL;
    }
    
    memset(errBuffer, 0, 1024);

    for(index=0; index<13; index++)
    {
        Calendar = index + 1;
        /*retrieve the specified calendar info*/
        err = GetCalendarInfoW(Locale,/*locale idendifier*/
                            Calendar, /*calendar identifier*/
                            CalType,  /*calendar tyope*/
                            NULL,     /*buffer to store the retreive info*/
                            0,        /*alwayse zero*/
                            &dwValue);/*to store the requrest data*/               
        if(0 == err)
        {
            strcat(errBuffer, CalendarID[index]);
            strcat(errBuffer, ", ");           
        }
    }


    if(strlen(errBuffer) > 0)
    {
        Fail("\nFailed to call GetCalendarInfoW API by passing %s"
             " Calendar identifier(s)\n",errBuffer);
    }
    

    PAL_Terminate();
    return PASS;
}