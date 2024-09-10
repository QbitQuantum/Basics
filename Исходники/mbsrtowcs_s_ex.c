int main()
{
    const char *mbptr = "Any multibyte string";
    wchar_t wcstr[10];            // A buffer for wide characters
    size_t len;                   // and its capacity.
    mbstate_t state = {0};

    if( mbsrtowcs_s( &len, wcstr, 10, &mbptr, 9, &state) != 0)
        printf("The array contains an invalid multibyte character.\n");
    else
    {
       printf("Length: %zu; text: %ls\n", len, wcstr);
       printf("The remaining characters: %s\n", mbptr);
    }
    return 0;
}