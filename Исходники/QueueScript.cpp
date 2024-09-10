void QueueScriptController::AddMessage(Message::EKind kind, const char* text)
{
	const char* msgText = text + m_prefixLen;

	if (!strncmp(msgText, "[NZB] ", 6))
	{
		debug("Command %s detected", msgText + 6);
		if (!strncmp(msgText + 6, "NZBPR_", 6))
		{
			CString param = msgText + 6 + 6;
			char* value = strchr(param, '=');
			if (value)
			{
				*value = '\0';
				GuardedDownloadQueue downloadQueue = DownloadQueue::Guard();
				NzbInfo* nzbInfo = QueueScriptCoordinator::FindNzbInfo(downloadQueue, m_id);
				if (nzbInfo)
				{
					nzbInfo->GetParameters()->SetParameter(param, value + 1);
				}
			}
			else
			{
				error("Invalid command \"%s\" received from %s", msgText, GetInfoName());
			}
		}
		else if (!strncmp(msgText + 6, "DIRECTORY=", 10) &&
			m_event == QueueScriptCoordinator::qeNzbDownloaded)
		{
			GuardedDownloadQueue downloadQueue = DownloadQueue::Guard();
			NzbInfo* nzbInfo = QueueScriptCoordinator::FindNzbInfo(downloadQueue, m_id);
			if (nzbInfo)
			{
				nzbInfo->SetFinalDir(msgText + 6 + 10);
			}
		}
		else if (!strncmp(msgText + 6, "MARK=BAD", 8))
		{
			m_markBad = true;
			GuardedDownloadQueue downloadQueue = DownloadQueue::Guard();
			NzbInfo* nzbInfo = QueueScriptCoordinator::FindNzbInfo(downloadQueue, m_id);
			if (nzbInfo)
			{
				nzbInfo->PrintMessage(Message::mkWarning, "Marking %s as bad", *m_nzbName);
				nzbInfo->SetMarkStatus(NzbInfo::ksBad);
			}
		}
		else
		{
			error("Invalid command \"%s\" received from %s", msgText, GetInfoName());
		}
	}
	else
	{
		NzbInfo* nzbInfo = nullptr;
		{
			GuardedDownloadQueue downloadQueue = DownloadQueue::Guard();
			nzbInfo = QueueScriptCoordinator::FindNzbInfo(downloadQueue, m_id);
			if (nzbInfo)
			{
				nzbInfo->AddMessage(kind, text);
			}
		}

		if (!nzbInfo)
		{
			ScriptController::AddMessage(kind, text);
		}
	}
}