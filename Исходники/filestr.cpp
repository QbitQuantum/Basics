bool GetFileString::GetTString(std::vector<T>& From, std::vector<T>& To, bool bBigEndian)
{
	typedef eol<T> eol;

	bool ExitCode = true;
	T* ReadBufPtr = ReadPos < ReadSize ? From.data() + ReadPos / sizeof(T) : nullptr;

	To.clear();

	// Обработка ситуации, когда у нас пришёл двойной \r\r, а потом не было \n.
	// В этом случаем считаем \r\r двумя MAC окончаниями строк.
	if (bCrCr)
	{
		To.emplace_back(T(eol::cr));
		bCrCr = false;
	}
	else
	{
		EolType Eol = FEOL_NONE;
		for (;;)
		{
			if (ReadPos >= ReadSize)
			{
				if (!(SrcFile.Read(From.data(), ReadBufCount*sizeof(T), ReadSize) && ReadSize))
				{
					if (To.empty())
					{
						ExitCode = false;
					}
					break;
				}

				if (bBigEndian && sizeof(T) != 1)
				{
					_swab(reinterpret_cast<char*>(From.data()), reinterpret_cast<char*>(From.data()), static_cast<int>(ReadSize));
				}

				ReadPos = 0;
				ReadBufPtr = From.data();
			}
			if (Eol == FEOL_NONE)
			{
				// UNIX
				if (*ReadBufPtr == eol::lf)
				{
					Eol = FEOL_UNIX;
				}
				// MAC / Windows? / Notepad?
				else if (*ReadBufPtr == eol::cr)
				{
					Eol = FEOL_MAC;
				}
			}
			else if (Eol == FEOL_MAC)
			{
				// Windows
				if (*ReadBufPtr == eol::lf)
				{
					Eol = FEOL_WINDOWS;
				}
				// Notepad?
				else if (*ReadBufPtr == eol::cr)
				{
					Eol = FEOL_MAC2;
				}
				else
				{
					break;
				}
			}
			else if (Eol == FEOL_WINDOWS || Eol == FEOL_UNIX)
			{
				break;
			}
			else if (Eol == FEOL_MAC2)
			{
				// Notepad
				if (*ReadBufPtr == eol::lf)
				{
					Eol = FEOL_NOTEPAD;
				}
				else
				{
					// Пришёл \r\r, а \n не пришёл, поэтому считаем \r\r двумя MAC окончаниями строк
					To.pop_back();
					bCrCr = true;
					break;
				}
			}
			else
			{
				break;
			}

			ReadPos += sizeof(T);

			if (To.size() == To.capacity())
				To.reserve(To.size() * 2);

			To.emplace_back(*ReadBufPtr);
			ReadBufPtr++;
		}
	}
	To.push_back(0);
	return ExitCode;
}