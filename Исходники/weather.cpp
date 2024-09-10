Weather::ReturnVals Weather::GetVals(const char * key, uint32_t zip, const char * pws, bool usePws) const
{
	ReturnVals vals = {0};
	EthernetClient client;
	if (client.connect(m_wundergroundAPIHost, 80))
	{
		char getstring[255];
		trace(F("Connected\n"));
		if (usePws)
			snprintf(getstring, sizeof(getstring), "GET http://%s/api/%s/yesterday/conditions/q/pws:%s.json HTTP/1.1\r\n",m_wundergroundAPIHost, key, pws);
		else
			snprintf(getstring, sizeof(getstring), "GET http://%s/api/%s/yesterday/conditions/q/%ld.json HTTP/1.1\r\n",m_wundergroundAPIHost, key, (long) zip);

		//trace("GetString:%s\n",getstring);
		client.write((uint8_t*) getstring, strlen(getstring));
		
		//send host header
		snprintf(getstring, sizeof(getstring), "Host: %s\r\nConnection: close\r\n\r\n",m_wundergroundAPIHost);
		//trace("GetString:%s\n",getstring);
		client.write((uint8_t*) getstring, strlen(getstring));

		ParseResponse(client, &vals);
		vals.resolvedIP=client.GetIpAddress();

		client.stop();
		if (!vals.valid)
		{
			if (vals.keynotfound)
				trace("Invalid WUnderground Key\n");
			else
				trace("Bad WUnderground Response\n");
		}
	}
	else
	{
		trace(F("connection failed\n"));
		client.stop();
	}
	return vals;
}