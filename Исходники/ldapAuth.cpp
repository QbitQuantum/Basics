/*  PrintBanner()   -       Prints a banner to the screen
 
    Parameters
 
                LPOLESTR pwszBanner   - String to print
*/
void PrintBanner(LPOLESTR pwszBanner)
{
    _putws(L"");
    _putws(L"////////////////////////////////////////////////////");
    wprintf(L"\t");
    _putws(pwszBanner);
    _putws(L"////////////////////////////////////////////////////\n");
}