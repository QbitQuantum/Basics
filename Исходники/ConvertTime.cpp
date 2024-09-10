TInt CUnknownZoneTest::CreateAndRunTestUnitL()
{
    User::LeaveIfError(iTimeZoneServer.Connect());

    //
    // Initially set home zone to London
    //
    CTzId* tzId = CTzId::NewL(_L8("Europe/London"));
    CleanupStack::PushL(tzId);
    iTimeZoneServer.SetTimeZoneL(*tzId);

    //
    // Call SetUnknownZoneTime. Set the time to a winter time in Europe/London
    // to check that the previous time zone settings are overridden by the new
    // unknown zone settings.
    //
    TDateTime winterDateTime(2006,EJanuary,10,10,0,0,0); // 11-Jan-2006 10:00
    TTime localTime(winterDateTime);
    localTime.HomeTime();
    TInt offset = 120; // UTC+2
    iTimeZoneServer.SetUnknownZoneTimeL(localTime,offset);

    TTime utcTime(localTime);
    iTimeZoneServer.ConvertToUniversalTime(utcTime);

    TTimeIntervalMinutes diff;
    localTime.MinutesFrom(utcTime,diff);

    if (diff.Int() != offset)
    {
        ERR_PRINTF3(_L("Expected offset = %D, Retrieved offset = %D"),&offset,&diff);
        return KErrGeneral;
    }

    // convert back to local time and we should get the initial time again
    iTimeZoneServer.ConvertToLocalTime(utcTime);
    if (utcTime!=localTime)
    {
        ERR_PRINTF1(_L("ConvertToLocalTime failed"));
        return KErrGeneral;
    }

    //
    // Repeat again with a London summer time
    //

    // reset time zone to London
    iTimeZoneServer.SetTimeZoneL(*tzId);

    TDateTime summerDateTime(2006,EJune,10,10,0,0,0); // 11-June-2006 10:00

    localTime = summerDateTime;
    localTime.HomeTime();
    iTimeZoneServer.SetUnknownZoneTimeL(localTime,offset);

    utcTime = localTime;
    iTimeZoneServer.ConvertToUniversalTime(utcTime);

    localTime.MinutesFrom(utcTime,diff);

    if (diff.Int() != offset)
    {
        ERR_PRINTF3(_L("Expected offset = %D, Retrieved offset = %D"),&offset,&diff);
        return KErrGeneral;
    }

    // convert back to local time and we should get the initial time again
    iTimeZoneServer.ConvertToLocalTime(utcTime);
    if (utcTime!=localTime)
    {
        ERR_PRINTF1(_L("ConvertToLocalTime failed"));
        return KErrGeneral;
    }

    CleanupStack::PopAndDestroy(tzId);
    return KErrNone;
}