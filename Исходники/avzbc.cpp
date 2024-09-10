VOID AddToLog(WCHAR *txt, PUNICODE_STRING txt1, ULONG *StatusCode)
{
 IO_STATUS_BLOCK		LogFileStatusBlock;
 HANDLE					LogFileHandle = 0;
 NTSTATUS				ns;
 // Проверка, разрешено ли протоколирование
 if (!EnableLog) return;
 __try {
 // Подготовка атрибутов файла
 OBJECT_ATTRIBUTES   	ob;
 InitializeObjectAttributes(&ob,
	 &usLogFile,
	 OBJ_CASE_INSENSITIVE + OBJ_KERNEL_HANDLE,
	 NULL, NULL);
 // Создание/открытие файла
 ns = ZwCreateFile(&LogFileHandle,
	               FILE_APPEND_DATA + SYNCHRONIZE,
				   &ob,
				   &LogFileStatusBlock,
				   0, FILE_ATTRIBUTE_NORMAL, 0, 
				   FILE_CREATE + FILE_OPEN, 
				   FILE_SYNCHRONOUS_IO_NONALERT, 
				   NULL, 0);
 if (ns == STATUS_SUCCESS) 
 {
	 // Буфер строки
	 WCHAR			Buffer[1024], CodeTxt[20];
	 ULONG          BuffSize = 0;
	 // Очистка буфера строки
	 RtlZeroMemory(&Buffer, sizeof(Buffer));
	 // Копирование строки
	 wcscpy(Buffer, txt);
	 // Добавление второй необязательной строки
	 if (txt1 != NULL && txt1->Buffer != NULL) {
		 __try {
			 for (int i = 0; i < txt1->Length / 2; i++)
				 if (txt1->Buffer[i] == 0)
					 txt1->Buffer[i] = L'*';
		 } __except(EXCEPTION_EXECUTE_HANDLER) {}
		 wcscat(Buffer, (wchar_t *)txt1->Buffer);
	 }
	 // Добавление парметра
	 if (StatusCode != NULL) {
		 if (*StatusCode == 0)
			 wcscat(Buffer, L" - succeeded");
		 else {
			 wcscat(Buffer, L" - failed (0x");
			 swprintf(CodeTxt, L"%X", *StatusCode);
			 wcscat(Buffer, (wchar_t *)CodeTxt);
			 wcscat(Buffer, L")");
		 }
	 }
	 // Добавление к нему CRLF	
	 wcscat(Buffer, L"\r\n");
     BuffSize = wcslen(Buffer) * 2;

	 zDbgPrint("%S", Buffer);
	 if (AnsiLog) {
		 // Преобразование буфера в ANSI
		 ANSI_STRING		AnsiString;
		 UNICODE_STRING     UnicodeString;
		 RtlInitUnicodeString(&UnicodeString, Buffer);
		 if (RtlUnicodeStringToAnsiString(&AnsiString, &UnicodeString, TRUE) == STATUS_SUCCESS)	  
			 // Запись AnsiString 
			 ns = ZwWriteFile(LogFileHandle, 0,
						NULL,NULL,
						&LogFileStatusBlock,
						AnsiString.Buffer,
						AnsiString.Length,
						NULL,NULL);
	 }
	 else 
		 // Запись буфера c UNICODE строкой
		 ns = ZwWriteFile(LogFileHandle, 0, 
		 NULL,NULL,
		 &LogFileStatusBlock,
		 Buffer,
		 BuffSize,
		 NULL,NULL);
	 ZwClose(LogFileHandle);
 }