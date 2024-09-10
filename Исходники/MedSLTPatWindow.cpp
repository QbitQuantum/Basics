MedSLTPatWindow::MedSLTPatWindow(MedSLTPatWindowObserver& observer)
	: 	m_observer(observer),
		m_list_index(0),
		m_list_items(0),
		m_is_fullscreen(FALSE),
		m_back_translation(""),
		m_ui_state(UI_STATE_DISCONNECTED)		
{
	ACE_TRACE("[MedSLTPatWindow::MedSLTPatWindow()]");

	GtkBox*					hbox;
	GtkBox*					coverbox;
	GtkBox*					textbox;
	GtkBox*					buthbox;
	GtkWidget*				menu;
	GtkWidget*				appimage;	
	GtkWidget*				scroll1;
	GtkWidget* 				scroll2;
	GtkWidget* 				scroll3;
	PangoFontDescription*	font1;
	PangoFontDescription*	font2;	
	GtkStyle*				style; 
	GtkAccelGroup*			accel = gtk_accel_group_new();

	// Window
#ifdef _MAEMO
	m_window = GTK_WINDOW(hildon_window_new());	
#else
	m_window = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));
	gtk_window_set_default_size(m_window, 450, -1);
#endif
	
	gtk_window_add_accel_group(m_window, accel);	
	gtk_window_set_icon_from_file(m_window, app_icon, NULL);	
	gtk_container_set_border_width(GTK_CONTAINER(m_window), 5);
	
	// Boxes
	coverbox = GTK_BOX(gtk_vbox_new(False, 5));	
	hbox = GTK_BOX(gtk_hbox_new(False, 5));	
	textbox = GTK_BOX(gtk_vbox_new(False, 5));
	buthbox = GTK_BOX(gtk_vbox_new(False, 5));
		
	// Image
	appimage = gtk_image_new_from_file(app_icon_big);
	
	// Fonts	
	font1 = pango_font_description_from_string("Monospace Bold 20");
	font2 = pango_font_description_from_string("Monospace Bold 16");
	
	// Styles
	style = gtk_style_new();
	style->font_desc = font1;
	gdk_color_parse ("red", &(style->fg[GTK_STATE_NORMAL]));
	
	// Lists
	m_list = gtk_clist_new(1);
	 
	gtk_widget_set_size_request(GTK_WIDGET(m_list), 550, 130);
	gtk_widget_modify_font(m_list, font1);
		
	/*gchar* text[3][1] = {	{"où avez vous mal?"},		
							{"avez vous mal sous le devant de la tête?"},
							{"la douleur survient elle le matin?"}};	*/
	
	gchar* text[3][1] = {	{"sí mucho"},		
								{"no sé"},
								{"la cabeza"}};
	
	gtk_clist_append((GtkCList*)m_list, text[0]);
	gtk_clist_append((GtkCList*)m_list, text[1]);
	gtk_clist_append((GtkCList*)m_list, text[2]);
	
	m_list_items = 3;
	
	gtk_clist_select_row((GtkCList*)m_list, 0, 0);
	
	// Text Boxes
	m_txtbox1 = gtk_text_view_new();
			
	gtk_widget_modify_font(m_txtbox1, font1);
		
	gtk_widget_set_size_request(GTK_WIDGET(m_txtbox1), 550, 50);
		
	gtk_text_view_set_editable(GTK_TEXT_VIEW(m_txtbox1), false);
		
	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(m_txtbox1), GTK_WRAP_WORD_CHAR);
	
	gtk_widget_set_style (m_txtbox1, style);
	
	m_txtbox2 = gtk_text_view_new();
				
	gtk_widget_modify_font(m_txtbox2, font1);
			
	gtk_widget_set_size_request(GTK_WIDGET(m_txtbox2), 550, 50);
			
	gtk_text_view_set_editable(GTK_TEXT_VIEW(m_txtbox2), false);
		
	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(m_txtbox2), GTK_WRAP_WORD_CHAR);
		
	// Scroll bars
	scroll1 = gtk_scrolled_window_new(NULL, NULL);
	scroll2 = gtk_scrolled_window_new(NULL, NULL);
	scroll3 = gtk_scrolled_window_new(NULL, NULL);
	
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll1), GTK_POLICY_ALWAYS, GTK_POLICY_ALWAYS);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll2), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll3), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);
	
	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(scroll1), GTK_SHADOW_IN);
	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(scroll2), GTK_SHADOW_IN);
	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(scroll3), GTK_SHADOW_IN);
	
	gtk_container_add(GTK_CONTAINER(scroll1), GTK_WIDGET(m_list));
	gtk_container_add(GTK_CONTAINER(scroll2), GTK_WIDGET(m_txtbox1));
	gtk_container_add(GTK_CONTAINER(scroll3), GTK_WIDGET(m_txtbox2));
			
	// Text labels
	m_understood = gtk_label_new("Understood");
	m_question = gtk_label_new("Question");
	m_translation = gtk_label_new("Translation");

	gtk_widget_modify_font(m_understood, font2);
	gtk_widget_modify_font(m_question, font2);
	gtk_widget_modify_font(m_translation, font2);
	
	gtk_label_set_justify(GTK_LABEL(m_understood), GTK_JUSTIFY_LEFT);
	gtk_label_set_justify(GTK_LABEL(m_question), GTK_JUSTIFY_LEFT);
	gtk_label_set_justify(GTK_LABEL(m_translation), GTK_JUSTIFY_LEFT);
		
	gtk_label_set_ellipsize(GTK_LABEL(m_understood), PANGO_ELLIPSIZE_END);	
	gtk_label_set_ellipsize(GTK_LABEL(m_question), PANGO_ELLIPSIZE_END);
	gtk_label_set_ellipsize(GTK_LABEL(m_translation), PANGO_ELLIPSIZE_END);
		
	// Buttons
	m_rec = gtk_button_new();
	m_speech = gtk_button_new();
	m_abort = gtk_button_new();
	m_up = gtk_button_new();
	m_select = gtk_button_new();
	m_down = gtk_button_new();
	
	gtk_button_set_image(GTK_BUTTON(m_rec),
							gtk_image_new_from_file(record_icon));
	gtk_button_set_image(GTK_BUTTON(m_speech),
									gtk_image_new_from_file(speech_icon));
	gtk_button_set_image(GTK_BUTTON(m_abort),
							gtk_image_new_from_file(stop_icon));
	gtk_button_set_image(GTK_BUTTON(m_up),
							gtk_image_new_from_file(up_icon));
	gtk_button_set_image(GTK_BUTTON(m_select),
							gtk_image_new_from_file(select_icon));
	gtk_button_set_image(GTK_BUTTON(m_down),
							gtk_image_new_from_file(down_icon));

	// Menu
	// Recheck: Is it destroyed somewhere
	menu = CreateMenu(accel);
	
	// Progress bar
	m_progressbar = gtk_progress_bar_new();
	gtk_progress_set_text_alignment(GTK_PROGRESS(m_progressbar),
									0.5, 0.5);
	gtk_widget_set_size_request(GTK_WIDGET(m_progressbar), 150, 50);	
	//gtk_container_add(GTK_CONTAINER(m_window), GTK_WIDGET(vbox));	
		
	gtk_box_pack_start(textbox, m_understood, TRUE, TRUE, 0);
	gtk_box_pack_start(textbox, scroll1, TRUE, TRUE, 0);
	gtk_box_pack_start(textbox, m_question, TRUE, TRUE, 0);
	gtk_box_pack_start(textbox, scroll2, TRUE, TRUE, 0);
	gtk_box_pack_start(textbox, m_translation, TRUE, TRUE, 0);
	gtk_box_pack_start(textbox, scroll3, TRUE, TRUE, 0);
	
	//gtk_box_pack_start(buthbox, appimage, TRUE, TRUE, 0);
	gtk_box_pack_start(buthbox, m_rec, TRUE, TRUE, 0);
	gtk_box_pack_start(buthbox, m_speech, TRUE, TRUE, 0);
	gtk_box_pack_start(buthbox, m_abort, TRUE, TRUE, 0);
	gtk_box_pack_start(buthbox, m_up, TRUE, TRUE, 0);
	gtk_box_pack_start(buthbox, m_select, TRUE, TRUE, 0);
	gtk_box_pack_start(buthbox, m_down, TRUE, TRUE, 0);
	
	gtk_box_pack_start(hbox, GTK_WIDGET(textbox), TRUE, TRUE, 0);
	gtk_box_pack_start(hbox, GTK_WIDGET(buthbox), TRUE, TRUE, 0);
	
	gtk_box_pack_start(coverbox, GTK_WIDGET(hbox), TRUE, TRUE, 0);
	gtk_box_pack_start(coverbox, m_progressbar, TRUE, TRUE, 0);
	
	gtk_container_add(GTK_CONTAINER(m_window), GTK_WIDGET(coverbox));
	
