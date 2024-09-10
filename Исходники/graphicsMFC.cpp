void cGraphicsMFC::setClipRegion(cRealBox *pclipbox)
{
	if (!pclipbox)
		_pMemDC->SelectClipRgn(NULL); //Makes the clipping region the client window.
	else
	{
		CRgn cliprgn; //Temporary region used as a kind of scratchpad.
		CRect crectclipbox = realBoxToCRect(*pclipbox);
		cliprgn.CreateRectRgn(crectclipbox.left, crectclipbox.top, crectclipbox.right,
			crectclipbox.bottom);
		_pMemDC->SelectClipRgn(&cliprgn); //Makes a copy of cliprgn.
		cliprgn.DeleteObject(); //Need to do this, or resource leak!  CRgn destructor won't do it.
	}
} 