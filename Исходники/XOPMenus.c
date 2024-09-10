void
WMDeleteMenu(short menuID)
{
	if (!CheckRunningInMainThread("WMDeleteMenu"))
		return;
	DeleteMenu(menuID);
}