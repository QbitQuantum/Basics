static LRESULT
HOTKEY_SetFocus (HOTKEY_INFO *infoPtr)
{
    infoPtr->bFocus = TRUE;

    CreateCaret (infoPtr->hwndSelf, NULL, 1, infoPtr->nHeight);
    SetCaretPos (infoPtr->CaretPos, GetSystemMetrics(SM_CYBORDER));
    ShowCaret (infoPtr->hwndSelf);

    return 0;
}