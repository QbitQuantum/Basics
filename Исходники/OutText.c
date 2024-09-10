void OutT_LogStop()
{
	if (!WriteToLog)
	{
		OutDbg("Log non actif");
		return;
	}
	OutDbg("Arrêt du log...");
	
	if (LogBufCount)
	{
		if (!CreateLogFile())
		{
			PutString2Log("</font>\n</font>\n</body>\n</html>");
			WriteToLog = false;
			
			if (Fat12_WriteFile(&LogFile,LogBufCount,&LogBuf[0]))
			{	
				OutDbgColor(12,"Ah zut buffer du log écrit, erreur d'écriture...");
			}
			else
			{
				OutDbg("Buffer du log écrit.");
			}
			Fat12_CloseFile(&LogFile);
		}
	}
	
	WriteToLog = false;
}