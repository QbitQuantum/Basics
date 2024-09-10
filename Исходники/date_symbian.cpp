datetime_t TimePackToRel(const datepack_t *tp, bool_t Local)
{
    TDateTime Date;
    TTime ot;
	if (!tp) return INVALID_DATETIME_T;
    Date.SetYear(tp->Year);
    Date.SetMonth((TMonth)(tp->Month-1));
    Date.SetDay(tp->Day-1);
    Date.SetHour(tp->Hour);
    Date.SetMinute(tp->Minute);
    Date.SetSecond(tp->Second);

    ot = TTime(Date);

    if (Local) 
    {
#ifndef SYMBIAN90
        TLocale locale;
        TTimeIntervalSeconds universalTimeOffset(locale.UniversalTimeOffset());
        ot -= universalTimeOffset;
        if (locale.QueryHomeHasDaylightSavingOn())
        {
            TTimeIntervalHours daylightSaving(1);
            ot -= daylightSaving;
        }
#else
        RTz TzServer;
        if (TzServer.Connect()==KErrNone)
        {
            CTzConverter* Converter = CTzConverter::NewL(TzServer); 
            Converter->ConvertToUniversalTime(ot);
            delete Converter;
            TzServer.Close();
        }
#endif
    }

    return SymbianToDateTime(ot);
}