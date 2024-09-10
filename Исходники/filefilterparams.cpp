void FileFilterParams::SetMask(bool Used, const wchar_t *Mask)
{
	FMask.Used = Used;
	FMask.strMask = Mask;
	/* Обработка %PATHEXT% */
	string strMask = FMask.strMask;
	size_t pos;

	// проверим
	if (strMask.PosI(pos,L"%PATHEXT%"))
	{
		{
			size_t IQ1=(strMask.At(pos+9) == L',' || strMask.At(pos+9) == L';')?10:9;
			wchar_t *Ptr = strMask.GetBuffer();
			// Если встречается %pathext%, то допишем в конец...
			wmemmove(Ptr+pos,Ptr+pos+IQ1,strMask.GetLength()-pos-IQ1+1);
			strMask.ReleaseBuffer();
		}
		size_t posSeparator;

		if (strMask.Pos(posSeparator, EXCLUDEMASKSEPARATOR))
		{
			if (pos > posSeparator) // PATHEXT находится в масках исключения
			{
				Add_PATHEXT(strMask); // добавляем то, чего нету.
			}
			else
			{
				string strTmp = strMask;
				strTmp.LShift(posSeparator);
				strMask.SetLength(posSeparator);
				Add_PATHEXT(strMask);
				strMask += strTmp;
			}
		}
		else
		{
			Add_PATHEXT(strMask); // добавляем то, чего нету.
		}
	}

	// Проверка на валидность текущих настроек фильтра
	if (!FMask.FilterMask.Set(strMask,FMF_SILENT))
	{
		FMask.strMask = L"*";
		FMask.FilterMask.Set(FMask.strMask,FMF_SILENT);
	}
}