std::string CLoLChecker::GetCaptcha()
{		
	std::string strPicPath;

	if (this->HTTP->IsOpen() && 
		this->HTTP->Connect(L"www.google.com", 443))
	{
		if (this->HTTP->SendRequest(L"GET", L"/recaptcha/api/reload?c=03AHJ_VuurlCeu8nEIwl-k3nT9fX0IVYaxEic7cN-keN3loPs9NpCNO0W2B6bAvghY4ryJz9gJn_ovYsUIygOnourSkyFuCDOWY5T44uS5gw6PDyJmCGDN7fD6M_vno0uUfXbDNBVWtUpFPMaXVUHaTY412EAzR_n5s_f-HeLJF-nwIFpOea4jvNs3ss2tgTFgm_4U-b1h09FjXzDogkMLQWBOarYjEeUN1w&k=6LcwdeESAAAAAJg_ltVGdjrqlf7Bmbg449SyUcSW&reason=i&type=image", L"", ""))
		{
			std::string strResponse = reinterpret_cast<const char*>(this->HTTP->GetResponse().c_str());

			DWORD dwChallangeStart = strResponse.find("('") + 2,
				 dwChallangeEnd = strResponse.find("',", dwChallangeStart);

			this->captcha.strChallange = strResponse.substr(dwChallangeStart, dwChallangeEnd - dwChallangeStart);

			if (this->captcha.strChallange.size() > 0)
			{
				if (this->HTTP->Connect(L"www.google.com", 443))
				{
					std::wstring strObj = std::wstring(L"/recaptcha/api/image?c=").append(StringToWString(this->captcha.strChallange));

					if (this->HTTP->SendRequest(L"GET", strObj, L"", ""))
					{
						std::basic_string<byte> strResponse = this->HTTP->GetResponse();

						char pwszTempPath[MAX_PATH];

						if (GetTempPathA(MAX_PATH, pwszTempPath))
						{
							char pwszTempFile[MAX_PATH];

							if (GetTempFileNameA(pwszTempPath, "s3c", 0, pwszTempFile))
								DeleteFileA(pwszTempFile);

							strPicPath = pwszTempFile;
							strPicPath.replace(strPicPath.find(".tmp"), 4, ".jpg");

							DWORD dwPos = 0;
							FileIO output(strPicPath.c_str(), GENERIC_WRITE, CREATE_ALWAYS);

							if (output.open())
								output.write(strResponse.c_str(), strResponse.size(), dwPos);
						}
					}
				}
			}
		}
	}

	return strPicPath;
}