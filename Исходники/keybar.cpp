void KeyBar::ReadRegGroup(const wchar_t *RegGroup, const wchar_t *Language)
{
	if (!RegReaded || StrCmpI(strLanguage,Language) || StrCmpI(strRegGroupName,RegGroup))
	{
		DWORD Index=0;
		string strRegName;
		string strValue;
		string strValueName;

		strLanguage=Language;
		strRegGroupName=RegGroup;
		strRegName=L"KeyBarLabels.";
		strRegName+=strLanguage;
		strRegName+=L".";
		strRegName+=RegGroup;

		ClearKeyTitles(true);

		while (GeneralCfg->EnumValues(strRegName,Index++,strValueName,strValue))
		{
			DWORD Key=KeyNameToKey(strValueName);
			DWORD Key0=Key&(~KEY_CTRLMASK);
			DWORD Ctrl=Key&KEY_CTRLMASK;

			if (Key0 >= KEY_F1 && Key0 <= KEY_F24)
			{
				size_t J;
				static DWORD Area[][2]=
				{
					{ KBL_MAIN,         0 },
					{ KBL_SHIFT,        KEY_SHIFT },
					{ KBL_CTRL,         KEY_CTRL },
					{ KBL_ALT,          KEY_ALT },
					{ KBL_CTRLSHIFT,    KEY_CTRL|KEY_SHIFT },
					{ KBL_ALTSHIFT,     KEY_ALT|KEY_SHIFT },
					{ KBL_CTRLALT,      KEY_CTRL|KEY_ALT },
					{ KBL_CTRLALTSHIFT, KEY_CTRL|KEY_ALT|KEY_SHIFT },
				};

				for (J=0; J < ARRAYSIZE(Area); ++J)
					if (Area[J][1] == Ctrl)
						break;

				if (J <= ARRAYSIZE(Area))
				{
					KeyTitlesCustom[Area[J][0]][Key0-KEY_F1]=xf_wcsdup(strValue.CPtr());
				}
			}
		}

		RegReaded=TRUE;
	}
}