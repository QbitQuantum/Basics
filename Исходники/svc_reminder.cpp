/**
 * This function checks all contacts.
 *
 * @param	notify			- notification type
 *
 * @return	nothing
 **/
VOID SvcReminderCheckAll(const ENotify notify)
{
    if (gRemindOpts.RemindState != REMIND_OFF)
    {
        HANDLE hContact;
        CEvent evt;
        MTime now;
        WORD a1 = 0;

        now.GetLocalTime();

        //walk through all the contacts stored in the DB
        for (hContact = DB::Contact::FindFirst();
                hContact != NULL;
                hContact = DB::Contact::FindNext(hContact))
        {
            CheckContact(hContact, now, evt, notify != NOTIFY_CLIST, &a1);
        }

        if (notify != NOTIFY_CLIST)
        {
            // play sound for the next anniversary
            NotifyWithSound(evt);

            // popup anniversary list
            if (DB::Setting::GetByte(SET_ANNIVLIST_POPUP, FALSE))
            {
                DlgAnniversaryListShow(0, 0);
            }

            if (evt._wDaysLeft > gRemindOpts.wDaysEarlier && notify == NOTIFY_NOANNIV)
            {
                NotifyWithPopup(NULL, CEvent::NONE, 0, NULL, TranslateT("No anniversaries to remind of"));
            }
        }
        UpdateTimer(FALSE);
    }
}