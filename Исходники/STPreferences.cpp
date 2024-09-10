void CSTPreferences::SaveSettingL(RFile& aFile, const TDesC8& aSettingName, const TDesC& aSettingValue)
{
	aFile.Write(aSettingName);
	aFile.Write(KLit8Colon);
	
	
	HBufC8* encodedSettingValue = ConvertToUtf8L(aSettingValue);
	if (encodedSettingValue)
	{
		CleanupStack::PushL(encodedSettingValue);
		
		TBuf8<16> settingLength;
		settingLength.Num(encodedSettingValue->Length());
		aFile.Write(settingLength);
		
		aFile.Write(KLit8EqualSign);
		aFile.Write(*encodedSettingValue);
		CleanupStack::PopAndDestroy(); // encodedSettingValue
	}
	else
	{
		_LIT8(KLit8Unset, "0=");
		aFile.Write(KLit8Unset);
	}
	
	aFile.Write(KLit8EndLine);
}