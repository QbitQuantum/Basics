static void
workspaceview_destroy( GtkObject *object )
{
	Workspaceview *wview;

#ifdef DEBUG
	printf( "workspaceview_destroy: %p\n", object );
#endif /*DEBUG*/

	g_return_if_fail( object != NULL );
	g_return_if_fail( IS_WORKSPACEVIEW( object ) );

	wview = WORKSPACEVIEW( object );

	/* Instance destroy.
	 */
	workspaceview_scroll_stop( wview );
	IM_FREEF( iwindow_cursor_context_destroy, wview->context );
	FREESID( wview->watch_changed_sid, main_watchgroup );
	DESTROY_GTK( wview->popup );

	GTK_OBJECT_CLASS( parent_class )->destroy( object );
}