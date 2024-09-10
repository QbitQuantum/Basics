extern void MCP_RegistHandler(GHashTable *StatusTable, char *status,
                              char *event, void (*handler)(ProcessNode *)) {
  GHashTable *EventTable;

  if ((EventTable = g_hash_table_lookup(StatusTable, status)) == NULL) {
    EventTable = NewNameHash();
    g_hash_table_insert(StatusTable, StrDup(status), EventTable);
  }
  if (g_hash_table_lookup(EventTable, event) == NULL) {
    g_hash_table_insert(EventTable, StrDup(event), handler);
  }
}