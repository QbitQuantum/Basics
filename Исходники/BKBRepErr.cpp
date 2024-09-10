//============================================================================================
// Для ошибок Tobii Gaze SDK (перегружена)
//============================================================================================
void BKBReportError(tobiigaze_error_code tbg_error_code, TCHAR *SourceFile, TCHAR *FuncName, int LineNumber)
{
	TCHAR BKBMessage[1024];	// Это строка, в которой формируется сообщение об ошибке
	TCHAR ConvertASCII2W[1024];

	if (tbg_error_code)
    {
		const TCHAR *tmp_char;
		if(fp_tobiigaze_get_error_message)
		{
			MultiByteToWideChar(CP_ACP, 0, (*fp_tobiigaze_get_error_message)(tbg_error_code), -1, ConvertASCII2W, 1023);
			tmp_char=ConvertASCII2W;
		}
		else tmp_char=Internat::Message(24,L"неизвестно");

		// Сформировать строку с полным описанием ошибки
		swprintf_s(BKBMessage, _countof(BKBMessage),
			Internat::Message(25,L"Module: %s\nFunction: %s\nLine number: %d\nОшибка Tobii Gaze SDK: %d (%s)"),
			SourceFile, FuncName, LineNumber,
			tbg_error_code, 
			tmp_char);


		//Печатаем сообщение об ошибке (если возможно, на экран)
		BKBMessageBox(NULL,BKBMessage,Internat::Message(26,L"BKB:Gaze SDK: сообщение об ошибке"),MB_OK|MB_ICONINFORMATION );

		//А также в файл 
		FILE *fout;
		fopen_s(&fout,"reperr.log","ab");

		time_t mytime = time(0); /* not 'long' */
		TCHAR ctbuf[1024];
		_wctime_s(ctbuf,1023,&mytime);
		
		fwprintf(fout,L"****\n%s%s\n", ctbuf, BKBMessage);
		fflush(fout);
		fclose(fout);
	}
}