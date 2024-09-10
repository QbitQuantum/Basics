void linphone_gtk_call_log_update(GtkWidget *w){
	GtkTreeView *v=GTK_TREE_VIEW(linphone_gtk_get_widget(w,"logs_view"));
	GtkTreeStore *store;
	const MSList *logs;
	GtkTreeSelection *select;
	GtkWidget *notebook=linphone_gtk_get_widget(w,"viewswitch");
	gint nb;

	store=(GtkTreeStore*)gtk_tree_view_get_model(v);
	if (store==NULL){
		store=gtk_tree_store_new(3,GDK_TYPE_PIXBUF,G_TYPE_STRING,G_TYPE_POINTER,G_TYPE_STRING);
		gtk_tree_view_set_model(v,GTK_TREE_MODEL(store));
		g_object_unref(G_OBJECT(store));
		fill_renderers(GTK_TREE_VIEW(linphone_gtk_get_widget(w,"logs_view")));
		select=gtk_tree_view_get_selection(v);
		gtk_tree_selection_set_mode(select, GTK_SELECTION_SINGLE);
		g_signal_connect_swapped(G_OBJECT(select),"changed",(GCallback)call_log_selection_changed,v);
		g_signal_connect(G_OBJECT(notebook),"focus-tab",(GCallback)linphone_gtk_call_log_reset_missed_call,NULL);
		g_signal_connect(G_OBJECT(v),"button-press-event",(GCallback)linphone_gtk_call_log_button_pressed,NULL);
//		gtk_button_set_image(GTK_BUTTON(linphone_gtk_get_widget(w,"call_back_button")),
//		                     create_pixmap (linphone_gtk_get_ui_config("callback_button","status-green.png")));
	}
	nb=linphone_core_get_missed_calls_count(linphone_gtk_get_core());
	if(nb > 0)
		linphone_gtk_call_log_display_missed_call(nb);
	gtk_tree_store_clear (store);

	for (logs=linphone_core_get_call_logs(linphone_gtk_get_core());logs!=NULL;logs=logs->next){
		LinphoneCallLog *cl=(LinphoneCallLog*)logs->data;
		GtkTreeIter iter, iter2;
		LinphoneAddress *la=linphone_call_log_get_dir(cl)==LinphoneCallIncoming ? linphone_call_log_get_from(cl) : linphone_call_log_get_to(cl);
		char *addr= linphone_address_as_string(la);
		const char *display;
		gchar *logtxt, *headtxt, *minutes, *seconds;
		gchar quality[20];
		const char *status=NULL;
		gchar *start_date=NULL;
		LinphoneFriend *lf=NULL;
		int duration=linphone_call_log_get_duration(cl);
		time_t start_date_time=linphone_call_log_get_start_date(cl);
		
#if GLIB_CHECK_VERSION(2,26,0)
		if (start_date_time){
			GDateTime *dt=g_date_time_new_from_unix_local(start_date_time);
			start_date=g_date_time_format(dt,"%c");
			g_date_time_unref(dt);
		}
#else
		start_date=g_strdup(ctime(&start_date_time));
#endif
		lf=linphone_core_get_friend_by_address(linphone_gtk_get_core(),addr);
		if(lf != NULL){
			if ((display=linphone_address_get_display_name(linphone_friend_get_address(lf)))) {
				/*update display name from friend*/
				linphone_address_set_display_name(la,display);
			}
		} else {
			display=linphone_address_get_display_name(la);
		}
		if (display==NULL){
			display=linphone_address_get_username (la);
			if (display==NULL){
				display=linphone_address_get_domain (la);
			}
		}

		if (linphone_call_log_get_quality(cl)!=-1){
			snprintf(quality,sizeof(quality),"%.1f",linphone_call_log_get_quality(cl));
		}else snprintf(quality,sizeof(quality)-1,"%s",_("n/a"));
		switch(linphone_call_log_get_status(cl)){
			case LinphoneCallAborted:
				status=_("Aborted");
			break;
			case LinphoneCallMissed:
				status=_("Missed");
			break;
			case LinphoneCallDeclined:
				status=_("Declined");
			break;
			default:
			break;
		}
		minutes=g_markup_printf_escaped(
			ngettext("%i minute", "%i minutes", duration/60),
			duration/60);
		seconds=g_markup_printf_escaped(
			ngettext("%i second", "%i seconds", duration%60),
			duration%60);
		if (status==NULL) {
				headtxt=g_markup_printf_escaped(_("<big><b>%s</b></big>\t%s"),display,start_date ? start_date : "");
				logtxt=g_markup_printf_escaped(
				_("<small><i>%s</i>\t" 
				  "<i>Quality: %s</i></small>\n%s\t%s\t"),
				addr, quality, minutes, seconds);
		} else {
			headtxt=g_markup_printf_escaped(_("<big><b>%s</b></big>\t%s"),display,start_date ? start_date : "");
			logtxt=g_markup_printf_escaped(
			_("<small><i>%s</i></small>\t"
				"\n%s"),addr, status);
		}
		g_free(minutes);
		g_free(seconds);
		if (start_date) g_free(start_date);
		gtk_tree_store_append (store,&iter,NULL);

		GdkPixbuf *incoming = create_pixbuf("call_status_incoming.png");
		GdkPixbuf *outgoing = create_pixbuf("call_status_outgoing.png");
		gtk_tree_store_set (store,&iter,
		               0, linphone_call_log_get_dir(cl)==LinphoneCallOutgoing ? outgoing : incoming,
		               1, headtxt,2,cl,-1);
		gtk_tree_store_append (store,&iter2,&iter);
		gtk_tree_store_set (store,&iter2,1,logtxt,-1);
		ms_free(addr);
		g_free(logtxt);
		g_free(headtxt);
	}
}