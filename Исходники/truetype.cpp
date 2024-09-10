BOOL TrueTypeImport::BuildCharacterEx(UINT index, float height, BezierShape &shape, float &width, int fontShapeVersion, bool ggo_native)  {
    assert(hFont);
	if(!hFont)
		return 0;

	// Set up for the font and release it when this function returns
	FontReady fontRdy(hFont);
			    
	// allocate space for the bitmap/outline
	GLYPHMETRICS gm;
    // init it to prevent UMR in GetGlyphOutline
    gm.gmBlackBoxX = 
    gm.gmBlackBoxY = 
    gm.gmptGlyphOrigin.x =
    gm.gmptGlyphOrigin.y =
    gm.gmCellIncX = 
    gm.gmCellIncY = 0; 

	// Give it an identity matrix
	MAT2 mat;
	IdentityMat(&mat);

	// get unicode outline
	DWORD size;
	if(!ggo_native)
		size= GetGlyphOutlineW(fontRdy.hdc, index, GGO_GLYPH_INDEX|GGO_NATIVE, &gm, 0, NULL, &mat); 
	else
		size= GetGlyphOutlineW(fontRdy.hdc,  (index & 0x0000ffff), GGO_NATIVE, &gm, 0, NULL, &mat); 

	if(size != GDI_ERROR && size > 0) {
		GenericAlloc mem(size);
		if(!mem.ptr)
			goto failure;
		// get unicode outline
		if(!ggo_native){
			if ((GetGlyphOutlineW(fontRdy.hdc, index, GGO_GLYPH_INDEX|GGO_NATIVE, &gm, size, mem.ptr, &mat)) != size)
				goto failure;
		}
		else
		{
			if ((GetGlyphOutlineW(fontRdy.hdc,  (index & 0x0000ffff), GGO_NATIVE, &gm, size, mem.ptr, &mat)) != size)
				goto failure;
		}

		curSpline = NULL;	// reset the current spline pointer
		if(!CreateCharacterShape((TTPOLYGONHEADER *)mem.ptr, size, shape, fontShapeVersion))
			goto failure;
		// Make sure the height matches the request
		float scaleFactor = height / 1000.0f;
		Matrix3 tm = ScaleMatrix(Point3(scaleFactor, scaleFactor, 0.0f));
		shape.Transform(tm);
		width = float(gm.gmCellIncX) * scaleFactor;
		return TRUE;
		}

	// Character wasn't found!
	failure:
	width = 0.0f;
	return FALSE;
	}