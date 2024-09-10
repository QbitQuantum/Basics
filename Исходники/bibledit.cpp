// Initialize library.
// To be called once during the lifetime of the app.
// $package: The folder where the package data resides.
// $webroot: The document root folder for the web server.
void bibledit_initialize_library (const char * package, const char * webroot)
{
  // Must initialize libcurl before any threads are started.
#ifdef HAVE_CLIENT
#else
  curl_global_init (CURL_GLOBAL_ALL);
#endif
  
  // Thread locking.
  thread_setup ();
  
  // Initialize SQLite: Full thread safety: https://www.sqlite.org/c3ref/threadsafe.html.
  // This is supported to prevent "database locked" errors.
  if (!sqlite3_threadsafe ()) {
    cerr << "SQLite is not threadsafe" << endl;
  }
  sqlite3_config (SQLITE_CONFIG_SERIALIZED);

  // Binary file mode on Windows.
#ifdef HAVE_WINDOWS
  _set_fmode (_O_BINARY);
#endif

  // Set the web root folder.
  config_globals_document_root = webroot;
  
  // Initialize SSL/TLS (after webroot has been set).
  filter_url_ssl_tls_initialize ();
  
#ifndef HAVE_CLIENT
  // Cloud initializes OpenLDAP server access settings (after webroot has been set).
  ldap_logic_initialize ();
#endif

#ifdef HAVE_CLIENT
  // Set local timezone offset in the library.
#ifdef HAVE_WINDOWS
  TIME_ZONE_INFORMATION tzi;
  DWORD dwRet = GetTimeZoneInformation (&tzi);
  (void)dwRet;
  int offset = 0 - (tzi.Bias / 60);
  bibledit_set_timezone_hours_offset_utc (offset);
#else
  time_t t = time (NULL);
  struct tm lt = {};
  localtime_r (&t, &lt);
  int offset = round (lt.tm_gmtoff / 3600);
  bibledit_set_timezone_hours_offset_utc (offset);
#endif
  
#endif

  // Initialize data in a thread.
  thread setup_thread = thread (setup_conditionally, package);
  setup_thread.detach ();
  
  // Multiple start/stop guard.
  bibledit_started = false;
}