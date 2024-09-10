/**
 * Main function that will be run by the scheduler.
 *
 * @param cls closure
 * @param args remaining command-line arguments
 * @param cfgfile name of the configuration file used (for saving, can be NULL!)
 * @param cfg configuration
 */
static void
run (void *cls, char *const *args, const char *cfgfile,
     const struct GNUNET_CONFIGURATION_Handle *cfg)
{
  set_value = GNUNET_NO;
  if (NULL != args[0])
  {
    if (1 != SSCANF (args[0], "%llu", &set_val))
    {
      FPRINTF (stderr, _("Invalid argument `%s'\n"), args[0]);
      ret = 1;
      return;
    }
    set_value = GNUNET_YES;
  }
  if (NULL != remote_host)
    GNUNET_CLIENT_service_test ("resolver", cfg, GNUNET_TIME_UNIT_SECONDS,
				&resolver_test_task, (void *) cfg);
  else
    GNUNET_SCHEDULER_add_now (&main_task, (void *) cfg);
}