void RARCH_LOG_V(const char *tag, const char *fmt, va_list ap)
{
#if TARGET_OS_IPHONE
   static int asl_initialized = 0;
#if !TARGET_IPHONE_SIMULATOR
static aslclient asl_client;
#endif
#else
   FILE *fp = NULL;
   (void)fp;
#endif

   if (!verbosity_is_enabled())
      return;
#if TARGET_OS_IPHONE
#if TARGET_IPHONE_SIMULATOR
   vprintf(fmt, ap);
#else
   if (!asl_initialized)
   {
      asl_client = asl_open(file_path_str(FILE_PATH_PROGRAM_NAME), "com.apple.console", ASL_OPT_STDERR | ASL_OPT_NO_DELAY);
      asl_initialized = 1;
   }
   aslmsg msg = asl_new(ASL_TYPE_MSG);
   asl_set(msg, ASL_KEY_READ_UID, "-1");
   if (tag)
      asl_log(asl_client, msg, ASL_LEVEL_NOTICE, "%s", tag);
   asl_vlog(asl_client, msg, ASL_LEVEL_NOTICE, fmt, ap);
   asl_free(msg);
#endif
#elif defined(_XBOX1)
   /* FIXME: Using arbitrary string as fmt argument is unsafe. */
   char msg_new[1024];
   char buffer[1024];

   msg_new[0] = buffer[0] = '\0';
   snprintf(msg_new, sizeof(msg_new), "%s: %s %s",
         file_path_str(FILE_PATH_PROGRAM_NAME),
         tag ? tag : "",
         fmt);
   wvsprintf(buffer, msg_new, ap);
   OutputDebugStringA(buffer);
#elif defined(ANDROID)
   int prio = ANDROID_LOG_INFO;
   if (tag)
   {
      if (string_is_equal(file_path_str(FILE_PATH_LOG_WARN), tag))
         prio = ANDROID_LOG_WARN;
      else if (string_is_equal(file_path_str(FILE_PATH_LOG_ERROR), tag))
         prio = ANDROID_LOG_ERROR;
   }
   __android_log_vprint(prio,
         file_path_str(FILE_PATH_PROGRAM_NAME),
         fmt,
         ap);
#else

#ifdef HAVE_FILE_LOGGER
   fp = (FILE*)retro_main_log_file();
#else
   fp = stderr;
#endif
   fprintf(fp, "%s %s :: ",
         file_path_str(FILE_PATH_PROGRAM_NAME),
         tag ? tag : file_path_str(FILE_PATH_LOG_INFO));
   vfprintf(fp, fmt, ap);
   fflush(fp);
#endif
}