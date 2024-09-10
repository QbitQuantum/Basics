/**
 * Exit point from the plugin.
 *
 * @param cls the plugin context (as returned by "init")
 * @return always NULL
 */
void *
libgnunet_plugin_datastore_sqlite_done (void *cls)
{
  char *fn;
  struct GNUNET_DATASTORE_PluginFunctions *api = cls;
  struct Plugin *plugin = api->cls;

  GNUNET_log_from (GNUNET_ERROR_TYPE_DEBUG, "sqlite",
                   "sqlite plugin is done\n");
  fn = NULL;
  if (plugin->drop_on_shutdown)
    fn = GNUNET_strdup (plugin->fn);
  GNUNET_log_from (GNUNET_ERROR_TYPE_DEBUG, "sqlite",
                   "Shutting down database\n");
  database_shutdown (plugin);
  plugin->env = NULL;
  GNUNET_free (api);
  if (fn != NULL)
  {
    if (0 != UNLINK (fn))
      GNUNET_log_strerror_file (GNUNET_ERROR_TYPE_WARNING, "unlink", fn);
    GNUNET_free (fn);
  }
  GNUNET_log_from (GNUNET_ERROR_TYPE_DEBUG, "sqlite",
                   "sqlite plugin is finished\n");
  return NULL;
}