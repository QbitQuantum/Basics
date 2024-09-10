void XmlReport::createOSNode( ER_OPERATINGSYSTEM& outOS )
{
	OSVERSIONINFOA  oi = {};
	oi.dwOSVersionInfoSize = sizeof(oi);
	GetVersionExA(&oi);

	// 设置 MajorVersion 属性。
	outOS.MajorVersion = (int)oi.dwMajorVersion;

	// 设置 MinorVersion 属性。
	outOS.MinorVersion = (int)oi.dwMinorVersion;

	// 设置 BuildNumber  属性。
	outOS.BuildNumber  = (int)oi.dwBuildNumber;

	// 设置 CSDVersion   属性。
	outOS.CSDVersion   = oi.szCSDVersion;

	// 设置 OSLanguage   属性。
	LANGID localID = GetSystemDefaultLangID();
	switch (localID)
	{
	case 0x0404:
		outOS.OSLanguage = "Chinese (Taiwan)";
		break;
	case 0x0804:
		outOS.OSLanguage = "Chinese (PRC)";
		break;
	case 0x0c04:
		outOS.OSLanguage = "Chinese (Hong Kong SAR, PRC)";
		break;
	case 0x1004:
		outOS.OSLanguage = "Chinese (Singapore)";
		break;
	case 0x0411:
		outOS.OSLanguage = "Japanese";
		break;
	case 0x0409:
		outOS.OSLanguage = "English (United States)";
		break;
	case 0x0809:
		outOS.OSLanguage = "English (United Kingdom)";
		break;
	case 0x0c09:
		outOS.OSLanguage = "English (Australian)";
		break;
	case 0x1009:
		outOS.OSLanguage = "English (Canadian)";
		break;
	case 0x1409:
		outOS.OSLanguage = "English (New Zealand)";
		break;
	case 0x1809:
		outOS.OSLanguage = "English (Ireland)";
		break;
	case 0x1c09:
		outOS.OSLanguage = "English (South Africa)";
		break;
	case 0x2009:
		outOS.OSLanguage = "English (Jamaica)";
		break;
	case 0x2409:
		outOS.OSLanguage = "English (Caribbean)";
		break;
	case 0x2809:
		outOS.OSLanguage = "English (Belize)";
		break;
	case 0x2c09:
		outOS.OSLanguage = "English (Trinidad)";
		break;

	default:
		outOS.OSLanguage  = "Unknown";
	}
}