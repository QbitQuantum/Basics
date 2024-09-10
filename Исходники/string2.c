/*
используем Wide Char API для обработки текста
*/
int main(void)
{
    wchar_t c;
    setlocale(LC_ALL, "");
    while ((c = getwc(stdin)) != EOF) {
        wprintf(L"%Lc\n", (int) c);
    }
}