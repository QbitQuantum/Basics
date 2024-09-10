Boolean IsChangedAddressDB()
{
    return !((MemCmp((char*) &gAdcdate, gPrefsR.adrcdate, 4) == 0) &&
            (MemCmp((char*) &gAdmdate, gPrefsR.adrmdate, 4) == 0));
}