void nullpointer(int value) {
    int res = 0;
    FILE *fp;

    // cppcheck-suppress nullPointer
    clearerr(0);
    // cppcheck-suppress ignoredReturnValue
    // cppcheck-suppress nullPointer
    feof(0);
    // cppcheck-suppress nullPointer
    fgetc(0);
    // cppcheck-suppress nullPointer
    fclose(0);
    // cppcheck-suppress ignoredReturnValue
    // cppcheck-suppress nullPointer
    ferror(0);
    // cppcheck-suppress nullPointer
    ftell(0);
    // cppcheck-suppress nullPointer
    puts(0);
    // cppcheck-suppress nullPointer
    fp=fopen(0,0);
    fclose(fp);
    fp = 0;
    // No FP
    fflush(0);
    // No FP
    // cppcheck-suppress redundantAssignment
    fp = freopen(0,"abc",stdin);
    fclose(fp);
    fp = 0;
    // cppcheck-suppress nullPointer
    fputc(0,0);
    // cppcheck-suppress nullPointer
    fputs(0,0);
    // cppcheck-suppress nullPointer
    fgetpos(0,0);
    // cppcheck-suppress nullPointer
    frexp(1.0,0);
    // cppcheck-suppress nullPointer
    fsetpos(0,0);
    // cppcheck-suppress nullPointer
    itoa(123,0,10);
    putchar(0);
    // cppcheck-suppress ignoredReturnValue
    // cppcheck-suppress nullPointer
    strchr(0,0);
    // cppcheck-suppress ignoredReturnValue
    // cppcheck-suppress nullPointer
    strlen(0);
    // cppcheck-suppress nullPointer
    strcpy(0,0);
    // cppcheck-suppress ignoredReturnValue
    // cppcheck-suppress nullPointer
    strspn(0,0);
    // cppcheck-suppress ignoredReturnValue
    // cppcheck-suppress nullPointer
    strcspn(0,0);
    // cppcheck-suppress ignoredReturnValue
    // cppcheck-suppress nullPointer
    strcoll(0,0);
    // cppcheck-suppress nullPointer
    strcat(0,0);
    // cppcheck-suppress ignoredReturnValue
    // cppcheck-suppress nullPointer
    strcmp(0,0);
    // cppcheck-suppress nullPointer
    strncpy(0,0,1);
    // cppcheck-suppress nullPointer
    strncat(0,0,1);
    // cppcheck-suppress ignoredReturnValue
    // cppcheck-suppress nullPointer
    strncmp(0,0,1);
    // cppcheck-suppress ignoredReturnValue
    // cppcheck-suppress nullPointer
    strstr(0,0);
    // cppcheck-suppress nullPointer
    strtoul(0,0,0);
    // cppcheck-suppress nullPointer
    strtoull(0,0,0);
    // cppcheck-suppress nullPointer
    strtol(0,0,0);

    // #6100 False positive nullPointer - calling mbstowcs(NULL,)
    res += mbstowcs(0,"",0);
    // cppcheck-suppress unreadVariable
    res += wcstombs(0,L"",0);

    strtok(NULL,"xyz");

    strxfrm(0,"foo",0);
    // TODO: error message
    strxfrm(0,"foo",42);

    snprintf(NULL, 0, "someformatstring"); // legal
    // cppcheck-suppress nullPointer
    snprintf(NULL, 42, "someformatstring"); // not legal
}