#ifdef _MAEMO
	hildon_window_set_menu(HILDON_WINDOW(m_window), GTK_MENU(menu));	
#else
	gtk_box_pack_start(vbox, menu, FALSE, FALSE, 0);
#endif

	// Signals
	g_signal_connect(G_OBJECT(m_rec), "clicked", 
						G_CALLBACK(RecognizeClicked), this);
	g_signal_connect(G_OBJECT(m_speech), "clicked",
							G_CALLBACK(AbortClicked), this);
	g_signal_connect(G_OBJECT(m_abort), "clicked",
						G_CALLBACK(AbortClicked), this);
	g_signal_connect(G_OBJECT(m_up), "clicked",
						G_CALLBACK(UpClicked), this);
	g_signal_connect(G_OBJECT(m_select), "clicked",
						G_CALLBACK(SelectClicked), this);
	g_signal_connect(G_OBJECT(m_down), "clicked",
						G_CALLBACK(DownClicked), this);
	g_signal_connect(G_OBJECT(m_list), "select_row",
						G_CALLBACK(ListRowSelected), this);
	g_signal_connect(G_OBJECT(m_window), "destroy",
						G_CALLBACK(CloseApp), this);
	g_signal_connect(G_OBJECT(m_window), "delete_event",
						G_CALLBACK(CloseApp), this);

	// Shortcuts
#ifndef _MAEMO
	gtk_widget_add_accelerator(m_rec, "clicked", accel, GDK_space,
								0, 0);
	gtk_widget_add_accelerator(m_speech, "clicked", accel, GDK_space,
									0, 0);
	gtk_widget_add_accelerator(m_abort, "clicked", accel, GDK_space,
								0, 0);
	gtk_widget_add_accelerator(m_next, "clicked", accel, GDK_Right,
								GDK_CONTROL_MASK, 0);
#endif

	// Initial state
	SetUiState(UI_STATE_DISCONNECTED);
	
	return;
}