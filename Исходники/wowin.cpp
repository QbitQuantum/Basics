void CloseConsole(){//关闭控制台
#ifdef _OUT
//	fclose(g_stdOut);
	FreeConsole();
#endif
}