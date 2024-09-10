static void frontend_xdk_get_environment_settings(int *argc, char *argv[],
      void *args, void *params_data)
{
   HRESULT ret;
#ifdef _XBOX360
   unsigned long license_mask;
   DWORD volume_device_type;
#endif
#ifndef IS_SALAMANDER
   static char path[PATH_MAX_LENGTH] = {0};
#if defined(_XBOX1)
   LAUNCH_DATA ptr;
   DWORD launch_type;
#elif defined(_XBOX360)
   DWORD dwLaunchDataSize;
#endif
#endif
#ifndef IS_SALAMANDER
   bool original_verbose       = verbosity_is_enabled();
#endif

   (void)ret;

#ifndef IS_SALAMANDER
#if defined(HAVE_LOGGER)
   logger_init();
#elif defined(HAVE_FILE_LOGGER)
   retro_main_log_file_init("/retroarch-log.txt");
#endif
#endif

#ifdef _XBOX360
   /* Detect install environment. */
   if (XContentGetLicenseMask(&license_mask, NULL) == ERROR_SUCCESS)
   {
      XContentQueryVolumeDeviceType("GAME",&volume_device_type, NULL);

      switch(volume_device_type)
      {
         case XCONTENTDEVICETYPE_HDD: /* Launched from content package on HDD */
         case XCONTENTDEVICETYPE_MU:  /* Launched from content package on USB/Memory Unit. */
         case XCONTENTDEVICETYPE_ODD: /* Launched from content package on Optial Disc Drive. */
         default:                     /* Launched from content package on unknown device. */
            break;
      }
   }
#endif

#if defined(_XBOX1)
   strlcpy(g_defaults.dirs[DEFAULT_DIR_CORE],
         "D:", sizeof(g_defaults.dirs[DEFAULT_DIR_CORE]));
   fill_pathname_join(g_defaults.path.config, g_defaults.dirs[DEFAULT_DIR_CORE],
         file_path_str(FILE_PATH_MAIN_CONFIG), sizeof(g_defaults.path.config));
   fill_pathname_join(g_defaults.dirs[DEFAULT_DIR_SAVESTATE],
         g_defaults.dirs[DEFAULT_DIR_CORE],
         "savestates",
         sizeof(g_defaults.dirs[DEFAULT_DIR_SAVESTATE]));
   fill_pathname_join(g_defaults.dirs[DEFAULT_DIR_SRAM],
         g_defaults.dirs[DEFAULT_DIR_CORE],
         "savefiles",
         sizeof(g_defaults.dirs[DEFAULT_DIR_SRAM]));
   fill_pathname_join(g_defaults.dirs[DEFAULT_DIR_SYSTEM],
         g_defaults.dirs[DEFAULT_DIR_CORE],
         "system",
         sizeof(g_defaults.dirs[DEFAULT_DIR_SYSTEM]));
   fill_pathname_join(g_defaults.dirs[DEFAULT_DIR_SCREENSHOT],
         g_defaults.dirs[DEFAULT_DIR_CORE],
         "screenshots",
         sizeof(g_defaults.dirs[DEFAULT_DIR_SCREENSHOT]));
   fill_pathname_join(g_defaults.dirs[DEFAULT_DIR_OVERLAY],
         g_defaults.dirs[DEFAULT_DIR_CORE],
         "overlays",
         sizeof(g_defaults.dirs[DEFAULT_DIR_OVERLAY]));
   fill_pathname_join(g_defaults.dirs[DEFAULT_DIR_ASSETS],
         g_defaults.dirs[DEFAULT_DIR_CORE],
         "media", sizeof(g_defaults.dirs[DEFAULT_DIR_ASSETS]));
   fill_pathname_join(g_defaults.dirs[DEFAULT_DIR_CORE_ASSETS],
         g_defaults.dirs[DEFAULT_DIR_CORE],
         "downloads", sizeof(g_defaults.dirs[DEFAULT_DIR_CORE_ASSETS]));
   fill_pathname_join(g_defaults.dirs[DEFAULT_DIR_PLAYLIST],
         g_defaults.dirs[DEFAULT_DIR_CORE],
         "playlists", sizeof(g_defaults.dirs[DEFAULT_DIR_PLAYLIST]));
#elif defined(_XBOX360)
   strlcpy(g_defaults.dirs[DEFAULT_DIR_CORE],
         "game:",
         sizeof(g_defaults.dirs[DEFAULT_DIR_CORE]));
   strlcpy(g_defaults.path.config,
         "game:\\retroarch.cfg", sizeof(g_defaults.path.config));
   strlcpy(g_defaults.dirs[DEFAULT_DIR_SCREENSHOT],
         "game:",
         sizeof(g_defaults.dirs[DEFAULT_DIR_SCREENSHOT]));
   strlcpy(g_defaults.dirs[DEFAULT_DIR_SAVESTATE],
         "game:\\savestates",
         sizeof(g_defaults.dirs[DEFAULT_DIR_SAVESTATE]));
   strlcpy(g_defaults.dirs[DEFAULT_DIR_PLAYLIST],
         "game:\\playlists",
         sizeof(g_defaults.dirs[DEFAULT_DIR_PLAYLIST]));
   strlcpy(g_defaults.dirs[DEFAULT_DIR_SRAM],
         "game:\\savefiles",
         sizeof(g_defaults.dirs[DEFAULT_DIR_SRAM]));
   strlcpy(g_defaults.dirs[DEFAULT_DIR_SYSTEM],
         "game:\\system", sizeof(g_defaults.dirs[DEFAULT_DIR_SYSTEM]));
#endif
   fill_pathname_join(g_defaults.dirs[DEFAULT_DIR_CORE_INFO],
         g_defaults.dirs[DEFAULT_DIR_CORE],
         "info", sizeof(g_defaults.dirs[DEFAULT_DIR_CORE_INFO]));

#ifndef IS_SALAMANDER
#if defined(_XBOX1)
   if (XGetLaunchInfo(&launch_type, &ptr) == ERROR_SUCCESS)
   {
      char *extracted_path = NULL;
      if (launch_type == LDT_FROM_DEBUGGER_CMDLINE)
         goto exit;

      extracted_path = (char*)&ptr.Data;

      if (
            !string_is_empty(extracted_path)
            && (strstr(extracted_path, "Pool") == NULL)
            /* Hack. Unknown problem */)
      {
         /* Auto-start game */
         strlcpy(path, extracted_path, sizeof(path));
      }
   }
#elif defined(_XBOX360)
   if (XGetLaunchDataSize(&dwLaunchDataSize) == ERROR_SUCCESS)
   {
      char *extracted_path                 = (char*)calloc(dwLaunchDataSize, sizeof(char));
      BYTE* pLaunchData                    = (BYTE*)calloc(dwLaunchDataSize, sizeof(BYTE));

      XGetLaunchData(pLaunchData, dwLaunchDataSize);
      memset(extracted_path, 0, dwLaunchDataSize);

      strlcpy(extracted_path, pLaunchData, dwLaunchDataSize);

      /* Auto-start game */
      if (!string_is_empty(extracted_path))
         strlcpy(path, extracted_path, sizeof(path));

      if (pLaunchData)
         free(pLaunchData);
   }
#endif
   if (!string_is_empty(path))
   {
      struct rarch_main_wrap *args = (struct rarch_main_wrap*)params_data;

      if (args)
      {
         /* Auto-start game. */
         args->touched        = true;
         args->no_content     = false;
         args->verbose        = false;
         args->config_path    = NULL;
         args->sram_path      = NULL;
         args->state_path     = NULL;
         args->content_path   = path;
         args->libretro_path  = NULL;
      }
   }
#endif

#ifndef IS_SALAMANDER
#ifdef _XBOX1
exit:
   if (original_verbose)
      verbosity_enable();
   else
      verbosity_disable();
#endif
#endif
}