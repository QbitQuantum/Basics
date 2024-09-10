bool CCssSoap::CommitPlayerScoreRecords(char * szGameGuid)
{
	char szHdrs[512];
	sprintf(szHdrs, "Content-Type: text/xml;charset=UTF-8\r\nSOAPAction: \"http://tempuri.org/GameData/CommitPlayerData\"");

	char soapBody[4092];
	int length = 0;

	length += sprintf(soapBody,
		"<soapenv:Envelope xmlns:soapenv=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:tem=\"http://tempuri.org/\" xmlns:all=\"http://schemas.datacontract.org/2004/07/Allegiance.CommunitySecuritySystem.Server\"> \
		   <soapenv:Header/> \
		   <soapenv:Body> \
			  <tem:CommitPlayerData> \
				 <tem:request> \
					<all:GameGuid>%s</all:GameGuid> \
				 </tem:request> \
			  </tem:CommitPlayerData> \
		   </soapenv:Body> \
		</soapenv:Envelope>",
		szGameGuid);

	int soapLength = strlen(soapBody);

	ZString Response = UTL::DoHTTP(szHdrs, m_szCssServerDomain, "POST", m_szCssGameDataServicePath, soapBody, soapLength, true);

	char * szToken;
	char * szResponse = (char*)_alloca(10000);
	Strcpy(szResponse, (PCC)Response);

	return strstr(szResponse, "<a:Succeeded>true</a:Succeeded>") >= 0;
}