BOOL WINAPI HookHotPatch(void **pTarget, const void *pDetour)
{
#pragma pack(push, 1)
	typedef struct
	{
		unsigned char	nJumpInst;
		unsigned long	nRelativeAddr;
		unsigned short	nHotPatch;
	} HOT_PATCH;
#pragma pack(pop)

	HOT_PATCH *pPatch;
	DWORD op = 0;
	const unsigned char *pHook;
	const unsigned char *pDestination;

	static const unsigned char nJumpBack[] = { 0xEB, 0xF9 };

	pHook = (const unsigned char *)(*pTarget);

	if (HOTPATCH_HEAD != *((const unsigned short *)pHook))
		return FALSE;

	pDestination	= (const unsigned char *)(pDetour);
	pPatch			= (HOT_PATCH *)(pHook - JMP_SIZE);

	if (FALSE == VirtualProtect(pPatch, sizeof(HOT_PATCH), PAGE_EXECUTE_READWRITE, &op))
		return FALSE;

	pPatch->nJumpInst		= JMP_INSTR;
	pPatch->nRelativeAddr	= PtrToLong(pDestination - pHook);
	pPatch->nHotPatch		= *(const unsigned short *)nJumpBack;

	(*pTarget) = (void *)(pHook + 2);

	VirtualProtect(pPatch, sizeof(HOT_PATCH), op, &op);

	return TRUE;
}