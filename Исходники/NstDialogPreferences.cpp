		ibool Preferences::OnCmdDefault(Param&)
		{
			dialog.CheckBox( IDC_PREFERENCES_BEGIN_EMULATION       ).Check( true  );
			dialog.CheckBox( IDC_PREFERENCES_RUN_IN_BACKGROUND     ).Check( false );
			dialog.CheckBox( IDC_PREFERENCES_STARTUP_FULLSCREEN    ).Check( false );
			dialog.CheckBox( IDC_PREFERENCES_DISABLE_ROM_WARNINGS  ).Check( false );
			dialog.CheckBox( IDC_PREFERENCES_CLOSE_POWER_OFF       ).Check( false );
			dialog.CheckBox( IDC_PREFERENCES_CONFIRM_EXIT          ).Check( true  );
			dialog.CheckBox( IDC_PREFERENCES_CONFIRM_RESET         ).Check( false );
			dialog.CheckBox( IDC_PREFERENCES_MULTIPLE_INSTANCES    ).Check( false );
			dialog.CheckBox( IDC_PREFERENCES_SAVE_LOGFILE          ).Check( true  );
			dialog.CheckBox( IDC_PREFERENCES_SAVE_LAUNCHER         ).Check( true  );
			dialog.CheckBox( IDC_PREFERENCES_SAVE_CHEATCODES       ).Check( true  );
			dialog.CheckBox( IDC_PREFERENCES_SAVE_NETPLAY_GAMELIST ).Check( true  );
			dialog.CheckBox( IDC_PREFERENCES_SAVE_WINDOWPOS        ).Check( false );
			dialog.CheckBox( IDC_PREFERENCES_SAVE_LAUNCHERSIZE     ).Check( false );

			dialog.ComboBox( IDC_PREFERENCES_PRIORITY )[ PRIORITY_NORMAL ].Select();

			dialog.RadioButton( IDC_PREFERENCES_FAVORED_NES_NTSC ).Check( true  );
			dialog.RadioButton( IDC_PREFERENCES_FAVORED_NES_PAL  ).Check( false );
			dialog.RadioButton( IDC_PREFERENCES_FAVORED_FAMICOM  ).Check( false );
			dialog.RadioButton( IDC_PREFERENCES_FAVORED_DENDY    ).Check( false );

			dialog.CheckBox( IDC_PREFERENCES_FAVORED_ALWAYS_ASK ).Check( false );

			dialog.CheckBox( IDC_PREFERENCES_MENUCOLOR_DESKTOP_DEFAULT ).Check( true );
			dialog.CheckBox( IDC_PREFERENCES_MENUCOLOR_FULLSCREEN_DEFAULT ).Check( true );

			dialog.Control( IDC_PREFERENCES_MENUCOLOR_DESKTOP_CHANGE ).Enable( false );
			dialog.Control( IDC_PREFERENCES_MENUCOLOR_FULLSCREEN_CHANGE ).Enable( false );

			menuColorWindows[0].color = DEFAULT_DESKTOP_MENU_COLOR;
			menuColorWindows[1].color = DEFAULT_FULLSCREEN_MENU_COLOR;

			UpdateColors();

			return true;
		}