//显示源文件中的一行。
void DisplayLine(LPCTSTR sourceFile, const std::wstring& line, int lineNumber, BOOL isCurLine) {

	if (isCurLine == TRUE) {
		std::wcout << TEXT("=>");
	}
	else {
		std::wcout << TEXT("  ");
	}

	LONG displacement;
	IMAGEHLP_LINE64 lineInfo = { 0 };
	lineInfo.SizeOfStruct = sizeof(lineInfo);

	if (SymGetLineFromName64(
		GetDebuggeeHandle(),
		NULL,
		sourceFile,
		lineNumber, 
		&displacement,
		&lineInfo) == FALSE) {

		std::wcout << TEXT("SymGetLineFromName64 failed: ") << GetLastError() << std::endl;
		return;
	}

	std::wcout << std::setw(4) << std::setfill(TEXT(' ')) << lineNumber << TEXT("  ");

	if (displacement == 0) {

		PrintHex((unsigned int)lineInfo.Address, FALSE);
	}
	else {

		std::wcout << std::setw(8) << TEXT(" ");
	}

	std::wcout << TEXT("  ") << line << std::endl;
}