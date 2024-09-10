static int64 readLog(FILE *input,
                     sqlite3 *db)
{
  int64 eventCount = 0;

  /* declare statements for every event type */
  EVENT_LIST(EVENT_TYPE_DECLARE_STATEMENT, X);

  /* prepare statements for every event type */
  EVENT_LIST(EVENT_TYPE_PREPARE_STATEMENT, X);

  runStatement(db, "BEGIN", "Transaction start");

  while (TRUE) { /* loop for each event */
    char line[MAX_LOG_LINE_LENGTH];
    char *p;
    char *q;
    int last_index=0;
    sqlite3_stmt *statement = NULL;
    int res;
    int64 clock_field;
    long code;

    p = fgets(line, MAX_LOG_LINE_LENGTH, input);
    if (!p) {
      if (feof(input))
        break;
      else
        error("Couldn't read line after event %llu", eventCount);
    }

    eventCount++;

    clock_field = strtoll(p, &q, 16);

    if (q == p)
      error("event %llu clock field not a hex integer: %s",
            eventCount, p);

    if (*q != ' ')
      error("event %llu code field not preceded by ' ': %s",
            eventCount, q);
    while(*q == ' ')
      ++q;

    p = q;
    code = strtol(p, &q, 16);
    if (q == p)
      error("event %llu code field not an integer: %s",
            eventCount, p);
    p = q;

    /* Write event to SQLite. */
    switch (code) {
      /* this macro sets statement and last_index */
      EVENT_LIST(EVENT_TYPE_WRITE_SQL, X);
    default:
      error("Event %llu has Unknown event code %d", eventCount, code);
    }
    /* bind the fields we store for every event */ \
    res = sqlite3_bind_int64(statement, last_index+1, logSerial);
    if (res != SQLITE_OK)
      sqlite_error(res, db, "Event %llu bind of log_serial failed.", eventCount);
    res = sqlite3_bind_int64(statement, last_index+2, clock_field);
    if (res != SQLITE_OK)
      sqlite_error(res, db, "Event %llu bind of clock failed.", eventCount);
    res = sqlite3_step(statement);
    if (res != SQLITE_DONE)
      sqlite_error(res, db, "insert of event %llu failed.", eventCount);
    res = sqlite3_reset(statement);
    if (res != SQLITE_OK)
      sqlite_error(res, db, "Couldn't reset insert statement of event %llu", eventCount);

    if (progress) {
      if ((eventCount % SMALL_TICK) == 0) {
        printf(".");
        fflush(stdout);
        if (((eventCount / SMALL_TICK) % BIG_TICK) == 0) {
          printf("\n");
          fflush(stdout);
          evlog(LOG_SOMETIMES, "%lu events.", (unsigned long)eventCount);
        }
      }
    }
  }
  if (progress) {
    printf("\n");
    fflush(stdout);
  }
  runStatement(db, "COMMIT", "Transaction finish");
  logFileCompleted(db, eventCount);

  /* finalize all the statements */
  EVENT_LIST(EVENT_TYPE_FINALIZE_STATEMENT, X);

  return eventCount;
}