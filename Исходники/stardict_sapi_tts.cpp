static void configure()
{
	configure_changed = false;
	GtkWidget *window = gtk_dialog_new_with_buttons(_("SAPI TTS configuration"), GTK_WINDOW(plugin_info->pluginwin), GTK_DIALOG_MODAL, GTK_STOCK_OK, GTK_RESPONSE_ACCEPT, NULL);
	GtkWidget *vbox = gtk_vbox_new(false, 5);
	gtk_container_set_border_width(GTK_CONTAINER(vbox),5);
	gtk_container_add (GTK_CONTAINER (GTK_DIALOG(window)->vbox), vbox);
	GtkWidget *frame = gtk_frame_new(_("TTS voice engine"));
	gtk_box_pack_start(GTK_BOX(vbox), frame, false, false, 3);
	GtkWidget *table = gtk_table_new(2, 3, false);
	gtk_container_set_border_width(GTK_CONTAINER(table),8);
	gtk_container_add (GTK_CONTAINER (frame), table);
	GtkWidget *label = gtk_label_new(_("Voice :"));
	gtk_misc_set_alignment (GTK_MISC (label), 0, .5);
	gtk_table_attach(GTK_TABLE(table), label, 0, 1, 0, 1, GTK_FILL, (GtkAttachOptions)0, 5, 0);
	GtkWidget *combobox = gtk_combo_box_new_text();
	gtk_table_attach(GTK_TABLE(table), combobox, 1, 2, 0, 1, GtkAttachOptions(GTK_FILL | GTK_EXPAND), (GtkAttachOptions)0, 5, 0);

	ULONG ulNumTokens;
	WCHAR** ppszTokenIds = NULL;
	CComPtr<IEnumSpObjectTokens> cpEnum;
	HRESULT hr = SpEnumTokens(SPCAT_VOICES, NULL, NULL, &cpEnum);
	if ( S_OK == hr ) {
		hr = cpEnum->GetCount( &ulNumTokens );
		if ( SUCCEEDED( hr ) && 0 != ulNumTokens ) {
			WCHAR *pszCurTokenId = NULL;
			ISpObjectToken *pToken;
			HRESULT hr = pVoice->GetVoice( &pToken );
			if ( SUCCEEDED( hr ) ) {
				pToken->GetId( &pszCurTokenId );
				pToken->Release();
			}
			if (pszCurTokenId) {
				ppszTokenIds = new WCHAR* [ulNumTokens];
				ZeroMemory( ppszTokenIds, ulNumTokens*sizeof( WCHAR* ) );
				LONG ulCurToken = -1;
				ULONG ulIndex = 0;
				while (cpEnum->Next(1, &pToken, NULL) == S_OK) {
					WCHAR *description;
					SpGetDescription( pToken, &description);
					DWORD dwNum = WideCharToMultiByte(CP_UTF8,NULL,description,-1,NULL,0,NULL,FALSE);
					char *text = new char[dwNum];
					WideCharToMultiByte (CP_UTF8,NULL,description,-1,text,dwNum,NULL,FALSE);
					gtk_combo_box_append_text(GTK_COMBO_BOX(combobox), text);
					delete []text;
					CoTaskMemFree(description);
					pToken->GetId( &ppszTokenIds[ulIndex]);
					if (ulCurToken == -1 && _wcsicmp( pszCurTokenId, ppszTokenIds[ulIndex]) == 0) {
						ulCurToken = ulIndex;
					}
					ulIndex++;
					pToken->Release();
				}
				CoTaskMemFree( pszCurTokenId );
				if (ulCurToken != -1)
					gtk_combo_box_set_active(GTK_COMBO_BOX(combobox), ulCurToken);
			}
		}
	}
	g_signal_connect (G_OBJECT (combobox), "changed", G_CALLBACK (on_voice_combobox_changed), ppszTokenIds);

	label = gtk_label_new(_("Volume :"));
	gtk_misc_set_alignment (GTK_MISC (label), 0, .5);
	gtk_table_attach(GTK_TABLE(table), label, 0, 1, 1, 2, GTK_FILL, (GtkAttachOptions)0, 5, 0);
	GtkWidget *volume_hscale = gtk_hscale_new_with_range(0, 100, 1);
	gtk_table_attach(GTK_TABLE(table), volume_hscale, 1, 2, 1, 2, GtkAttachOptions(GTK_FILL | GTK_EXPAND), (GtkAttachOptions)0, 5, 0);
	USHORT volume;
	pVoice->GetVolume(&volume);
	gtk_range_set_value(GTK_RANGE(volume_hscale), volume);
	g_signal_connect(G_OBJECT(volume_hscale),"value-changed", G_CALLBACK(on_volume_hscale_value_changed), NULL);
	label = gtk_label_new(_("Rate :"));
	gtk_misc_set_alignment (GTK_MISC (label), 0, .5);
	gtk_table_attach(GTK_TABLE(table), label, 0, 1, 2, 3, GTK_FILL, (GtkAttachOptions)0, 5, 0);
	GtkWidget *rate_hscale = gtk_hscale_new_with_range(-10, 10, 1);
	gtk_table_attach(GTK_TABLE(table), rate_hscale, 1, 2, 2, 3, GtkAttachOptions(GTK_FILL | GTK_EXPAND), (GtkAttachOptions)0, 5, 0);
	long rate;
	pVoice->GetRate(&rate);
	gtk_range_set_value(GTK_RANGE(rate_hscale), rate);
	g_signal_connect(G_OBJECT(rate_hscale),"value-changed", G_CALLBACK(on_rate_hscale_value_changed), NULL);

	GtkWidget *vbox1 = gtk_vbox_new(false, 5);
	gtk_box_pack_start(GTK_BOX(vbox), vbox1, false, false, 10);
	label = gtk_label_new(_("Input the test text:"));
	gtk_misc_set_alignment (GTK_MISC (label), 0, .5);
	gtk_box_pack_start(GTK_BOX(vbox1), label, false, false, 0);
	GtkWidget *hbox = gtk_hbox_new(false, 5);
	gtk_box_pack_start(GTK_BOX(vbox1), hbox, false, false, 0);
	GtkWidget *entry = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(entry), "This is the test text");
	gtk_box_pack_start(GTK_BOX(hbox), entry, true, true, 0);
	GtkWidget *button = gtk_button_new_with_label(_("Test"));
	gtk_box_pack_start(GTK_BOX(hbox), button, false, false, 0);
	g_signal_connect(G_OBJECT(button),"clicked", G_CALLBACK(on_test_tts_button_clicked), GTK_ENTRY(entry));

	gtk_widget_show_all(vbox);
	gtk_dialog_run(GTK_DIALOG(window));
	if (configure_changed) {
		char *voice = NULL;
		ISpObjectToken *pToken;
		HRESULT hr = pVoice->GetVoice( &pToken );
		if ( SUCCEEDED( hr ) ) {
			WCHAR *id;
			pToken->GetId( &id );
			DWORD dwNum = WideCharToMultiByte(CP_UTF8,NULL,id,-1,NULL,0,NULL,FALSE);
			voice = new char[dwNum];
			WideCharToMultiByte (CP_UTF8,NULL,id,-1,voice,dwNum,NULL,FALSE);
			CoTaskMemFree(id);
			pToken->Release();
		}
		if (voice) {
			gint volume = (gint)gtk_range_get_value(GTK_RANGE(volume_hscale));
			gint rate = (gint)gtk_range_get_value(GTK_RANGE(rate_hscale));
			gchar *data = g_strdup_printf("[sapi_tts]\nvoice=%s\nvolume=%d\nrate=%d\n", voice, volume, rate);
			std::string res = get_cfg_filename();
			g_file_set_contents(res.c_str(), data, -1, NULL);
			g_free(data);
			delete []voice;
		}
	}
	ULONG ulIndex;
	if ( ppszTokenIds ) {
		for ( ulIndex = 0; ulIndex < ulNumTokens; ulIndex++ ) {
			if ( NULL != ppszTokenIds[ulIndex] ) {
				CoTaskMemFree( ppszTokenIds[ulIndex] );
			}
		}
		delete [] ppszTokenIds;
	}
	gtk_widget_destroy (window);
}