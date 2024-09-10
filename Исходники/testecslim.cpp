void Display(char* fmt,...) {
    const size_t size = 1024;
    char buf[size];
    va_list ap;
    va_start(ap, fmt);
    int n = vsnprintf(buf, size, fmt, ap);
    va_end(ap);

    DWORD nCharsWritten;
    char fullbuf[size];
    sprintf(fullbuf, "%*s", depth, "");
    strcat(fullbuf, buf);
    FILE* f = fopen("c:\\dart_bleeding\\trace.log", "a+");
    fprintf(f, "%s", fullbuf);
    fclose(f);
    va_end(ap);
//  WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), fullbuf, strlen(fullbuf), &nCharsWritten, NULL);
    return;

    WCHAR wfullbuf[size];
    _swprintf(wfullbuf, _T("%*s"), depth, _T(""));

    WCHAR wbuf[size];
    mbstowcs(wbuf, buf, strlen(buf));
    wbuf[strlen(buf)] = L'\0';
    wcscat(wfullbuf, wbuf);

    //WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), wfullbuf, wcslen(wfullbuf), &nCharsWritten, NULL);
    //wprintf(wfullbuf);
    //WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), wfullbuf, wcslen(wfullbuf),&nCharsWritten,NULL);
}