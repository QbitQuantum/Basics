	virtual void SaveValue(FarDialogItem *Item, int RadioGroupIndex)
	{
		const wchar_t *DataPtr = (const wchar_t *) Info.SendDlgMessage(*DialogHandle, DM_GETCONSTTEXTPTR, ID, 0);
		lstrcpynW(Value, DataPtr, MaxSize);
	}