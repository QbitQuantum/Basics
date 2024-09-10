/*
 * @unimplemented
 */
VOID
WINAPI
FatalAppExitA(UINT uAction,
              LPCSTR lpMessageText)
{
    UNICODE_STRING MessageTextU;
    ANSI_STRING MessageText;

    RtlInitAnsiString(&MessageText, (LPSTR)lpMessageText);

    RtlAnsiStringToUnicodeString(&MessageTextU,
                                 &MessageText,
                                 TRUE);

    FatalAppExitW(uAction, MessageTextU.Buffer);

    RtlFreeUnicodeString(&MessageTextU);
}