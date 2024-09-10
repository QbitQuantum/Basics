static char *
UpperCase(const char *text)
{
    while (isspace(*text))
        text++;
    char *temp = new char[strlen(text)+1];
    strcpy(temp, text);
    for (int n = strlen(temp); n > 0; n--)
        if (isspace(temp[n-1]))
            temp[--n] = 0;
    StrUpr(temp);
    return temp;
}