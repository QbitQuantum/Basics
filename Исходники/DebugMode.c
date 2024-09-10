/* デバッグファイルを作成し、開く */
void CreateDebugFile(void)
{
	OSErr	err;
	FSSpec	spec;
	ProcessSerialNumber	psn;
	ProcessInfoRec		processInfo;
	
	/* アプリケーションの位置を記録 */
	err=GetCurrentProcess(&psn);
	processInfo.processInfoLength=sizeof(ProcessInfoRec);
	processInfo.processName=nil;
	processInfo.processAppSpec=&spec;
	err=GetProcessInformation(&psn,&processInfo);
	
	if (err!=noErr) return;
	
	PStrCpy(kDebugFileName,spec.name);
	
	#ifdef BACKUP_LOG
	{
		/* バックアップする */
		FSSpec	bSpec=spec;
		PStrCpy(kBDebugFileName,bSpec.name);
		
		err=FSpCreate(&bSpec,kDebugFileCreator,kDebugFileType,smSystemScript);
		
		err=FSpExchangeFiles(&spec,&bSpec);
	}
	#endif
	
	/* まず消す */
	err=FSpDelete(&spec);
	
	err=FSpCreate(&spec,kDebugFileCreator,kDebugFileType,smSystemScript);
	if (err!=noErr) return;
	
	err=FSpOpenDF(&spec,fsWrPerm,&debugFileRefNum);
	if (err!=noErr) return;
}