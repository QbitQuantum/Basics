CWE36_Absolute_Path_Traversal__wchar_t_file_fopen_84_bad::~CWE36_Absolute_Path_Traversal__wchar_t_file_fopen_84_bad()
{
    {
        FILE *pFile = NULL;
        /* POTENTIAL FLAW: Possibly opening a file without validating the file name or path */
        pFile = FOPEN(data, L"wb+");
        if (pFile != NULL)
        {
            fclose(pFile);
        }
    }
}