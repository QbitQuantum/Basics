void termPlugins() {
  int i;

  traceEvent(TRACE_INFO, "Terminating plugins.");

  i = 0;
  while((i < MAX_NUM_PLUGINS) && (all_plugins[i] != NULL)) {
    if(all_plugins[i]->enabled && all_plugins[i]->termFctn) {
      traceEvent(TRACE_INFO, "Terminating %s", all_plugins[i]->name);
      all_plugins[i]->termFctn();
    }

    i++;
  }
}