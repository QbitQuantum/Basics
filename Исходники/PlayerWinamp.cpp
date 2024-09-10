/*
** Called during each update of the main measure.
**
*/
void PlayerWinamp::UpdateData()
{
	if (m_Initialized || CheckWindow())
	{
		const auto playing = SendMessage(m_Window, WM_WA_IPC, 0, IPC_ISPLAYING);
		if (playing == 0)
		{
			// Make sure Winamp is still active
			if (!IsWindow(m_Window))
			{
				m_Initialized = false;
				ClearData();

				if (m_WinampHandle) CloseHandle(m_WinampHandle);
			}
			else if (m_State != STATE_STOPPED)
			{
				ClearData(false);
			}

			// Don't continue if Winamp has quit or is stopped
			return;
		}
		else
		{
			m_State = (playing == 1) ? STATE_PLAYING : STATE_PAUSED;
			m_Position = (UINT)SendMessage(m_Window, WM_WA_IPC, 0, IPC_GETOUTPUTTIME) / 1000;  // ms to secs
			m_Volume = ((UINT)SendMessage(m_Window, WM_WA_IPC, -666, IPC_SETVOLUME) * 100) / 255;  // 0 - 255 to 0 - 100
		}

		WCHAR wBuffer[MAX_PATH];
		char cBuffer[MAX_PATH];

		if (m_UseUnicodeAPI)
		{
			if (!ReadProcessMemory(m_WinampHandle, m_WinampAddress, &wBuffer, sizeof(wBuffer), nullptr))
			{
				// Failed to read memory
				return;
			}
		}
		else
		{
			// MediaMonkey doesn't support wide IPC messages
			const auto pos = SendMessage(m_Window, WM_WA_IPC, 0, IPC_GETLISTPOS);
			LPCVOID address = (LPCVOID)SendMessage(m_Window, WM_WA_IPC, pos, IPC_GETPLAYLISTFILE);

			if (!ReadProcessMemory(m_WinampHandle, address, &cBuffer, sizeof(cBuffer), nullptr))
			{
				// Failed to read memory
				return;
			}

			mbstowcs(wBuffer, cBuffer, MAX_PATH);
		}

		if (wcscmp(wBuffer, m_FilePath.c_str()) != 0)
		{
			++m_TrackCount;
			m_FilePath = wBuffer;
			m_PlayingStream = (m_FilePath.find(L"://") != std::wstring::npos);

			if (!m_PlayingStream)
			{
				const int duration = (int)SendMessage(m_Window, WM_WA_IPC, 1, IPC_GETOUTPUTTIME);
				m_Duration = (duration != -1) ? duration : 0;

				m_Rating = (UINT)SendMessage(m_Window, WM_WA_IPC, 0, IPC_GETRATING);
				m_Shuffle = SendMessage(m_Window, WM_WA_IPC, 0, IPC_GET_SHUFFLE) != 0;
				m_Repeat = SendMessage(m_Window, WM_WA_IPC, 0, IPC_GET_REPEAT) != 0;

				TagLib::FileRef fr(wBuffer, false);
				TagLib::Tag* tag = fr.tag();
				if (tag)
				{
					m_Artist = tag->artist().toWString();
					m_Album = tag->album().toWString();
					m_Title = tag->title().toWString();
					m_Number = tag->track();
					m_Year = tag->year();

					if (m_Measures & MEASURE_LYRICS)
					{
						FindLyrics();
					}
				}
				else if (m_Measures & MEASURE_LYRICS)
				{
					m_Lyrics.clear();
				}

				// Find cover if needed
				if (m_Measures & MEASURE_COVER)
				{
					if (tag && CCover::GetEmbedded(fr, m_TempCoverPath))
					{
						// Got everything, return
						m_CoverPath = m_TempCoverPath;
						return;
					}

					std::wstring trackFolder = CCover::GetFileFolder(m_FilePath);
					if (tag && !m_Album.empty())
					{
						// Winamp stores covers usually as %album%.jpg
						std::wstring file = m_Album;
						std::wstring::size_type end = file.length();
						for (std::wstring::size_type pos = 0; pos < end; ++pos)
						{
							// Replace reserved chars according to Winamp specs
							switch (file[pos])
							{
							case L'?':
							case L'*':
							case L'|':
								file[pos] = L'_';
								break;

							case L'/':
							case L'\\':
							case L':':
								file[pos] = L'-';
								break;

							case L'\"':
								file[pos] = L'\'';
								break;

							case L'<':
								file[pos] = L'(';
								break;

							case L'>':
								file[pos] = L')';
								break;
							}
						}

						if (CCover::GetLocal(file, trackFolder, m_CoverPath))
						{
							// %album% art file found
							return;
						}
					}

					if (!CCover::GetLocal(L"cover", trackFolder, m_CoverPath) &&
						!CCover::GetLocal(L"folder", trackFolder, m_CoverPath))
					{
						// Nothing found
						m_CoverPath.clear();
					}
				}

				if (tag)
				{
					return;
				}
			}
			else
			{
				m_Rating = 0;
				m_Duration = 0;
				m_CoverPath.clear();
			}
		}
		else if (!m_PlayingStream)
		{
			if (m_Duration == 0)
			{
				const int duration = (int)SendMessage(m_Window, WM_WA_IPC, 1, IPC_GETOUTPUTTIME);
				m_Duration = (duration != -1) ? duration : 0;
			}

			return;
		}

		// TagLib couldn't parse the file or Winamp is playing a stream, try to get title
		if (m_UseUnicodeAPI)
		{
			LPCVOID address = (LPCVOID)SendMessage(m_Window, WM_WA_IPC, 0, IPC_GET_PLAYING_TITLE);
			ReadProcessMemory(m_WinampHandle, address, &wBuffer, sizeof(wBuffer), nullptr);
		}
		else
		{
			const auto pos = SendMessage(m_Window, WM_WA_IPC, 0, IPC_GETLISTPOS);
			LPCVOID address = (LPCVOID)SendMessage(m_Window, WM_WA_IPC, pos, IPC_GETPLAYLISTTITLE);
			ReadProcessMemory(m_WinampHandle, address, &cBuffer, sizeof(cBuffer), nullptr);
			mbstowcs(wBuffer, cBuffer, MAX_PATH);
		}

		std::wstring title = wBuffer;
		std::wstring::size_type pos = title.find(L" - ");
		if (pos != std::wstring::npos)
		{
			m_Artist.assign(title, 0, pos);
			pos += 3;  // Skip " - "
			m_Title.assign(title, pos, title.length() - pos);
			m_Album.clear();

			if (m_PlayingStream)
			{
				// Remove crap from title if playing radio
				pos = m_Title.find(L" (");
				if (pos != std::wstring::npos)
				{
					m_Title.resize(pos);
				}
			}
		}
		else
		{
			m_Title = title;
			m_Artist.clear();
			m_Album.clear();
		}
	}
}