static int
prolog_history_hook(orchids_t *ctx, mod_entry_t *mod, void *data, event_t *event)
{
  prolog_history_cfg_t *cfg;
  int		i;
  event_t	*e;
  char		buff[256];

  cfg = (prolog_history_cfg_t *)mod->config;

  for (i = 0; i < cfg->time_fields_nb; i++)
    for (e = event; e; e = e->next)
      if (cfg->time_fields_ids[i] == e->field_id)
      {
	DebugLog(DF_MOD, DS_DEBUG, "Followed time field %i (%s). "
		 "Current Db (%s).\n",
		 cfg->time_fields_ids[i], ctime(&(CTIME(e->value))),
		 ctime(&(SLIST_FIRST(&cfg->history)->time)));

	if (CTIME(e->value) > SLIST_FIRST(&cfg->history)->time)
	{
	  snprintf(buff, 256, "flushall, getall('%s').",
		   SLIST_FIRST(&cfg->history)->odbc_DSN);
	  int ret = pl_execute(buff);
	  DebugLog(DF_MOD, DS_DEBUG, "Update database to odbc %s.\n",
		   (SLIST_FIRST(&cfg->history)->odbc_DSN), ret);
	  if (ret)
	  {
	    SLIST_REMOVE_HEAD(&cfg->history, next);
	    gettimeofday(&cfg->prolog_cfg->last_db_update, NULL);
	  }
	}
	return 0;
      }

  return 0;
}