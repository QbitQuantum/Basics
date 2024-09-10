int main(int argc, char *argv[] )
{
	GtkWidget *window, *vbox;
	char applName[256];

	// Initialisations
	gtk_init (&argc, &argv);
	StripPath (argv[0], applName);
	CheckMidiShare (applName);
	gRefNum = MidiOpen(applName);
	MidiSetRcvAlarm (gRefNum,rcv_alarm);
	MidiConnect(gRefNum,0,1);
	MidiConnect(0,gRefNum,1);

	// Window definition
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), applName);
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

	vbox = gtk_vbox_new (FALSE, 10);
	
	// Add controllers
	add_time (vbox);
	add(vbox, gtk_hseparator_new());
	add_buttons (vbox);
	
	gtk_container_add(GTK_CONTAINER(window), vbox);	
	gtk_widget_show_all (window);
	
	gtk_signal_connect(GTK_OBJECT(gRun), "clicked", GTK_SIGNAL_FUNC(start_stop_action), NULL);
	gtk_signal_connect(GTK_OBJECT(gReset), "clicked", GTK_SIGNAL_FUNC(reset_action), NULL);

	// Connexion of signals	
	gtk_signal_connect(
			GTK_OBJECT(window), "destroy", 
			GTK_SIGNAL_FUNC(my_delete_action), NULL
	);
	
	gtk_main ();

	return(0);
}