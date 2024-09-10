DDEstring::DDEstring(const char *name) : hSz(NULL)
{
    /*
	Was aeeror with invalid converting to (CHAR*)
    */	
    hSz = DdeCreateStringHandleA(*DDEbase::base, (CHAR*)name, CP_WINANSI);
}