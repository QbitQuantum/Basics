extern "C" int __declspec(dllexport) Load(PLUGINLINK *link)
{
	char text[_MAX_PATH];
	char *p, *q;
	GetModuleFileName(hInst, text, sizeof(text));
	p = strrchr(text, '\\');
	p++;
	q = strrchr(p, '.');
	*q = '\0';
	muccModuleName = _strdup(p);
	_strupr(muccModuleName);

	pluginLink = link;
	/*
	**	HookEvent(ME_OPT_INITIALISE, TlenOptInit);
	*/
	HookEvent(ME_OPT_INITIALISE, MUCCOptInit);
	HookEvent(ME_SYSTEM_MODULESLOADED, ModulesLoaded);
	HookEvent(ME_SYSTEM_PRESHUTDOWN, PreShutdown);

	CreateServiceFunction(MS_MUCC_QUERY_RESULT, MUCCQueryResult);
	CreateServiceFunction(MS_MUCC_NEW_WINDOW, MUCCNewWindow);
	CreateServiceFunction(MS_MUCC_EVENT, MUCCEvent);
	hHookEvent = CreateHookableEvent(ME_MUCC_EVENT);

	LoadIcons();
	return 0;
}