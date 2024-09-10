int
main(int argc, char *argv[])
{
   char path[PATH_MAX];
   FILE *log;

   strcpy(path, "/tmp/efreetd_XXXXXX");
   if (mkstemp(path) < 0)
     {
        perror("mkstemp");
        return 1;
     }
   if (chmod(path, 0700) < 0)
     {
        perror("chmod");
        return 1;
     }

   log = fopen(path, "wb");
   if (!log) return 1;

   if (!eina_init()) return 1;
   eina_log_print_cb_set(eina_log_print_cb_file, log);

   efreetd_log_dom = eina_log_domain_register("efreetd", EFREETD_DEFAULT_LOG_COLOR);
   if (efreetd_log_dom < 0)
     {
        EINA_LOG_ERR("Efreet: Could not create a log domain for efreetd.");
        goto ecore_error;
     }
   if (!ecore_init()) goto ecore_error;
   ecore_app_args_set(argc, (const char **)argv);
   if (!ecore_file_init()) goto ecore_file_error;

   if (!dbus_init()) goto dbus_error;
   if (!cache_init()) goto cache_error;

#ifdef HAVE_SYS_RESOURCE_H
   setpriority(PRIO_PROCESS, 0, 19);
#elif _WIN32
    SetPriorityClass(GetCurrentProcess(), IDLE_PRIORITY_CLASS);
#endif

   ecore_main_loop_begin();

   cache_shutdown();
   dbus_shutdown();
   ecore_file_shutdown();
   ecore_shutdown();
   eina_log_domain_unregister(efreetd_log_dom);
   efreetd_log_dom = -1;
   eina_shutdown();
   return 0;

cache_error:
   dbus_shutdown();
dbus_error:
   ecore_file_shutdown();
ecore_file_error:
   ecore_shutdown();
ecore_error:
   if (efreetd_log_dom >= 0)
     eina_log_domain_unregister(efreetd_log_dom);
   efreetd_log_dom = -1;
   eina_shutdown();
   return 1;
}