void
Test_OneParamRoutine_BeginDeferWindowPos(void) /* 0x1e */
{
	HDWP hWinPosInfo;

	hWinPosInfo = (HDWP)NtUserCallOneParam(5, 0x1e);
	TEST(hWinPosInfo != 0);
	TEST(EndDeferWindowPos(hWinPosInfo) != 0);

}