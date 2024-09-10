void
immediate_options (int argc, char** argv) {
  if (get_env ("TEXMACS_HOME_PATH") == "")
#ifdef __MINGW32__
    if (get_env ("HOME") == "")
        set_env ("HOME", get_env("USERPROFILE"));
    set_env ("TEXMACS_HOME_PATH", get_env ("APPDATA") * "\\TeXmacs");
#else
    set_env ("TEXMACS_HOME_PATH", get_env ("HOME") * "/.TeXmacs");
#endif
  if (get_env ("TEXMACS_HOME_PATH") == "") return;
  for (int i=1; i<argc; i++) {
    string s= argv[i];
    if ((N(s)>=2) && (s(0,2)=="--")) s= s (1, N(s));
    if ((s == "-S") || (s == "-setup")) {
      remove (url ("$TEXMACS_HOME_PATH/system/settings.scm"));
      remove (url ("$TEXMACS_HOME_PATH/system/setup.scm"));
      remove (url ("$TEXMACS_HOME_PATH/system/cache") * url_wildcard ("*"));
      remove (url ("$TEXMACS_HOME_PATH/fonts/font-database.scm"));
      remove (url ("$TEXMACS_HOME_PATH/fonts/font-features.scm"));
      remove (url ("$TEXMACS_HOME_PATH/fonts/font-characteristics.scm"));
      remove (url ("$TEXMACS_HOME_PATH/fonts/error") * url_wildcard ("*"));
    }
    else if (s == "-delete-cache")
      remove (url ("$TEXMACS_HOME_PATH/system/cache") * url_wildcard ("*"));
    else if (s == "-delete-style-cache")
      remove (url ("$TEXMACS_HOME_PATH/system/cache") * url_wildcard ("__*"));
    else if (s == "-delete-font-cache") {
      remove (url ("$TEXMACS_HOME_PATH/system/cache/font_cache.scm"));
      remove (url ("$TEXMACS_HOME_PATH/fonts/font-database.scm"));
      remove (url ("$TEXMACS_HOME_PATH/fonts/font-features.scm"));
      remove (url ("$TEXMACS_HOME_PATH/fonts/font-characteristics.scm"));
      remove (url ("$TEXMACS_HOME_PATH/fonts/error") * url_wildcard ("*"));
    }
    else if (s == "-delete-doc-cache") {
      remove (url ("$TEXMACS_HOME_PATH/system/cache/doc_cache"));
      remove (url ("$TEXMACS_HOME_PATH/system/cache/dir_cache.scm"));
      remove (url ("$TEXMACS_HOME_PATH/system/cache/stat_cache.scm"));
    }
    else if (s == "-delete-file-cache") {
      remove (url ("$TEXMACS_HOME_PATH/system/cache/doc_cache"));
      remove (url ("$TEXMACS_HOME_PATH/system/cache/file_cache"));
      remove (url ("$TEXMACS_HOME_PATH/system/cache/dir_cache.scm"));
      remove (url ("$TEXMACS_HOME_PATH/system/cache/stat_cache.scm"));
    }
    else if (s == "-delete-plugin-cache")
      remove (url ("$TEXMACS_HOME_PATH/system/cache/plugin_cache.scm"));
    else if (s == "-delete-server-data")
      system ("rm -rf", url ("$TEXMACS_HOME_PATH/server"));
    else if (s == "-delete-databases") {
      system ("rm -rf", url ("$TEXMACS_HOME_PATH/system/database"));
      system ("rm -rf", url ("$TEXMACS_HOME_PATH/users"));
    }
    else if (s == "-log-file" && i + 1 < argc) {
      i++;
      char* log_file = argv[i];
      tm_ostream logf (log_file);
      if (!logf->is_writable ())
        cerr << "TeXmacs] Error: could not open " << log_file << "\n";
      cout.redirect (logf);
      cerr.redirect (logf);
    }
  }
}