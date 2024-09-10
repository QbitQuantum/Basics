void gcDDEManager::stringFromAtom(HSZ atom, char* str, size_t size)
{
	char buff[256];
	DdeQueryStringA(m_hDDEIdInst, atom, buff, 256, CP_WINANSI);
	Safe::snprintf(str, size, "%s", buff);
}