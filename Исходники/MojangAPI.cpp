void cMojangAPI::CacheNamesToUUIDs(const AStringVector & a_PlayerNames)
{
	// Create a list of names to query, by removing those that are already cached:
	AStringVector NamesToQuery;
	NamesToQuery.reserve(a_PlayerNames.size());
	{
		cCSLock Lock(m_CSNameToUUID);
		for (AStringVector::const_iterator itr = a_PlayerNames.begin(), end = a_PlayerNames.end(); itr != end; ++itr)
		{
			if (m_NameToUUID.find(*itr) == m_NameToUUID.end())
			{
				NamesToQuery.push_back(*itr);
			}
		}  // for itr - a_PlayerNames[]
	}  // Lock(m_CSNameToUUID)
	
	while (!NamesToQuery.empty())
	{
		// Create the request body - a JSON containing up to MAX_PER_QUERY playernames:
		Json::Value root;
		int Count = 0;
		AStringVector::iterator itr = NamesToQuery.begin(), end = NamesToQuery.end();
		for (; (itr != end) && (Count < MAX_PER_QUERY); ++itr, ++Count)
		{
			Json::Value req(*itr);
			root.append(req);
		}  // for itr - a_PlayerNames[]
		NamesToQuery.erase(NamesToQuery.begin(), itr);
		Json::FastWriter Writer;
		AString RequestBody = Writer.write(root);
	
		// Create the HTTP request:
		AString Request;
		Request += "POST " + m_NameToUUIDAddress + " HTTP/1.0\r\n";  // We need to use HTTP 1.0 because we don't handle Chunked transfer encoding
		Request += "Host: " + m_NameToUUIDServer + "\r\n";
		Request += "User-Agent: MCServer\r\n";
		Request += "Connection: close\r\n";
		Request += "Content-Type: application/json\r\n";
		Request += Printf("Content-Length: %u\r\n", (unsigned)RequestBody.length());
		Request += "\r\n";
		Request += RequestBody;

		// Get the response from the server:
		AString Response;
		if (!SecureRequest(m_NameToUUIDServer, Request, Response))
		{
			continue;
		}

		// Check the HTTP status line:
		const AString Prefix("HTTP/1.1 200 OK");
		AString HexDump;
		if (Response.compare(0, Prefix.size(), Prefix))
		{
			LOGINFO("%s failed: bad HTTP status line received", __FUNCTION__);
			LOGD("Response: \n%s", CreateHexDump(HexDump, Response.data(), Response.size(), 16).c_str());
			continue;
		}

		// Erase the HTTP headers from the response:
		size_t idxHeadersEnd = Response.find("\r\n\r\n");
		if (idxHeadersEnd == AString::npos)
		{
			LOGINFO("%s failed: bad HTTP response header received", __FUNCTION__);
			LOGD("Response: \n%s", CreateHexDump(HexDump, Response.data(), Response.size(), 16).c_str());
			continue;
		}
		Response.erase(0, idxHeadersEnd + 4);
		
		// Parse the returned string into Json:
		Json::Reader reader;
		if (!reader.parse(Response, root, false) || !root.isArray())
		{
			LOGWARNING("%s failed: Cannot parse received data (NameToUUID) to JSON!", __FUNCTION__);
			LOGD("Response body:\n%s", CreateHexDump(HexDump, Response.data(), Response.size(), 16).c_str());
			continue;
		}
	
		// Store the returned results into cache:
		size_t JsonCount = root.size();
		Int64 Now = time(NULL);
		{
			cCSLock Lock(m_CSNameToUUID);
			for (size_t idx = 0; idx < JsonCount; ++idx)
			{
				Json::Value & Val = root[idx];
				AString JsonName = Val.get("name", "").asString();
				AString JsonUUID = MakeUUIDShort(Val.get("id", "").asString());
				if (JsonUUID.empty())
				{
					continue;
				}
				m_NameToUUID[StrToLower(JsonName)] = sProfile(JsonName, JsonUUID, "", "", Now);
			}  // for idx - root[]
		}  // cCSLock (m_CSNameToUUID)
		
		// Also cache the UUIDToName:
		{
			cCSLock Lock(m_CSUUIDToName);
			for (size_t idx = 0; idx < JsonCount; ++idx)
			{
				Json::Value & Val = root[idx];
				AString JsonName = Val.get("name", "").asString();
				AString JsonUUID = MakeUUIDShort(Val.get("id", "").asString());
				if (JsonUUID.empty())
				{
					continue;
				}
				m_UUIDToName[JsonUUID] = sProfile(JsonName, JsonUUID, "", "", Now);
			}  // for idx - root[]
		}
	}  // while (!NamesToQuery.empty())
}