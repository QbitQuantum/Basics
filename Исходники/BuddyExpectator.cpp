void CALLBACK TimerProc(HWND, UINT, UINT_PTR, DWORD)
{
	for (auto &hContact : Contacts()) {
		char *proto = GetContactProto(hContact);
		if (proto && (db_get_b(hContact, proto, "ChatRoom", 0) == 0) && (CallProtoService(proto, PS_GETCAPS, PFLAGNUM_1, 0) & PF1_IMSEND) && isContactGoneFor(hContact, options.iAbsencePeriod2) && (db_get_b(hContact, MODULENAME, "StillAbsentNotified", 0) == 0))
		{
			db_set_b(hContact, MODULENAME, "StillAbsentNotified", 1);
			Skin_PlaySound("buddyExpectatorStillAbsent");

			wchar_t* message = TranslateT("has not returned after a long absence.");
			time_t tmpTime;
			wchar_t tmpBuf[251] = { 0 };
			tmpTime = getLastSeen(hContact);
			if (tmpTime != -1)
			{
				wcsftime(tmpBuf, 250, TranslateT("has not returned after being absent since %#x"), gmtime(&tmpTime));
				message = tmpBuf;
			}
			else
			{
				tmpTime = getLastInputMsg(hContact);
				if (tmpTime != -1)
				{
					wcsftime(tmpBuf, 250, TranslateT("has not returned after being absent since %#x"), gmtime(&tmpTime));
					message = tmpBuf;
				}
			}

			GoneNotify(hContact, message);
		}
	}
}