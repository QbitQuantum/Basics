CWE427_Uncontrolled_Search_Path_Element__wchar_t_environment_83_bad::~CWE427_Uncontrolled_Search_Path_Element__wchar_t_environment_83_bad()
{
    /* POTENTIAL FLAW: Set a new environment variable with a path that is possibly insecure */
    PUTENV(data);
}