int __cdecl wmain(int argc, wchar_t* argv[])
{
    UNREFERENCED_PARAMETER(argc);
    // Enumerate all the locales and report on them
    EnumSystemLocalesEx( MyFuncLocaleEx, LOCALE_ALL, (LPARAM)argv, NULL);
    // See which of the input locales are valid (if any)
    if (*argv && argv[1])
    {
	// Check each argument to see if our locale matches
        for (int i = 1; argv[i] != 0; i++)
        {
	    // See if this is a valid locale name 
            if (!IsValidLocaleName(argv[i]))
            {
                wprintf(L"%s is not a valid locale name\n", argv[i]);
                system("Pause");
            }
        }
    }
}