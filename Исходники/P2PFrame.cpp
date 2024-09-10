void Results::handleEvent(Event* evt)
{
	sysstring type = evt->get_type();

	EventPhaseType phase = evt->get_eventPhase();
	if (phase != CAPTURING_PHASE)
	{
		if (type == OLESTR("click"))
		{
			evt->stopPropagation();
			m_query->More();
		}
		else if (type == OLESTR("Activate"))
		{
			evt->stopPropagation();

			IItemSite* itemsite = dynamic_cast<IItemSite*>(evt->get_target());

			SHA1DigestField* sha1 = dynamic_cast<SHA1DigestField*>(itemsite->GetFieldData(4));

			std::string filename = ConvertS2A(dynamic_cast<TextString*>(itemsite->GetFieldUI(0))->get_textContent());
			//LPTSTR ext = PathFindExtension(filename.c_str());
			TCHAR filepart[512];
			TCHAR extpart[512];
			_splitpath(filename.c_str(), NULL, NULL, filepart, extpart);

			ByteStreamWriter* file = NULL;
			int n = 0;
			do
			{
				try
				{
					char modifiedfilename[512];

					if (n > 0)
						strcpy(modifiedfilename, filename.c_str());
					else
						sprintf(modifiedfilename, "%s(%d)%s", filepart, n, extpart);

					file = new ByteStreamWriter(modifiedfilename);
				}
				catch(int e)
				{
					if (e == ERROR_SHARING_VIOLATION)
					{
						n++;	// Try again
					}
					else
					{
						// Any other error, we give up
						break;
					}
				}
			}
			while (file == NULL);

			if (file == NULL)
			{
				MessageBox(NULL, "Couldn't create file", "", MB_OK);
			}
			else
			{
				MessageBeep(-1);
				//m_GnutellaNetwork->pP2P->Download(dynamic_cast<LongLongField*>(itemsite->GetFieldData(1))->m_value, sha1->m_buffer, m_Downloads, file);
			}
		}
	}
}