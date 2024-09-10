static void free_list(LPWSTR *list, DWORD count)
{
    LONG i;

    for (i = 0; i < count; i++)
        MIDL_user_free(list[i]);

    MIDL_user_free(list);
}