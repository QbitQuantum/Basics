void cmd_version(UBool noLoad)
{
    UVersionInfo icu;
    char str[200];
    printf("<ICUINFO>\n");
    printf("International Components for Unicode for C/C++\n");
    printf("%s\n", U_COPYRIGHT_STRING);
    printf("Compiled-Version: %s\n", U_ICU_VERSION);
    u_getVersion(icu);
    u_versionToString(icu, str);
    printf("Runtime-Version: %s\n", str);
    printf("Compiled-Unicode-Version: %s\n", U_UNICODE_VERSION);
    u_getUnicodeVersion(icu);
    u_versionToString(icu, str);
    printf("Runtime-Unicode-Version: %s\n", U_UNICODE_VERSION);
    printf("Platform: %s\n", getPlatform());
#if defined(U_BUILD)
    printf("Build: %s\n", U_BUILD);
#if defined(U_HOST)
    if(strcmp(U_BUILD,U_HOST)) {
      printf("Host: %s\n", U_HOST);
    }
#endif
#endif
#if defined(U_CC)
    printf("C compiler: %s\n", U_CC);
#endif
#if defined(U_CXX)
    printf("C++ compiler: %s\n", U_CXX);
#endif
#if defined(CYGWINMSVC)
    printf("Cygwin: CYGWINMSVC\n");
#endif
    printf("ICUDATA: %s\n", U_ICUDATA_NAME);
    do_init();
    printf("Data Directory: %s\n", u_getDataDirectory());
    printf("ICU Initialization returned: %s\n", u_errorName(initStatus));
    printf( "Default locale: %s\n", uloc_getDefault());
    {
      UErrorCode subStatus = U_ZERO_ERROR;
      ulocdata_getCLDRVersion(icu, &subStatus);
      if(U_SUCCESS(subStatus)) {
	u_versionToString(icu, str);
	printf("CLDR-Version: %s\n", str);
      } else {
	printf("CLDR-Version: %s\n", u_errorName(subStatus));
      }
    }
    
#if !UCONFIG_NO_CONVERSION
    if(noLoad == FALSE)
    {
      printf("Default converter: %s\n", ucnv_getDefaultName());
    }
#endif
#if !UCONFIG_NO_FORMATTING
    {
      UChar buf[100];
      char buf2[100];
      UErrorCode subsubStatus= U_ZERO_ERROR;
      int32_t len;

      len = ucal_getDefaultTimeZone(buf, 100, &subsubStatus);
      if(U_SUCCESS(subsubStatus)&&len>0) {
	u_UCharsToChars(buf, buf2, len+1);
	printf("Default TZ: %s\n", buf2);
      } else {
	printf("Default TZ: %s\n", u_errorName(subsubStatus));
      }
    }
    {
      UErrorCode subStatus = U_ZERO_ERROR;
      const char *tzVer = ucal_getTZDataVersion(&subStatus);
      if(U_FAILURE(subStatus)) {
	tzVer = u_errorName(subStatus);
      }
      printf("TZ data version: %s\n", tzVer);
    }
#endif
    
#if U_ENABLE_DYLOAD
    const char *pluginFile = uplug_getPluginFile();
    printf("Plugin file is: %s\n", (pluginFile&&*pluginFile)?pluginFile:"(not set. try setting ICU_PLUGINS to a directory.)");
#else
    fprintf(stderr, "Dynamic Loading: is disabled. No plugins will be loaded at start-up.\n");
#endif
    printf("</ICUINFO>\n\n");
}