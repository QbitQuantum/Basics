int main(int argc, char *argv[])
{
   int ret;
#if defined(_XBOX)
   XINPUT_STATE state;

   get_environment_settings();

   XInputGetState(0, &state);

   if(state.Gamepad.wButtons & XINPUT_GAMEPAD_Y)
   {
      //override path, boot first executable in cores directory
      RARCH_LOG("Fallback - Will boot first executable in RetroArch cores directory.\n");
      find_and_set_first_file();
   }
   else
   {
      //normal executable loading path
      init_settings();
   }

   XLaunchNewImage(libretro_path, NULL);
   RARCH_LOG("Launch libretro core: [%s] (return code: %x]).\n", libretro_path, ret);
#elif defined(__CELLOS_LV2__)
   CellPadData pad_data;
   char spawn_data[256], spawn_data_size[16];
   SceNpDrmKey * k_licensee = NULL;

   cellSysmoduleLoadModule(CELL_SYSMODULE_IO);
   cellSysmoduleLoadModule(CELL_SYSMODULE_FS);
   cellSysmoduleLoadModule(CELL_SYSMODULE_SYSUTIL_GAME);
   cellSysmoduleLoadModule(CELL_SYSMODULE_NET);

   cellSysmoduleLoadModule(CELL_SYSMODULE_SYSUTIL_NP);

   sys_net_initialize_network();

#ifdef HAVE_LOGGER
   logger_init();
#endif

   sceNpInit(NP_POOL_SIZE, np_pool);

   get_environment_settings();

   cellPadInit(7);

   cellPadGetData(0, &pad_data);

   if(pad_data.button[CELL_PAD_BTN_OFFSET_DIGITAL2] & CELL_PAD_CTRL_TRIANGLE)
   {
      //override path, boot first executable in cores directory
      RARCH_LOG("Fallback - Will boot first executable in RetroArch cores/ directory.\n");
      find_and_set_first_file();
   }
   else
   {
      //normal executable loading path
      init_settings();
   }

   cellPadEnd();

#ifdef HAVE_LOGGER
   logger_shutdown();
#endif

   for(unsigned int i = 0; i < sizeof(spawn_data); ++i)
      spawn_data[i] = i & 0xff;

   sprintf(spawn_data_size, "%d", 256);

   const char * const spawn_argv[] = {
	   spawn_data_size,
	   "test argv for",
	   "sceNpDrmProcessExitSpawn2()",
	   NULL
   };

   ret = sceNpDrmProcessExitSpawn2(k_licensee, libretro_path, (const char** const)spawn_argv, NULL, (sys_addr_t)spawn_data, 256, 1000, SYS_PROCESS_PRIMARY_STACK_SIZE_1M);
   RARCH_LOG("Launch libretro core: [%s] (return code: %x]).\n", libretro_path, ret);

   if(ret < 0)
   {
      RARCH_LOG("Executable file is not of NPDRM type, trying another approach to boot it...\n");
      sys_game_process_exitspawn2(libretro_path, NULL, NULL, NULL, 0, 1000, SYS_PROCESS_PRIMARY_STACK_SIZE_1M);
   }

   sceNpTerm();

   sys_net_finalize_network();

   cellSysmoduleUnloadModule(CELL_SYSMODULE_SYSUTIL_NP);

   cellSysmoduleUnloadModule(CELL_SYSMODULE_NET);
   cellSysmoduleUnloadModule(CELL_SYSMODULE_SYSUTIL_GAME);
   cellSysmoduleLoadModule(CELL_SYSMODULE_FS);
   cellSysmoduleLoadModule(CELL_SYSMODULE_IO);
#endif

   return 1;
}