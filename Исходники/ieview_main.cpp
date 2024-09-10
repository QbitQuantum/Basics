extern "C" int __declspec(dllexport) Load(PLUGINLINK *link)
{
	char text[_MAX_PATH];
	char *p, *q;
	
	int wdsize = GetCurrentDirectory(0, NULL);
	workingDir = new char[wdsize];
	GetCurrentDirectory(wdsize, workingDir);
	Utils::convertPath(workingDir);

	GetModuleFileName(hInstance, text, sizeof(text));
	p = strrchr(text, '\\');
	p++;
	q = strrchr(p, '.');
	*q = '\0';
	ieviewModuleName = _strdup(p);
	_strupr(ieviewModuleName);

	pluginLink = link;

	HookEvent(ME_OPT_INITIALISE, IEViewOptInit);

	HookEvent(ME_SYSTEM_MODULESLOADED, ModulesLoaded);
	HookEvent(ME_SYSTEM_PRESHUTDOWN, PreShutdown);

	CreateServiceFunction(MS_IEVIEW_WINDOW, HandleIEWindow);
	CreateServiceFunction(MS_IEVIEW_EVENT, HandleIEEvent);
	CreateServiceFunction(MS_IEVIEW_SHOWSMILEYSELECTION, HandleSmileyShowSelection);
	return 0;
}