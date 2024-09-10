int main(int argc, char *argv[]) {
    wchar_t pw[MAX_PASS_LEN*2+1];
    char *locale;
    locale  = setlocale(LC_ALL, "");
    fwide(stdout, 1);

    if (argc != 2) {
        printf("\n  Usage: aim_decode <base64 blob>");
        printf("\n  Example: aim_decode zo+VVoi9LWCtc0B8z9ZnfojNdjVuv08DXid8yK++LYI=\n");
        return 0;
    }

    if (strlen(argv[1]) % 2 != 0) {
        printf("\n  %s doesn't appear to be valid base64 string!\n", argv[1]);
        return 0;
    }

    AIM_Decrypt(argv[1], pw);
    wprintf(L"\n  Password = \"%s\"\n", pw);
    return 0;
}