/**
 *	This is called when the mouse button is released.
 *
 *  @param flags	The flags which shift-key status etc.
 *  @param point	The coordinates of the mouse.
 */
/*afx_msg*/ void ChunkWatchControl::OnLButtonUp(UINT /*flags*/, CPoint point)
{
	getDrawConstants();

    float x, z;
    if (screenToWorld(point, &x, &z))
    {    
		// Find the height at this point
		float fheight = TerrainUtils::heightAtPos(x, z, true);
		float y = fheight + Options::getOptionInt( "graphics/farclip", 500 )/10.0f;

		// Set the view matrix to the new world coords and preserve the 
		// current orientation:
		Matrix view = WorldEditorCamera::instance().currentCamera().view();
		view.invert();
		view.translation(Vector3(x, y, z));
		view.invert();
		WorldEditorCamera::instance().currentCamera().view(view);
	}
}