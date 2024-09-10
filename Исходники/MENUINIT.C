static void Init_MenuSlotNames(void)
{
    if (hMenuSlotNameIDs && lpMenuSNs)
    {
        GLOBALUNLOCK(hMenuSlotNameIDs);
        GlobalFree(hMenuSlotNameIDs);
    }

    hMenuSlotNameIDs = GLOBALALLOC(GHND, sizeof(MENU_SLOT_NAME_IDS));
    lpMenuSNs = (MENUSLOTNAMEIDS) GLOBALLOCK(hMenuSlotNameIDs);

    lpMenuSNs->idXSN = KppAddAtom(GetStringTable(IDS_X));
    lpMenuSNs->idYSN = KppAddAtom(GetStringTable(IDS_Y));
    lpMenuSNs->idSelectorsSN = KppAddAtom(GetStringTable(IDS_SELECTORS));
    lpMenuSNs->idSelectorTitlesSN =
    KppAddAtom(GetStringTable(IDS_SELECTORTITLES));
    lpMenuSNs->idCheckedSelectorsSN =
    KppAddAtom(GetStringTable(IDS_CHECKED));
    lpMenuSNs->idDisabledSelectorsSN =
    KppAddAtom(GetStringTable(IDS_DISABLED));
    lpMenuSNs->idDefaultMessageSN =
    KppAddAtom(GetStringTable(IDS_DEFAULTMESSAGE));
}