short CRConData::CheckProgressInConsole(UINT nCursorLine)
{
	if (!isValid(true, nWidth*(nCursorLine+1)))
		return -1;

	const wchar_t* pszCurLine = pConChar + (nWidth * nCursorLine);

	// Обработка прогресса NeroCMD и пр. консольных программ (если курсор находится в видимой области)
	//Плагин Update
	//"Downloading Far                                               99%"
	//NeroCMD
	//"012% ########.................................................................."
	//ChkDsk
	//"Completed: 25%"
	//Rar
	// ...       Vista x86\Vista x86.7z         6%
	//aria2c
	//[#1 SIZE:0B/9.1MiB(0%) CN:1 SPD:1.2KiBs ETA:2h1m11s]
	int nIdx = 0;
	bool bAllowDot = false;
	short nProgress = -1;

	const wchar_t *szPercentEng = L" percent";
	const wchar_t *szComplEng  = L"Completed:";
	static wchar_t szPercentRus[16] = {}, szComplRus[16] = {};
	static int nPercentEngLen = lstrlen(szPercentEng), nComplEngLen = lstrlen(szComplEng);
	static int nPercentRusLen, nComplRusLen;

	if (szPercentRus[0] == 0)
	{
		szPercentRus[0] = L' ';
		TODO("Хорошо бы и другие национальные названия обрабатывать, брать из настройки");
		lstrcpy(szPercentRus,L"процент");
		lstrcpy(szComplRus,L"Завершено:");

		nPercentRusLen = lstrlen(szPercentRus);
		nComplRusLen = lstrlen(szComplEng);
	}

	// Сначала проверим, может цифры идут в начале строки (лидирующие пробелы)?
	if (pszCurLine[nIdx] == L' ' && isDigit(pszCurLine[nIdx+1]))
		nIdx++; // один лидирующий пробел перед цифрой
	else if (pszCurLine[nIdx] == L' ' && pszCurLine[nIdx+1] == L' ' && isDigit(pszCurLine[nIdx+2]))
		nIdx += 2; // два лидирующих пробела перед цифрой
	else if (!isDigit(pszCurLine[nIdx]))
	{
		// Строка начинается НЕ с цифры. Может начинается одним из известных префиксов (ChkDsk)?

		if (!wcsncmp(pszCurLine, szComplRus, nComplRusLen))
		{
			nIdx += nComplRusLen;

			if (pszCurLine[nIdx] == L' ') nIdx++;

			if (pszCurLine[nIdx] == L' ') nIdx++;

			bAllowDot = true;
		}
		else if (!wcsncmp(pszCurLine, szComplEng, nComplEngLen))
		{
			nIdx += nComplEngLen;

			if (pszCurLine[nIdx] == L' ') nIdx++;

			if (pszCurLine[nIdx] == L' ') nIdx++;

			bAllowDot = true;
		}
		else if (!wcsncmp(pszCurLine, L"[#", 2))
		{
			const wchar_t* p = wcsstr(pszCurLine, L"%) ");
			while ((p > pszCurLine) && (p[-1] != L'('))
				p--;
			if (p > pszCurLine)
				nIdx = p - pszCurLine;
		}

		// Известных префиксов не найдено, проверяем, может процент есть в конце строки?
		if (!nIdx)
		{
			//TODO("Не работает с одной цифрой");
			// Creating archive T:\From_Work\VMWare\VMWare.part006.rar
			// ...       Vista x86\Vista x86.7z         6%
			int i = nWidth - 1;

			// Откусить trailing spaces
			while ((i > 3) && (pszCurLine[i] == L' '))
				i--;

			// Теперь, если дошли до '%' и перед ним - цифра
			if (i >= 3 && pszCurLine[i] == L'%' && isDigit(pszCurLine[i-1]))
			{
				//i -= 2;
				i--;

				int j = i, k = -1;
				while (j > 0 && isDigit(pszCurLine[j-1]))
					j--;

				// Может быть что-то типа "Progress 25.15%"
				if (((i - j) <= 2) && (j >= 2) && isDot(pszCurLine[j-1]))
				{
					k = j - 1;
					while (k > 0 && isDigit(pszCurLine[k-1]))
						k--;
				}

				if (k >= 0)
				{
					if (((j - k) <= 3) // 2 цифры + точка
						|| (((j - k) <= 4) && (pszCurLine[k] == L'1'))) // "100.0%"
					{
						nIdx = i = k;
						bAllowDot = true;
					}
				}
				else
				{
					if (((j - i) <= 2) // 2 цифры + точка
						|| (((j - i) <= 3) && (pszCurLine[j] == L'1'))) // "100%"
					{
						nIdx = i = j;
					}
				}

				#if 0
				// Две цифры перед '%'?
				if (isDigit(pszCurLine[i-1]))
					i--;

				// Три цифры допускается только для '100%'
				if (pszCurLine[i-1] == L'1' && !isDigit(pszCurLine[i-2]))
				{
					nIdx = i - 1;
				}
				// final check
				else if (!isDigit(pszCurLine[i-1]))
				{
					nIdx = i;
				}
				#endif

				// Может ошибочно детектировать прогресс, если его ввести в prompt
				// Допустим, что если в строке есть символ '>' - то это не прогресс
				while (i>=0)
				{
					if (pszCurLine[i] == L'>')
					{
						nIdx = 0;
						break;
					}

					i--;
				}
			}
		}
	}

	// Менять nProgress только если нашли проценты в строке с курсором
	if (isDigit(pszCurLine[nIdx]))
	{
		if (isDigit(pszCurLine[nIdx+1]) && isDigit(pszCurLine[nIdx+2])
			&& (pszCurLine[nIdx+3]==L'%' || (bAllowDot && isDot(pszCurLine[nIdx+3]))
				|| !wcsncmp(pszCurLine+nIdx+3,szPercentEng,nPercentEngLen)
				|| !wcsncmp(pszCurLine+nIdx+3,szPercentRus,nPercentRusLen)))
		{
			nProgress = 100*(pszCurLine[nIdx] - L'0') + 10*(pszCurLine[nIdx+1] - L'0') + (pszCurLine[nIdx+2] - L'0');
		}
		else if (isDigit(pszCurLine[nIdx+1])
			&& (pszCurLine[nIdx+2]==L'%' || (bAllowDot && isDot(pszCurLine[nIdx+2]))
				|| !wcsncmp(pszCurLine+nIdx+2,szPercentEng,nPercentEngLen)
				|| !wcsncmp(pszCurLine+nIdx+2,szPercentRus,nPercentRusLen)))
		{
			nProgress = 10*(pszCurLine[nIdx] - L'0') + (pszCurLine[nIdx+1] - L'0');
		}
		else if (pszCurLine[nIdx+1]==L'%' || (bAllowDot && isDot(pszCurLine[nIdx+1]))
			|| !wcsncmp(pszCurLine+nIdx+1,szPercentEng,nPercentEngLen)
			|| !wcsncmp(pszCurLine+nIdx+1,szPercentRus,nPercentRusLen))
		{
			nProgress = (pszCurLine[nIdx] - L'0');
		}
	}

	if (nProgress != -1)
	{
		mp_RCon->setLastConsoleProgress(nProgress, true); // его обновляем всегда
	}
	else
	{
		DWORD nDelta = GetTickCount() - mp_RCon->m_Progress.LastConProgrTick;
		if (nDelta < CONSOLEPROGRESSTIMEOUT) // Если таймаут предыдущего значения еще не наступил
			nProgress = mp_RCon->m_Progress.ConsoleProgress; // возъмем предыдущее значение
		mp_RCon->setLastConsoleProgress(-1, false); // его обновляем всегда
	}

	return nProgress;
}