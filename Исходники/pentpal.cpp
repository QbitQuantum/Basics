IDataSource * choosePalette()
{
	FileSystem * filesys = FileSystem::get_instance();
	GtkWidget *file_sel;
	gchar *filename;
	gboolean selected = FALSE;

	file_sel = gtk_file_selection_new( "Choose a Palette" );
	gtk_window_set_modal( GTK_WINDOW( file_sel ), TRUE );

	gtk_signal_connect( GTK_OBJECT( file_sel ), "destroy",
                            GTK_SIGNAL_FUNC( file_sel_delete ), &file_sel );

	gtk_signal_connect( GTK_OBJECT( GTK_FILE_SELECTION( file_sel )->cancel_button ), "clicked", GTK_SIGNAL_FUNC( file_sel_delete ), &file_sel );

	gtk_signal_connect( GTK_OBJECT( GTK_FILE_SELECTION( file_sel )->ok_button ), "clicked", GTK_SIGNAL_FUNC( file_selected ), &selected );

	gtk_widget_show( file_sel );

	while( ( ! selected ) && ( file_sel ) )
		gtk_main_iteration();

	/* canceled or window was closed */
	if( ! selected )
		return 0;

	/* ok */
	filename = g_strdup( gtk_file_selection_get_filename( GTK_FILE_SELECTION( file_sel ) ) );
	gtk_widget_destroy( file_sel );

	IDataSource * ds = filesys->ReadFile(filename);
	return ds;
}