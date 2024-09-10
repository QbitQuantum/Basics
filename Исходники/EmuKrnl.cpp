// ******************************************************************
// * 0x0038 - InterlockedFlushSList()
// ******************************************************************
// Source:ReactOS
// Dxbx Note : The Xbox1 SINGLE_LIST strucures are the same as in WinNT
XBSYSAPI EXPORTNUM(56) xboxkrnl::PSINGLE_LIST_ENTRY FASTCALL xboxkrnl::KRNL(InterlockedFlushSList)
(
	IN xboxkrnl::PSLIST_HEADER ListHead
)
{
	LOG_FUNC_ONE_ARG(ListHead);

	PSINGLE_LIST_ENTRY res = (PSINGLE_LIST_ENTRY)InterlockedFlushSList((::PSLIST_HEADER)ListHead);

	RETURN(res);
}