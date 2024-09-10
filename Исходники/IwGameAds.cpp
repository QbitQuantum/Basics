//
//
//
//	ImMobi specific implementation
//
//
//
bool CIwGameAds::RequestAdInMobi()
{
	// Build M2M request URI string
	RequestURI = "http://w.inmobi.com/showad.asm";				// Live
//	RequestURI = "http://i.w.sandbox.inmobi.com/showad.asm";	// Test
    
    int slotSize = (int)SlotSize;

	CIwGameString body;
	CIwGameString urlencoded;

	body = "mk-siteid=";
	body += ApplicationID;
	body += "&mk-carrier=";
	body += IW_GAME_HTTP_MANAGER->getIPAddress();
	body += "&h-user-agent=";
	urlencoded.URLEncode(UserAgent.c_str());
	urlencoded.ToLower();
	body += urlencoded;
	body += "&u-id=";
	body += CIwGameString(UDID);
	body += "&d-localization=";
	urlencoded.URLEncode(s3eDeviceGetString(S3E_DEVICE_LOCALE));
	urlencoded.ToLower();
	body += urlencoded;
//	body += "&d-netType=wifi";
	body += "&d-netType=carrier";
    body += "&mk-ad-slot=";
    body += CIwGameString(slotSize);
	body += "&mk-version=pr-SPEC-CTATA-20130111";
	if (UserAge != 0)
	{
		body += "&u-age=";
		body += CIwGameString(UserAge);
	}
	if (UserGender != GenderInvalid)
	{
		if (UserGender == GenderFemale)
			body += "&u-gender=f";
		else
			body += "&u-gender=m";
	}
	if (!UserGPSLocation.IsEmpty())
	{
		body += "&u-latlong=";
		body += UserGPSLocation;
	}
	if (!UserKeywords.IsEmpty())
	{
		body += "&u-interests=";
		body += UserKeywords;
	}
	if (!ExtraInfo.IsEmpty())
	{
		body += ExtraInfo;
	}
//	body.ToLower();

	AdRequest.setPOST();
	AdRequest.setURI(RequestURI.c_str());
	AdRequest.setContentAvailableCallback(&AdInfoRetrievedCallback, NULL);
	AdRequest.SetHeader("User-Agent", UserAgent.c_str());
	AdRequest.SetHeader("X-Mkhoj-SiteID", ApplicationID.c_str());
	AdRequest.SetHeader("Content-Type", "application/x-www-form-urlencoded");
	AdRequest.SetHeader("Content-Length", CIwGameString(body.GetLength()).c_str());
	AdRequest.setBody(body.c_str());
	IW_GAME_HTTP_MANAGER->AddRequest(&AdRequest);
	BusyTimer.setDuration(IW_GAME_ADS_TIMEOUT);

	return true;
}