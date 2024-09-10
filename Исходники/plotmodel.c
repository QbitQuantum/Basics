static void
plotmodel_dispose( GObject *gobject )
{
	Plotmodel *plotmodel;

	g_return_if_fail( gobject != NULL );
	g_return_if_fail( IS_PLOTMODEL( gobject ) );

	plotmodel = PLOTMODEL( gobject );

#ifdef DEBUG
	printf( "plotmodel_dispose %p: ", plotmodel );
	iobject_print( IOBJECT( plotmodel ) );
#endif /*DEBUG*/

	/* My instance destroy stuff.
	 */
	FREESID( plotmodel->changed_sid, plotmodel->plot );
	FREESID( plotmodel->destroy_sid, plotmodel->plot );

	G_OBJECT_CLASS( parent_class )->dispose( gobject );
}