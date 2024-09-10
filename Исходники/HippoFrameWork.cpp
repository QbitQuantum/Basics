void Hippo_WriteConsole(CONSOLE_COLOR color,char *szstr,... )
{
	DWORD numWritten = 0;
	static char szParsedString[1024];

	va_list va;
	va_start( va, szstr );
	vsprintf( szParsedString,szstr, va );
	va_end( va );

	SetConsoleTextAttribute(g_hippo_state->m_console_handle, MakeColor(color));

	WriteConsoleA(g_hippo_state->m_console_handle,szParsedString, (DWORD)strlen(szParsedString),&numWritten,0);
	WriteConsoleA(g_hippo_state->m_console_handle,"\n", 1,&numWritten,0);
}