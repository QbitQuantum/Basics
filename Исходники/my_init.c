static void my_win_init(void)
{
  DBUG_ENTER("my_win_init");

#if defined(_MSC_VER)
#if _MSC_VER < 1300
  /* 
    Clear the OS system variable TZ and avoid the 100% CPU usage
    Only for old versions of Visual C++
  */
  _putenv( "TZ=" ); 
#endif 
#if _MSC_VER >= 1400
  /* this is required to make crt functions return -1 appropriately */
  _set_invalid_parameter_handler(my_parameter_handler);
#endif
#endif  
#ifdef __MSVC_RUNTIME_CHECKS
  /*
    Install handler to send RTC (Runtime Error Check) warnings
    to log file
  */
  _RTC_SetErrorFunc(handle_rtc_failure);
#endif

  _tzset();

               
               
               
               
               
               
               
               
               
               
               
               
               
               
               
               
               
               
               
               
               
               
               
               
  /* The following is used by time functions */
#define OFFSET_TO_EPOC ((__int64) 134774 * 24 * 60 * 60 * 1000 * 1000 * 10)
#define MS 10000000
  {
    FILETIME ft;
    LARGE_INTEGER li, t_cnt;
    DBUG_ASSERT(sizeof(LARGE_INTEGER) == sizeof(query_performance_frequency));
    if (QueryPerformanceFrequency((LARGE_INTEGER *)&query_performance_frequency) == 0)
      query_performance_frequency= 0;
    else
    {
      GetSystemTimeAsFileTime(&ft);
      li.LowPart=  ft.dwLowDateTime;
      li.HighPart= ft.dwHighDateTime;
      query_performance_offset= li.QuadPart-OFFSET_TO_EPOC;
      QueryPerformanceCounter(&t_cnt);
      query_performance_offset-= (t_cnt.QuadPart /
                                  query_performance_frequency * MS +
                                  t_cnt.QuadPart %
                                  query_performance_frequency * MS /
                                  query_performance_frequency);
    }
  }

  {
    /*
      Open HKEY_LOCAL_MACHINE\SOFTWARE\MySQL and set any strings found
      there as environment variables
    */
    HKEY key_handle;
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, (LPCTSTR)"SOFTWARE\\MySQL",
                     0, KEY_READ, &key_handle) == ERROR_SUCCESS)
    {
      LONG ret;
      DWORD index= 0;
      DWORD type;
      char key_name[256], key_data[1024];
      DWORD key_name_len= sizeof(key_name) - 1;
      DWORD key_data_len= sizeof(key_data) - 1;

      while ((ret= RegEnumValue(key_handle, index++,
                                key_name, &key_name_len,
                                NULL, &type, (LPBYTE)&key_data,
                                &key_data_len)) != ERROR_NO_MORE_ITEMS)
      {
        char env_string[sizeof(key_name) + sizeof(key_data) + 2];

        if (ret == ERROR_MORE_DATA)
        {
          /* Registry value larger than 'key_data', skip it */
          DBUG_PRINT("error", ("Skipped registry value that was too large"));
        }
        else if (ret == ERROR_SUCCESS)
        {
          if (type == REG_SZ)
          {
            strxmov(env_string, key_name, "=", key_data, NullS);

            /* variable for putenv must be allocated ! */
            putenv(strdup(env_string)) ;
          }
        }
        else
        {
          /* Unhandled error, break out of loop */
          break;
        }

        key_name_len= sizeof(key_name) - 1;
        key_data_len= sizeof(key_data) - 1;
      }

      RegCloseKey(key_handle) ;
    }
  }
  DBUG_VOID_RETURN ;
}