void
Win32MUSH_setup(void)
{
  int indb_OK, outdb_OK, panicdb_OK;
  FILETIME indb_time, outdb_time, panicdb_time;
  long indb_size, outdb_size, panicdb_size;

#ifndef _DEBUG
  char FileName[256];
  if (GetModuleFileName(NULL, FileName, 256) != 0) {
    if (!strcasecmp(strrchr(FileName, '\\') + 1, "pennmush.exe")) {
      if (CopyFile("pennmush.exe", "pennmush_run.exe", FALSE)) {
        do_rawlog(LT_ERR, "Successfully copied executable, starting copy.");
#ifdef WIN32SERVICES
        execl("pennmush_run.exe", "pennmush_run.exe", "/run", NULL);
#else
        execl("pennmush_run.exe", "pennmush_run.exe", confname, NULL);
#endif
      }
    }
  }
#endif                          /*  */
  ConcatenateFiles("txt\\hlp\\*.hlp", "txt\\help.txt");
  ConcatenateFiles("txt\\nws\\*.nws", "txt\\news.txt");
  ConcatenateFiles("txt\\evt\\*.evt", "txt\\events.txt");
  ConcatenateFiles("txt\\rul\\*.rul", "txt\\rules.txt");
  ConcatenateFiles("txt\\idx\\*.idx", "txt\\index.txt");
  indb_OK = CheckDatabase(options.input_db, &indb_time, &indb_size);
  outdb_OK = CheckDatabase(options.output_db, &outdb_time, &outdb_size);
  panicdb_OK = CheckDatabase(options.crash_db, &panicdb_time, &panicdb_size);
  if (indb_OK) {                /* Look at outdb */
    if (outdb_OK) {             /* Look at panicdb */
      if (panicdb_OK) {         /* outdb or panicdb or indb */
        if (CompareFileTime(&panicdb_time, &outdb_time) > 0) {  /* panicdb or indb */
          if (CompareFileTime(&panicdb_time, &indb_time) > 0) { /* panicdb */
            ConcatenateFiles(options.crash_db, options.input_db);
          } else {              /* indb */
          }
        } else {                /* outdb or indb */
          if (CompareFileTime(&outdb_time, &indb_time) > 0) {   /* outdb */
            ConcatenateFiles(options.output_db, options.input_db);
          } else {              /* indb */
          }
        }
      } else {                  /* outdb or indb */
        if (CompareFileTime(&outdb_time, &indb_time) > 0) {     /* outdb */
          ConcatenateFiles(options.output_db, options.input_db);
        } else {                /* indb */
        }
      }
    } else {                    /* outdb not OK */
      if (panicdb_OK) {         /* panicdb or indb */
        if (CompareFileTime(&panicdb_time, &indb_time) > 0) {   /* panicdb */
          ConcatenateFiles(options.crash_db, options.input_db);
        } else {                /* indb */
        }
      } else {                  /* indb */
      }
    }
  } else {                      /* indb not OK */
    if (outdb_OK) {             /* look at panicdb */
      if (panicdb_OK) {         /* out or panic */
        if (CompareFileTime(&panicdb_time, &outdb_time) > 0) {  /* panicdb */
          ConcatenateFiles(options.crash_db, options.input_db);
        } else {                /* outdb */
          ConcatenateFiles(options.output_db, options.input_db);
        }
      } else {                  /* outdb */
        ConcatenateFiles(options.output_db, options.input_db);
      }
    } else {                    /* outdb not OK */
      if (panicdb_OK) {         /* panicdb */
        ConcatenateFiles(options.crash_db, options.input_db);
      } else {                  /* NOTHING */
        return;
      }
    }
  }

/* Final failsafe - input database SHOULD still be OK. */
  do_rawlog(LT_ERR, "Verifying selected database.");
  if (!CheckDatabase(options.input_db, &indb_time, &indb_size)) {
    do_rawlog(LT_ERR, "File corrupted during selection process.");
    exit(-1);
  } else {
    do_rawlog(LT_ERR, "Input database verified. Proceeding to analysis.");
  }
}