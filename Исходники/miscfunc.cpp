/*
	IME 制御
*/
BOOL SetImeOpenStatus(HWND hWnd, BOOL flg)
{
    BOOL ret = FALSE;

    HIMC hImc;

    if ((hImc = ImmGetContext(hWnd)))
    {
        ret = ImmSetOpenStatus(hImc, flg);
        ImmReleaseContext(hWnd, hImc);
    }
    return	ret;
}