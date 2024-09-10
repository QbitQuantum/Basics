static void
setup_runtime_paths (void)
{
        char cpbfr[1000];
        wchar_t wcbfr[1000];
        char *full_prefix = NULL;
        char *cp_prefix = NULL;
  
        G_LOCK (mutex);
        if (prefix != NULL) {
                G_UNLOCK (mutex);
                return;
        }

        if (G_WIN32_HAVE_WIDECHAR_API ()) {
                /* NT-based Windows */
                if (GetModuleFileNameW (hmodule, wcbfr, G_N_ELEMENTS (wcbfr))) {
                        full_prefix = g_utf16_to_utf8 (wcbfr, -1,
                                                   NULL, NULL, NULL);
                        if (GetShortPathNameW (wcbfr, wcbfr, G_N_ELEMENTS (wcbfr)) &&
                            WideCharToMultiByte (CP_ACP, 0, wcbfr, -1,
                                                 cpbfr, G_N_ELEMENTS (cpbfr),
                                                 NULL, NULL))
                                cp_prefix = g_strdup (cpbfr);
                        else if (full_prefix)
                                cp_prefix = g_locale_from_utf8 (full_prefix, -1,
                                                                NULL, NULL, NULL);
                }
        } else {
                /* Win9x */
                if (GetModuleFileNameA (hmodule, cpbfr, G_N_ELEMENTS (cpbfr))) {
                        full_prefix = g_locale_to_utf8 (cpbfr, -1,
                                                        NULL, NULL, NULL);
                        cp_prefix = g_strdup (cpbfr);
                }
        }

        if (full_prefix != NULL) {
                gchar *p = strrchr (full_prefix, '\\');
                if (p != NULL)
                        *p = '\0';
      
                p = strrchr (full_prefix, '\\');
                if (p && (g_ascii_strcasecmp (p + 1, "bin") == 0))
                        *p = '\0';
                prefix = full_prefix;
        }
                  
        if (cp_prefix != NULL) {
                gchar *p = _mbsrchr (cp_prefix, '\\');
                if (p != NULL)
                        *p = '\0';
      
                p = _mbsrchr (cp_prefix, '\\');
                if (p && (g_ascii_strcasecmp (p + 1, "bin") == 0))
                        *p = '\0';
                
        }

        server_libexecdir = _matecomponent_activation_win32_replace_prefix (full_prefix, SERVER_LIBEXECDIR);
        serverinfodir = _matecomponent_activation_win32_replace_prefix (full_prefix, SERVERINFODIR);
        server_confdir = _matecomponent_activation_win32_replace_prefix (full_prefix, SERVER_CONFDIR);
        localedir = _matecomponent_activation_win32_replace_prefix (cp_prefix, MATECOMPONENT_ACTIVATION_LOCALEDIR);

        G_UNLOCK (mutex);
}