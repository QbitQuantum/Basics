BString AIMProtocol::NormalizeNick(const char *nick) {
	BString normal = nick;
	
	normal.ReplaceAll(" ", "");
	normal.ToLower();
	
	map<string,BString>::iterator i = fNickMap.find(normal.String());
	
	if ( i == fNickMap.end() ) {
		// add 'real' nick if it's not already there
		LOG(fManager->Protocol(), liDebug, "Adding normal (%s) vs screen (%s)", normal.String(), nick );
		fNickMap[string(normal.String())] = BString(nick);
	}
	
	LOG(fManager->Protocol(), liDebug, "Screen (%s) to normal (%s)", nick, normal.String() );
	
	return normal;
};