void
CStCuiView::PrintW(
    WORD            inClr,
    LPCWSTR inFormat,
    va_list         inArgList)
{
    WORD oldClr = ChangeTextClr(inClr);
    vwprintf(inFormat, inArgList);
    ChangeTextClr(oldClr);
}