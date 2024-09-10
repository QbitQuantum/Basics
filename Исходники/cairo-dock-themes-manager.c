gboolean cairo_dock_manage_themes (GtkWidget *pWidget, gboolean bSafeMode)
{
	GString *sCommand = g_string_new ("");
	GHashTable *hThemeTable = NULL;
	gchar *cInitConfFile = cairo_dock_edit_themes (&hThemeTable, bSafeMode);

	if (cInitConfFile != NULL)
	{
		GError *erreur = NULL;
		gboolean bNeedSave = cairo_dock_theme_need_save ();

		//\___________________ On recupere les donnees de l'IHM apres modification par l'utilisateur.
		GKeyFile *pKeyFile = g_key_file_new ();

		g_key_file_load_from_file (pKeyFile, cInitConfFile, G_KEY_FILE_KEEP_COMMENTS | G_KEY_FILE_KEEP_TRANSLATIONS, &erreur);
		g_remove (cInitConfFile);
		g_free (cInitConfFile);
		if (erreur != NULL)
		{
			cd_warning ("Attention : %s", erreur->message);
			g_error_free (erreur);
			return FALSE;
		}

		//\___________________ On charge le nouveau theme choisi.
		gchar *cNewThemeName = g_key_file_get_string (pKeyFile, "Themes", "chosen theme", &erreur);
		if (erreur != NULL)
		{
			cd_warning ("Attention : %s", erreur->message);
			g_error_free (erreur);
			erreur = NULL;
		}
		if (cNewThemeName != NULL && *cNewThemeName == '\0')
		{
			g_free (cNewThemeName);
			cNewThemeName = NULL;
		}

		if (cNewThemeName != NULL)
		{
			if (bNeedSave)
			{
				int iAnswer = cairo_dock_ask_general_question_and_wait (_("You made some modifications in the current theme.\nYou will loose them if you don't save before choosing a new theme. Continue anyway ?"));
				if (iAnswer != GTK_RESPONSE_YES)
				{
					g_hash_table_destroy (hThemeTable);
					return TRUE;
				}
				else
					cairo_dock_mark_theme_as_modified (FALSE);
			}

			gchar *cNewThemePath = g_hash_table_lookup (hThemeTable, cNewThemeName);
			//\___________________ On charge les parametres de comportement.
			if (g_pMainDock == NULL || g_key_file_get_boolean (pKeyFile, "Themes", "use theme behaviour", NULL))
			{
				g_string_printf (sCommand, "/bin/cp '%s'/%s '%s'", cNewThemePath, CAIRO_DOCK_CONF_FILE, g_cCurrentThemePath);
				cd_message ("%s", sCommand->str);
				system (sCommand->str);
			}
			else
			{
				gchar *cNewConfFilePath = g_strdup_printf ("%s/%s", cNewThemePath, CAIRO_DOCK_CONF_FILE);
				cairo_dock_replace_keys_by_identifier (g_cConfFile, cNewConfFilePath, '+');
				g_free (cNewConfFilePath);
			}
			//\___________________ On charge les icones.
			g_string_printf (sCommand, "find '%s' -mindepth 1 ! -name '*.desktop' ! -name 'container-*' -delete", g_cCurrentLaunchersPath);
			cd_message ("%s", sCommand->str);
			system (sCommand->str);
			g_string_printf (sCommand, "find '%s/%s' -mindepth 1 ! -name '*.desktop' -exec /bin/cp -p '{}' '%s' \\;", cNewThemePath, CAIRO_DOCK_LAUNCHERS_DIR, g_cCurrentLaunchersPath);
			cd_message ("%s", sCommand->str);
			system (sCommand->str);
			
			//\___________________ On charge les lanceurs si necessaire, en effacant ceux existants.
			if (g_pMainDock == NULL || g_key_file_get_boolean (pKeyFile, "Themes", "use theme launchers", NULL))
			{
				g_string_printf (sCommand, "rm -f '%s'/*.desktop", g_cCurrentLaunchersPath);
				cd_message ("%s", sCommand->str);
				system (sCommand->str);

				g_string_printf (sCommand, "cp '%s/%s'/*.desktop '%s'", cNewThemePath, CAIRO_DOCK_LAUNCHERS_DIR, g_cCurrentLaunchersPath);
				cd_message ("%s", sCommand->str);
				system (sCommand->str);
			}
			
			//\___________________ On remplace tous les autres fichiers par les nouveaux.
			g_string_printf (sCommand, "find '%s' -mindepth 1 -maxdepth 1  ! -name '*.conf' -type f -exec rm -rf '{}' \\;", g_cCurrentThemePath);  // efface tous les fichiers du theme mais sans toucher aux lanceurs et aux plug-ins.
			cd_message ("%s", sCommand->str);
			system (sCommand->str);

			/// A FAIRE : fusionner les fichiers de conf des plug-ins si deja presents.
			g_string_printf (sCommand, "find '%s'/* -prune ! -name '*.conf' ! -name %s -exec /bin/cp -r '{}' '%s' \\;", cNewThemePath, CAIRO_DOCK_LAUNCHERS_DIR, g_cCurrentThemePath);  // copie tous les fichiers du nouveau theme sauf les lanceurs et le .conf, dans le repertoire du theme courant. Ecrase les fichiers de memes noms.
			cd_message ("%s", sCommand->str);
			system (sCommand->str);

			//\___________________ On charge le theme courant.
			cairo_dock_load_theme (g_cCurrentThemePath);

			g_free (cNewThemeName);
			g_hash_table_destroy (hThemeTable);
			return FALSE;
		}
		g_free (cNewThemeName);

		//\___________________ On sauvegarde le theme actuel
		cNewThemeName = g_key_file_get_string (pKeyFile, "Save", "theme name", &erreur);
		if (erreur != NULL)
		{
			cd_warning ("Attention : %s", erreur->message);
			g_error_free (erreur);
			erreur = NULL;
		}
		if (cNewThemeName != NULL && *cNewThemeName == '\0')
		{
			g_free (cNewThemeName);
			cNewThemeName = NULL;
		}
		cd_message ("cNewThemeName : %s", cNewThemeName);

		if (cNewThemeName != NULL)
		{
			cd_message ("on sauvegarde dans %s", cNewThemeName);
			gboolean bThemeSaved = FALSE;
			gchar *cNewThemePath = g_hash_table_lookup (hThemeTable, cNewThemeName);
			if (cNewThemePath != NULL)  // on ecrase un theme existant.
			{
				cd_message ("  theme existant");
				if (strncmp (cNewThemePath, CAIRO_DOCK_SHARE_THEMES_DIR, strlen (CAIRO_DOCK_SHARE_THEMES_DIR)) == 0)  // c'est un theme pre-installe.
				{
					cd_warning ("You can't overwrite a pre-installed theme");
				}
				else
				{
					gchar *question = g_strdup_printf (_("Are you sure you want to overwrite theme %s ?"), cNewThemeName);
					GtkWidget *dialog = gtk_message_dialog_new (GTK_WINDOW (pWidget),
						GTK_DIALOG_DESTROY_WITH_PARENT,
						GTK_MESSAGE_QUESTION,
						GTK_BUTTONS_YES_NO,
						question);
					g_free (question);
					int answer = gtk_dialog_run (GTK_DIALOG (dialog));
					gtk_widget_destroy (dialog);
					if (answer == GTK_RESPONSE_YES)
					{
						gchar *cNewConfFilePath = g_strdup_printf ("%s/%s", cNewThemePath, CAIRO_DOCK_CONF_FILE);
						if (g_key_file_get_boolean (pKeyFile, "Save", "save current behaviour", NULL))
						{
							g_string_printf (sCommand, "/bin/cp '%s' '%s'", g_cConfFile, cNewConfFilePath);
							cd_message ("%s", sCommand->str);
							system (sCommand->str);
						}
						else
						{
							cairo_dock_replace_keys_by_identifier (cNewConfFilePath, g_cConfFile, '+');
						}
						g_free (cNewConfFilePath);

						if (g_key_file_get_boolean (pKeyFile, "Save", "save current launchers", NULL))
						{
							g_string_printf (sCommand, "rm -f '%s/%s'/*", cNewThemePath, CAIRO_DOCK_LAUNCHERS_DIR);
							cd_message ("%s", sCommand->str);
							system (sCommand->str);
							
							g_string_printf (sCommand, "cp '%s'/* '%s/%s'", g_cCurrentLaunchersPath, cNewThemePath, CAIRO_DOCK_LAUNCHERS_DIR);
							cd_message ("%s", sCommand->str);
							system (sCommand->str);
						}

						g_string_printf (sCommand, "find '%s' -mindepth 1 -maxdepth 1  ! -name '*.conf' ! -name '%s' -exec /bin/cp -r '{}' '%s' \\;", g_cCurrentThemePath, CAIRO_DOCK_LAUNCHERS_DIR, cNewThemePath);
						cd_message ("%s", sCommand->str);
						system (sCommand->str);

						bThemeSaved = TRUE;
					}
				}
			}
			else
			{
				cNewThemePath = g_strdup_printf ("%s/%s/%s", g_cCairoDockDataDir, CAIRO_DOCK_THEMES_DIR, cNewThemeName);
				cd_message ("  nouveau theme (%s)", cNewThemePath);

				if (g_mkdir (cNewThemePath, 7*8*8+7*8+5) != 0)
					bThemeSaved = FALSE;
				else
				{
					g_string_printf (sCommand, "cp -r '%s'/* '%s'", g_cCurrentThemePath, cNewThemePath);
					cd_message ("%s", sCommand->str);
					system (sCommand->str);

					g_free (cNewThemePath);
					bThemeSaved = TRUE;
				}
			}
			if (bThemeSaved)
				cairo_dock_mark_theme_as_modified (FALSE);
		}

		//\___________________ On efface les themes qui ne sont plus desires.
		gsize length = 0;
		gchar ** cThemesList = g_key_file_get_string_list (pKeyFile, "Delete", "wanted themes", &length, &erreur);
		if (erreur != NULL)
		{
			cd_warning ("Attention : %s", erreur->message);
			g_error_free (erreur);
			erreur = NULL;
		}
		else if (cThemesList != NULL)
		{
			gchar *cThemesDir = g_strdup_printf ("%s/%s", g_cCairoDockDataDir, CAIRO_DOCK_THEMES_DIR);
			GHashTable *hUserThemeTable = cairo_dock_list_themes (cThemesDir, NULL, &erreur);
			g_free (cThemesDir);
			if (erreur != NULL)
			{
				cd_warning ("Attention : %s", erreur->message);
				g_error_free (erreur);
				erreur = NULL;
			}
			else
			{
				if (cNewThemeName != NULL)
					g_hash_table_remove (hUserThemeTable, cNewThemeName);  // pour ne pas effacer le theme qu'on vient d'enregistrer.
				gpointer data[2] = {cThemesList, pWidget};
				g_hash_table_foreach (hUserThemeTable, (GHFunc) _cairo_dock_delete_one_theme, data);
			}
			g_hash_table_destroy (hUserThemeTable);
		}
		g_strfreev (cThemesList);

		g_free (cNewThemeName);
		g_key_file_free (pKeyFile);
	}
	
	g_string_free (sCommand, TRUE);
	g_hash_table_destroy (hThemeTable);
	return FALSE;
}