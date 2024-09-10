//==============================
// BitmapFontSurfaceLocal::DrawText3D
void BitmapFontSurfaceLocal::DrawText3D( BitmapFont const & font, fontParms_t const & parms,
		Vector3f const & pos, Vector3f const & normal, Vector3f const & up,
		float scale, Vector4f const & color, char const * text )
{
	if ( text == NULL || text[0] == '\0' )
	{
		return;	// nothing to do here, move along
	}

	// TODO: multiple line support -- we would need to calculate the horizontal width
	// for each string ending in \n
	size_t len;
	float width;
	float height;
	float ascent;
	float descent;
	int const MAX_LINES = 128;
	float lineWidths[MAX_LINES];
	int numLines;
	AsLocal( font ).CalcTextMetrics( text, len, width, height, ascent, descent, lineWidths, MAX_LINES, numLines );
//	LOG( "BitmapFontSurfaceLocal::DrawText3D( \"%s\" %s %s ) : width = %.2f, height = %.2f, numLines = %i, fh = %.2f",
//			text, parms.CenterVert ? "cv" : "", parms.CenterHoriz ? "ch" : "",
//			width, height, numLines, AsLocal( font ).GetFontInfo().FontHeight );
	if ( len == 0 )
	{
		return;
	}

	DROID_ASSERT( normal.IsNormalized(), "BitmapFont" );
	DROID_ASSERT( up.IsNormalized(), "BitmapFont" );

	const FontInfoType & fontInfo = AsLocal( font ).GetFontInfo();

	float imageWidth = (float)AsLocal( font ).GetImageWidth();
	float const xScale = AsLocal( font ).GetFontInfo().ScaleFactor * scale;
	float const yScale = AsLocal( font ).GetFontInfo().ScaleFactor * scale;

	// allocate a vertex block
	size_t numVerts = 4 * len;
	VertexBlockType vb( font, numVerts, pos, Quatf(), parms.Billboard, parms.TrackRoll );

	Vector3f const right = up.Cross( normal );
	Vector3f const r = ( parms.Billboard ) ? Vector3f( 1.0f, 0.0f, 0.0f ) : right;
	Vector3f const u = ( parms.Billboard ) ? Vector3f( 0.0f, 1.0f, 0.0f ) : up;

	Vector3f curPos( 0.0f );
	if ( parms.CenterVert )
	{
		float const vofs = ( height * 0.5f ) - ascent;
		curPos += u * ( vofs * scale );
	}

	Vector3f basePos = curPos;
	if ( parms.CenterHoriz )
	{
		curPos -= r * ( lineWidths[0] * 0.5f * scale );
	}
	
	Vector3f lineInc = u * ( fontInfo.FontHeight * yScale );
	float const distanceScale = imageWidth / FontInfoType::DEFAULT_SCALE_FACTOR;
	const uint8_t fontParms[4] = 
	{
			(uint8_t)( OVR::Alg::Clamp( parms.AlphaCenter + fontInfo.CenterOffset, 0.0f, 1.0f ) * 255 ),
			(uint8_t)( OVR::Alg::Clamp( parms.ColorCenter + fontInfo.CenterOffset, 0.0f, 1.0f ) * 255 ),
			(uint8_t)( OVR::Alg::Clamp( distanceScale, 1.0f, 255.0f ) ),
			0
	};

    int iColor = ColorToABGR( color );

	int curLine = 0;
	fontVertex_t * v = vb.Verts;
	char const * p = text;
	size_t i = 0;
	uint32_t charCode = UTF8Util::DecodeNextChar( &p );
	for ( ; charCode != '\0'; i++, charCode = UTF8Util::DecodeNextChar( &p ) )
	{
		OVR_ASSERT( i < len );
		if ( charCode == '\n' && curLine < numLines && curLine < MAX_LINES )
		{
			// move to next line
			curLine++;
			basePos -= lineInc;
			curPos = basePos;
			if ( parms.CenterHoriz )
			{
				curPos -= r * ( lineWidths[curLine] * 0.5f * scale );
			}
		}

		FontGlyphType const & g = AsLocal( font ).GlyphForCharCode( charCode );

		float s0 = g.X;
		float t0 = g.Y;
		float s1 = ( g.X + g.Width );
		float t1 = ( g.Y + g.Height );

		float bearingX = g.BearingX * xScale;
		float bearingY = g.BearingY * yScale ;

		float rw = ( g.Width + g.BearingX ) * xScale;
		float rh = ( g.Height - g.BearingY ) * yScale;

        // lower left
        v[i * 4 + 0].xyz = curPos + ( r * bearingX ) - ( u * rh );
        v[i * 4 + 0].s = s0;
        v[i * 4 + 0].t = t1;
        *(UInt32*)(&v[i * 4 + 0].rgba[0]) = iColor;
		*(UInt32*)(&v[i * 4 + 0].fontParms[0]) = *(UInt32*)(&fontParms[0]);
	    // upper left
        v[i * 4 + 1].xyz = curPos + ( r * bearingX ) + ( u * bearingY );
        v[i * 4 + 1].s = s0;
        v[i * 4 + 1].t = t0;
        *(UInt32*)(&v[i * 4 + 1].rgba[0]) = iColor;
		*(UInt32*)(&v[i * 4 + 1].fontParms[0]) = *(UInt32*)(&fontParms[0]);
        // upper right
        v[i * 4 + 2].xyz = curPos + ( r * rw ) + ( u * bearingY );
        v[i * 4 + 2].s = s1;
        v[i * 4 + 2].t = t0;
        *(UInt32*)(&v[i * 4 + 2].rgba[0]) = iColor;
		*(UInt32*)(&v[i * 4 + 2].fontParms[0]) = *(UInt32*)(&fontParms[0]);
        // lower right
        v[i * 4 + 3].xyz = curPos + ( r * rw ) - ( u * rh );
        v[i * 4 + 3].s = s1;
        v[i * 4 + 3].t = t1;
        *(UInt32*)(&v[i * 4 + 3].rgba[0]) = iColor;
		*(UInt32*)(&v[i * 4 + 3].fontParms[0]) = *(UInt32*)(&fontParms[0]);
		// advance to start of next char
		curPos += r * ( g.AdvanceX * xScale );
	}
	// add the new vertex block to the array of vertex blocks
	VertexBlocks.PushBack( vb );
}