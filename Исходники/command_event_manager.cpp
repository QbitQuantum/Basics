CCommandEventManager::CScriptNode	*parseInstructionList()
{
	CInstListNode	*list = new CInstListNode();
	list->Root = parsedScript;
	list->Line = Parser.Line;

	do
	{
		uint	token = Parser.getToken();

		switch (token)
		{
		case TOKEN_END:
			return list;
			break;

		case TOKEN_IF:
			list->Nodes.push_back(parseIf());
			break;
		case TOKEN_ELSE:
			Parser.rewindToken();
			return list;
			break;
		case TOKEN_ENDIF:
			Parser.rewindToken();
			return list;
			break;

		case TOKEN_WHILE:
			list->Nodes.push_back(parseWhile());
			break;
		case TOKEN_ENDLOOP:
			Parser.rewindToken();
			return list;
			break;

		case TOKEN_CMD:
			list->Nodes.push_back(parseCmd());
			break;
		case TOKEN_SETTEXT:
			list->Nodes.push_back(parseSetText());
			break;
		case TOKEN_SETNUMERIC:
			list->Nodes.push_back(parseSetNumeric());
			break;
		case TOKEN_ERASE:
			list->Nodes.push_back(parseErase());
			break;
		case TOKEN_WAIT:
			list->Nodes.push_back(parseWait());
			break;
		case TOKEN_RECEIVE:
			list->Nodes.push_back(parseReceive());
			break;
		case TOKEN_SEND:
			list->Nodes.push_back(parseSend());
			break;
		case TOKEN_DISPLAY:
			list->Nodes.push_back(parseDisplay());
			break;

		case TOKEN_COMMENT:
			Parser.skipLine();
			break;

		case TOKEN_UNKNOWN:
			nlwarning("[%s] Unknow token at line %d: '%20s...', line ignored", parsedScript->Name.c_str(), Parser.Line, Parser.TokenStart);
			Parser.skipLine();
			break;
		}
	}
	while (true);

	return (CCommandEventManager::CScriptNode*)list;
}