MIRANDA_HOOK_EVENT(ME_DB_EVENT_FILTER_ADD, w, l)
{
	MCONTACT hContact = (MCONTACT)w;
	if (!l) //fix potential DEP crash
		return 0;
	DBEVENTINFO * dbei = (DBEVENTINFO*)l;

	// if event is in protocol that is not despammed
	if (!ProtoInList(dbei->szModule)) {
		// ...let the event go its way
		return 0;
	}
	//do not check excluded contact

	if (db_get_b(hContact, pluginName, "Answered", 0))
		return 0;
	if (db_get_b(hContact, pluginName, "Excluded", 0)) {
		if (!db_get_b(hContact, "CList", "NotOnList", 0))
			db_unset(hContact, pluginName, "Excluded");
		return 0;
	}
	//we want block not only messages, i seen many types other eventtype flood
	if (dbei->flags & DBEF_READ)
		// ...let the event go its way
		return 0;
	//mark contact which we trying to contact for exclude from check
	if ((dbei->flags & DBEF_SENT) && db_get_b(hContact, "CList", "NotOnList", 0)
		&& (!gbMaxQuestCount || db_get_dw(hContact, pluginName, "QuestionCount", 0) < gbMaxQuestCount) && gbExclude) {
		db_set_b(hContact, pluginName, "Excluded", 1);
		return 0;
	}
	// if message is from known or marked Answered contact
	if (!db_get_b(hContact, "CList", "NotOnList", 0))
		// ...let the event go its way
		return 0;
	// if message is corrupted or empty it cannot be an answer.
	if (!dbei->cbBlob || !dbei->pBlob)
		// reject processing of the event
		return 1;

	tstring message;

	if (dbei->flags & DBEF_UTF) {
		wchar_t* msg_u;
		char* msg_a = mir_strdup((char*)dbei->pBlob);
		mir_utf8decode(msg_a, &msg_u);
		message = msg_u;
	}
	else
		message = mir_a2u((char*)(dbei->pBlob));

	// if message contains right answer...

	boost::algorithm::erase_all(message, "\r");
	boost::algorithm::erase_all(message, "\n");

	bool bSendMsg = true;
	if (gbInvisDisable) {
		if (CallProtoService(dbei->szModule, PS_GETSTATUS, 0, 0) == ID_STATUS_INVISIBLE)
			bSendMsg = false;
		else if (db_get_w(hContact, dbei->szModule, "ApparentMode", 0) == ID_STATUS_OFFLINE)
			bSendMsg = false; //is it useful ?
	}
	bool answered = false;
	if (gbMathExpression) {
		if (boost::algorithm::all(message, boost::is_digit())) {
			int num = _ttoi(message.c_str());
			int math_answer = db_get_dw(hContact, pluginName, "MathAnswer", 0);
			if (num && math_answer)
				answered = (num == math_answer);
		}
	}
	else if (!gbRegexMatch)
		answered = gbCaseInsensitive ? (!Stricmp(message.c_str(), (variables_parse(gbAnswer, hContact).c_str()))) : (!mir_tstrcmp(message.c_str(), (variables_parse(gbAnswer, hContact).c_str())));
	else {
		if (gbCaseInsensitive) {
			std::string check(toUTF8(variables_parse(gbAnswer, hContact))), msg(toUTF8(message));
			boost::algorithm::to_upper(check);
			boost::algorithm::to_upper(msg);
			boost::regex expr(check);
			answered = boost::regex_search(msg.begin(), msg.end(), expr);
		}
		else {
			std::string check(toUTF8(variables_parse(gbAnswer, hContact))), msg(toUTF8(message));
			boost::regex expr(check);
			answered = boost::regex_search(msg.begin(), msg.end(), expr);
		}
	}
	if (answered) {
		// unhide contact
		db_unset(hContact, "CList", "Hidden");

		db_unset(hContact, pluginName, "MathAnswer");

		// mark contact as Answered
		db_set_b(hContact, pluginName, "Answered", 1);

		//add contact permanently
		if (gbAddPermanent) //do not use this )
			db_unset(hContact, "CList", "NotOnList");

		// send congratulation
		if (bSendMsg) {
			tstring prot = DBGetContactSettingStringPAN(NULL, dbei->szModule, "AM_BaseProto", _T(""));
			// for notICQ protocols or disable auto auth. reqwest
			if ((Stricmp(_T("ICQ"), prot.c_str())) || (!gbAutoReqAuth)) {
				char * buf = mir_utf8encodeW(variables_parse(gbCongratulation, hContact).c_str());
				CallContactService(hContact, PSS_MESSAGE, 0, (LPARAM)buf);
				mir_free(buf);
			}
			// Note: For ANSI can be not work
			if (!Stricmp(_T("ICQ"), prot.c_str())) {
				// grand auth.
				if (gbAutoAuth)
					CallProtoService(dbei->szModule, "/GrantAuth", w, 0);
				// add contact to server list and local group
				if (gbAutoAddToServerList) {
					db_set_ws(hContact, "CList", "Group", gbAutoAuthGroup.c_str());
					CallProtoService(dbei->szModule, "/AddServerContact", w, 0);
					db_unset(hContact, "CList", "NotOnList");
				};
				// auto auth. reqwest with send congratulation
				if (gbAutoReqAuth)
					CallContactService(hContact, PSS_AUTHREQUEST, 0, (LPARAM)variables_parse(gbCongratulation, hContact).c_str());
			}
		}
		return 0;
	}
	// URL contains check
	bSendMsg = (bSendMsg && gbIgnoreURL) ? (!IsUrlContains((TCHAR *)message.c_str())) : bSendMsg;
	// if message message does not contain infintite talk protection prefix
	// and question count for this contact is less then maximum
	if (bSendMsg) {
		if ((!gbInfTalkProtection || tstring::npos == message.find(_T("StopSpam automatic message:\r\n")))
			&& (!gbMaxQuestCount || db_get_dw(hContact, pluginName, "QuestionCount", 0) < gbMaxQuestCount)) {
			// send question
			tstring q;
			if (gbInfTalkProtection)
				q += _T("StopSpam automatic message:\r\n");
			if (gbMathExpression) { //parse math expression in question
				tstring tmp_question = gbQuestion;
				std::list<int> args;
				std::list<TCHAR> actions;
				tstring::size_type p1 = gbQuestion.find(_T("X")), p2 = 0;
				const tstring expr_chars = _T("X+-/*"), expr_acts = _T("+-/*");
				while (p1 < gbQuestion.length() && p1 != tstring::npos && expr_chars.find(gbQuestion[p1]) != tstring::npos) {
					std::string arg;
					p2 = p1;
					for (p1 = gbQuestion.find(_T("X"), p1); (p1 < gbQuestion.length()) && (gbQuestion[p1] == L'X'); ++p1)
						arg += get_random_num(1);

					tmp_question.replace(p2, arg.size(), toUTF16(arg));
					args.push_back(atoi(arg.c_str()));

					if ((p1 < gbQuestion.length()) && (p1 != tstring::npos) && (expr_acts.find(gbQuestion[p1]) != tstring::npos))
						actions.push_back(gbQuestion[p1]);
					++p1;
				}
				int math_answer = 0;
				math_answer = args.front();
				args.pop_front();
				while (!args.empty()) {
					if (!actions.empty()) {
						switch (actions.front()) {
						case _T('+'):
							{
								math_answer += args.front();
								args.pop_front();
							}
							break;
						case _T('-'):
							{
								math_answer -= args.front();
								args.pop_front();
							}
							break;
						case _T('/'):
							{
								math_answer /= args.front();
								args.pop_front();
							}
							break;
						case _T('*'):
							{
								math_answer *= args.front();
								args.pop_front();
							}
							break;
						}
						actions.pop_front();
					}
					else
						break;
				}
				db_set_dw(hContact, pluginName, "MathAnswer", math_answer);
				q += variables_parse(tmp_question, hContact);
			}
			else
				q += variables_parse(gbQuestion, hContact);

			CallContactService(hContact, PSS_MESSAGE, 0, ptrA(mir_utf8encodeW(q.c_str())));

			// increment question count
			DWORD questCount = db_get_dw(hContact, pluginName, "QuestionCount", 0);
			db_set_dw(hContact, pluginName, "QuestionCount", questCount + 1);
		}
		else {
			if (gbIgnoreContacts)
				db_set_dw(hContact, "Ignore", "Mask1", 0x0000007F);
		}
	}
	if (gbHideContacts)
		db_set_b(hContact, "CList", "Hidden", 1);
	if (gbSpecialGroup)
		db_set_ws(hContact, "CList", "Group", gbSpammersGroup.c_str());
	db_set_b(hContact, "CList", "NotOnList", 1);

	// save first message from contact
	if (db_get_dw(hContact, pluginName, "QuestionCount", 0) < 2) {
		dbei->flags |= DBEF_READ;
		db_event_add(hContact, dbei);
	};
	// reject processing of the event
	LogSpamToFile(hContact, message);
	return 1;
}