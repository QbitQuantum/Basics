static pascal OSStatus DBClientDataCallback (HIViewRef browser, DataBrowserItemID itemID, DataBrowserPropertyID property, DataBrowserItemDataRef itemData, Boolean changeValue)
{
	OSStatus 	err, result;
	CFStringRef	str;
	Boolean		r;
	uint32		address;
	uint8		value;
	char		code[256];

	result = noErr;

	switch (property)
	{
		case kCmCheckBox:
			ThemeButtonValue	buttonValue;

            if (changeValue)
			{
				err = GetDataBrowserItemDataButtonValue(itemData, &buttonValue);
				citem[itemID - 1].enabled = (buttonValue == kThemeButtonOn) ? true : false;
 	        }
			else
				err = SetDataBrowserItemDataButtonValue(itemData, citem[itemID - 1].enabled ? kThemeButtonOn : kThemeButtonOff);

			break;

		case kCmAddress:
			if (changeValue)
			{
				err = GetDataBrowserItemDataText(itemData, &str);
				r = CFStringGetCString(str, code, 256, CFStringGetSystemEncoding());
				CFRelease(str);
				if (r)
				{
					Boolean	translated;

					if (S9xProActionReplayToRaw(code, address, value) == NULL)
						translated = true;
					else
					if (S9xGameGenieToRaw(code, address, value) == NULL)
						translated = true;
					else
					{
						translated = false;
						if (sscanf(code, "%" SCNx32, &address) != 1)
							address = 0;
						else
							address &= 0xFFFFFF;
					}

					citem[itemID - 1].address = address;
					sprintf(code, "%06" PRIX32, address);
					str = CFStringCreateWithCString(kCFAllocatorDefault, code, CFStringGetSystemEncoding());
					err = SetDataBrowserItemDataText(itemData, str);
					CFRelease(str);

					if (translated)
					{
						DataBrowserItemID	id[1];

						citem[itemID - 1].value = value;
						id[0] = itemID;
						err = UpdateDataBrowserItems(browser, kDataBrowserNoItem, 1, id, kDataBrowserItemNoProperty, kCmValue);
					}
				}
			}
			else
			{
				sprintf(code, "%06" PRIX32, citem[itemID - 1].address);
				str = CFStringCreateWithCString(kCFAllocatorDefault, code, CFStringGetSystemEncoding());
				err = SetDataBrowserItemDataText(itemData, str);
				CFRelease(str);
			}

			break;

		case kCmValue:
			if (changeValue)
			{
				err = GetDataBrowserItemDataText(itemData, &str);
				r = CFStringGetCString(str, code, 256, CFStringGetSystemEncoding());
				CFRelease(str);
				if (r)
				{
					uint32	byte;

					if (sscanf(code, "%" SCNx32, &byte) == 1)
						citem[itemID - 1].value = (uint8) byte;
					else
					{
						citem[itemID - 1].value = 0;
						err = SetDataBrowserItemDataText(itemData, CFSTR("00"));
					}
				}
			}
			else
			{
				sprintf(code, "%02" PRIX8, citem[itemID - 1].value);
				str = CFStringCreateWithCString(kCFAllocatorDefault, code, CFStringGetSystemEncoding());
				err = SetDataBrowserItemDataText(itemData, str);
				CFRelease(str);
			}

			break;

		case kCmDescription:
			if (changeValue)
			{
				code[0] = 0;
				err = GetDataBrowserItemDataText(itemData, &str);
				strcpy(code, GetMultiByteCharacters(str, 19));
				CFRelease(str);

				if (code[0] == 0)
				{
					code[0] = ' ';
					code[1] = 0;
				}

				strcpy(citem[itemID - 1].description, code);
			}
			else
			{
				str = CFStringCreateWithCString(kCFAllocatorDefault, citem[itemID - 1].description, CFStringGetSystemEncoding());
				err = SetDataBrowserItemDataText(itemData, str);
				CFRelease(str);
			}

			break;

		case kDataBrowserItemIsActiveProperty:
			err = SetDataBrowserItemDataBooleanValue(itemData, true);
			break;

		case kDataBrowserItemIsEditableProperty:
			err = SetDataBrowserItemDataBooleanValue(itemData, true);
			break;

		default:
			result = errDataBrowserPropertyNotSupported;
	}

	return (result);
}