///////////////////////////////////////////////////////////////////
// InflateRegion - Inflates a region by the x and y values
// specified in nXInflate and nYInflate
// Creates a new region that represents the inflated region
// (retains the contents of the old region)
// Returns NULL if unsuccessfull
static HRGN InflateRegion(HRGN hRgn, int nXInflate, int nYInflate)
{
	// Local Variables
	LPRGNDATA lpData;	// The RGNDATA structure
	LPRECT lpRect;		// Pointer to the array of RECT structures
	DWORD BufSize;		// The amount of memory required
	DWORD i;			// General index variable
	HRGN hRgnNew;		// The newly created region

	// Get the number of rectangles in the region
	BufSize = GetRegionData(hRgn, 0, NULL);
	if(BufSize == 0)
		return NULL;
	// Allocate memory for the RGNDATA structure
	lpData = (LPRGNDATA)malloc(BufSize);
	// Set the location of the RECT structures
	lpRect = (LPRECT)(lpData->Buffer);
	// Get the region data
	if(!GetRegionData(hRgn, BufSize, lpData))
	{
		free(lpData);
		return NULL;
	}
	// Expand (or contract) all the rectangles in the data
	for(i=0; i<lpData->rdh.nCount; i++)
		InflateRect(&lpRect[i], nXInflate, nYInflate);
	// Create the new region
	hRgnNew = ExtCreateRegion(NULL, lpData->rdh.nCount, lpData);
	free((void*)lpData);
	return hRgnNew;
}