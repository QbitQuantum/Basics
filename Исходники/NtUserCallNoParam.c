INT
Test_NoParamRoutine_CreatePopupMenu(PTESTINFO pti) /* 1 */
{
	HMENU hMenu;

	hMenu = (HMENU)NtUserCallNoParam(_NOPARAM_ROUTINE_CREATEMENUPOPUP);
	TEST(IsMenu(hMenu) == TRUE);
	DestroyMenu(hMenu);

	return APISTATUS_NORMAL;
}