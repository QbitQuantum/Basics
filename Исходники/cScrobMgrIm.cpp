//----------------------------------------------------------------------------------------------
// ON MOUSE MOVE
//----------------------------------------------------------------------------------------------
void cScrobMgrIm :: on_mouse_move ( int x, int y )
{
	if ( mouse_is_outside_our_client_area ( x, y ) )
	{
		cPtI Inside; 
		get_last_inside_point ( &Inside, x, y );
		on_mouse_left_up ( Inside.x, Inside.y );
	}

	else
	{
	   ImageList_DragMove ( x + ClientOffset.x, y + ClientOffset.y );
	}
}