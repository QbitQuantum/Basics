void WriteTweetsToFile(PPROGRAM_CONTEXT ProgramContext, PFILE_WRITER_CONTEXT FileWriterContext)
{
	for(PTWEET Tweet = ProgramContext->NodeContext.Data; Tweet != ProgramContext->NodeContext.Data + ProgramContext->NodeContext.ElementsPerNode; Tweet++)
	{		
#ifdef WRITE_DEBUG_INFO_TO_FILE
		PrintTweetDebugInfoToStream(FileWriterContext->OutputFile, ProgramContext, Tweet);
#endif	
		fputws(ProgramContext->TweetStrings + Tweet->TweetStringOffset, FileWriterContext->OutputFile);
		fputwc(L'\n', FileWriterContext->OutputFile);
	}	
}