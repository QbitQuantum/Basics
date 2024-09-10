int CMaskEdit::SetValue(DWORD dwValue)
{
    char cText[32] = "";
    _ltoa(dwValue, cText, 10);
    SetWindowText(cText);
    return 0;
}