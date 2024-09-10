static void
prefs_destroy( GtkObject *object )
{
	Prefs *prefs = PREFS( object );

#ifdef DEBUG
	printf( "prefs_destroy\n" );
#endif /*DEBUG*/

	if( prefs->ws ) {
		Workspacegroup *wsg = workspace_get_workspacegroup( prefs->ws );
		Filemodel *filemodel = FILEMODEL( wsg );

		/* Force a recalc, in case we've changed the autorecalc 
		 * settings. Also does a scan on any widgets.
		 */
		symbol_recalculate_all_force( TRUE );

		if( filemodel->modified &&
			filemodel_top_save( filemodel, filemodel->filename ) ) 
			filemodel_set_modified( filemodel, FALSE );
	}

	/* My instance destroy stuff.
	 */
	FREESID( prefs->destroy_sid, prefs->ws );
	IM_FREE( prefs->caption_filter );
	prefs->ws = NULL;

	GTK_OBJECT_CLASS( parent_class )->destroy( object );
}