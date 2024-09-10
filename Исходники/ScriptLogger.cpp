void ScriptLogger::Log(const char* fmt, char* args)
{
	char* argStart = args;

	if(logFile)
	{
		FILE *f;
		_wfopen_s(&f, logFile, L"a");
		if(f)
		{
			vfprintf_s(f, fmt, args);
			fclose(f);
		}
	}

	args = argStart;

	char buffer[MAX_LINE_LENGTH];
	int charsWritten = vsnprintf_s(buffer, MAX_LINE_LENGTH, _TRUNCATE, fmt, args);
	std::string logline(buffer);
	if(charsWritten == -1) logline += "...";

	int firstNewline = -1;
	while((firstNewline = logline.find("\n")) != -1)
	{
		logLines[currentLine].append(logline.substr(0, firstNewline));
		logline = logline.substr(firstNewline + strlen("\n"));
		currentLine = (currentLine + 1 < numLines ? currentLine + 1 : 0);
		logLines[currentLine].clear();
	}
	logLines[currentLine].append(logline.c_str());

	args = argStart;

	vprintf(fmt, args);

	args = argStart;
}