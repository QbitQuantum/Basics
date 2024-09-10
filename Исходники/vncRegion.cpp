// Return all the rectangles
BOOL vncRegion::Rectangles(rectlist &rects)
{
	int buffsize;
	DWORD x;
	RGNDATA *buff;

	// If the region is empty then return empty rectangle list
	if (region == NULL)
		return FALSE;

	// Get the size of buffer required
	buffsize = GetRegionData(region, NULL, 0);
	buff = (RGNDATA *) new BYTE [buffsize];
	if (buff == NULL)
		return FALSE;

	// Now get the region data
	if (GetRegionData(region, buffsize, buff))
	{
		for (x=0; x<(buff->rdh.nCount); x++)
		{
			// Obtain the rectangles from the list
			RECT *rect = (RECT *) (((BYTE *) buff) + sizeof(RGNDATAHEADER) + x * sizeof(RECT));
			rects.push_front(*rect);
		}
	}

	// Delete the temporary buffer
	delete [] buff;

	// Return whether there are any rects!
	return !rects.empty();
}