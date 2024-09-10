TBool CDataWrapperBase::GetRectFromConfig(const TDesC& aSectName, const TDesC& aKeyName, TRect& aResult)
	{
	TBuf<KMaxTestExecuteCommandLength>	tempStore;

	TInt	top;
	tempStore.Format(KFormatEntryField, &aKeyName, &KTagRectTop);
	TBool	ret=GetIntFromConfig(aSectName, tempStore, top);

	TInt	left;
	tempStore.Format(KFormatEntryField, &aKeyName, &KTagRectLeft);
	if ( !GetIntFromConfig(aSectName, tempStore, left) )
		{
		ret=EFalse;
		}

	TInt	bottom;
	tempStore.Format(KFormatEntryField, &aKeyName, &KTagRectBottom);
	if ( !GetIntFromConfig(aSectName, tempStore, bottom) )
		{
		ret=EFalse;
		}

	TInt	right;
	tempStore.Format(KFormatEntryField, &aKeyName, &KTagRectRight);
	if ( !GetIntFromConfig(aSectName, tempStore, right) )
		{
		ret=EFalse;
		}

	if ( ret )
		{
		aResult.SetRect(left, top, right, bottom);
		}

	return ret;
	}