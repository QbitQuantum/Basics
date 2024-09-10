static void *
xmlModulePlatformOpen(const char *name)
{
	return LoadLibraryA(name);
}