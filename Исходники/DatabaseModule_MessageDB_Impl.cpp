BOOL DatabaseModule_Impl::sqlInsertMessage(IN MessageEntity& msg)
{
	if (module::TCPCLIENT_STATE_DISCONNECT == module::getTcpClientModule()->getTcpClientNetState()
		|| MESSAGE_RENDERTYPE_SYSTEMTIPS == msg.msgRenderType)
	{
		return FALSE;
	}
	if (msg.msgId <= 0)
	{
		std::string msgDecrptyCnt;
		DECRYPT_MSG(msg.content, msgDecrptyCnt);
		LOG__(ERR, _T("msgid <= 0, msgid:%d msg_content:%s Don't save to DB!")
			, msg.msgId, util::stringToCString(msgDecrptyCnt));
		return FALSE;
	}

	try
	{
		CppSQLite3Statement stmt = m_pSqliteDB->compileStatement(insertMessageSql.c_str());
		stmt.bind(1, (Int32)msg.msgId);
		stmt.bind(2, msg.sessionId.c_str());
		stmt.bind(3, msg.talkerSid.c_str());
		//对语音消息做个特殊处理，content存储的是json格式字符串
		if (MESSAGE_RENDERTYPE_AUDIO == msg.msgRenderType)
		{
			Json::Value root;
			root["msgAudioTime"] = msg.msgAudioTime;
			root["msgAudioId"] = msg.content;
			Json::FastWriter fstWrite;
			std::string audioContent = fstWrite.write(root);
			stmt.bind(4, audioContent.c_str());
		}
		else
		{
			stmt.bind(4, msg.content.c_str());
		}
		stmt.bind(5, msg.msgRenderType);
		stmt.bind(6, msg.msgSessionType);
		stmt.bind(7, (Int32)msg.msgTime);
		stmt.bind(8, time(0));
		stmt.execDML();
	}

	catch (CppSQLite3Exception& sqliteException)
	{
#ifdef _DEBUG
		//MessageBoxA(0, sqliteException.errorMessage(), "BD ERROR", MB_OK | MB_ICONHAND);
#endif
		CString csErrMsg = util::stringToCString(sqliteException.errorMessage(), CP_UTF8);
		LOG__(ERR, _T("db failed,error msg:%s"), csErrMsg);
		_msgToTrace(msg);
		return FALSE;
	}
	catch (...)
	{
		LOG__(ERR, _T("db unknown exception"));
		_msgToTrace(msg);
		return FALSE;
	}

	return TRUE;
}