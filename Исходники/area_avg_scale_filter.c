/*
 * Initialize the destination byte buffer with image data scaled to the
 * width and height specified from the source byte buffer.
 */
static void fillFourCompBuffer( FilterParam params ) {
	
	int srcWidth, srcHeight, srcComponents, srcPixels;
	int dstWidth, dstHeight;
	
	int row_cmp_size;
	row_cmp_ptr row;
	
	int sx, sy, dx, dy;
	int sxrem, syrem, dxrem, dyrem;
	int amtx, amty;
	int srcRowByteOffset, srcColByteOffset;
	int dstByteOffset;
	int dstRowByteIndex;
	int dstRowByteLength;
	int i;
	float a, r, g, b;
	float ascale, mult;
	
	jbyte *row_data;
	jbyte *srcBuffer;
	jbyte *dstBuffer;
	
	int a_int, r_int, g_int, b_int;
	
	param_ptr source = (param_ptr)params;
	
	srcWidth = source->pub.srcWidth;
	srcHeight = source->pub.srcHeight;
	srcComponents = source->pub.srcComponents;
	srcPixels = srcWidth * srcHeight;
	srcBuffer = source->pub.src_pixel_data;
	
	dstWidth = source->pub.dstWidth;
	dstHeight = source->pub.dstHeight;
	dstBuffer = source->pub.dst_pixel_data;
	
	row = (row_cmp_ptr)malloc( sizeof( row_cmp ) );
	
	row_cmp_size = dstWidth * sizeof( float );
	row->red = (float*)malloc( row_cmp_size );
	row->green = (float*)malloc( row_cmp_size );
	row->blue = (float*)malloc( row_cmp_size );
	row->alpha = (float*)malloc( row_cmp_size );
	
	dstRowByteLength = dstWidth*srcComponents;
	row_data = (jbyte*)malloc( dstRowByteLength );
	
	///////////////////////////////////////////////////////////////////
	sy = 0;
	syrem = dstHeight;
	dy = 0;
	dyrem = 0;
	
	srcRowByteOffset = 0;
	dstByteOffset = 0;
	
	while ( sy < srcHeight ) {
		amty;
		if ( dyrem == 0 ) {
			for ( i = 0; i < dstWidth; i++ ) {
				row->alpha[i] = row->red[i] = row->green[i] = row->blue[i] = 0;
			}
			dyrem = srcHeight;
		}
		if ( syrem < dyrem ) {
			amty = syrem;
		} else {
			amty = dyrem;
		}
		sx = 0;
		dx = 0;
		sxrem = 0;
		dxrem = srcWidth;
		a = 0, r = 0, g = 0, b = 0;
		while ( sx < srcWidth ) {
			if ( sxrem == 0 ) {
				sxrem = dstWidth;
				srcColByteOffset = sx * srcComponents;
				r = 0xff & srcBuffer[ srcRowByteOffset + srcColByteOffset++ ];
				g = 0xff & srcBuffer[ srcRowByteOffset + srcColByteOffset++ ];
				b = 0xff & srcBuffer[ srcRowByteOffset + srcColByteOffset++ ];
				a = 0xff & srcBuffer[ srcRowByteOffset + srcColByteOffset ];
				// premultiply the components if necessary
				if ( a != 255.0 ) {
					ascale = a / 255.0;
					r *= ascale;
					g *= ascale;
					b *= ascale;
				}
			}
			int amtx;
			if ( sxrem < dxrem ) {
				amtx = sxrem;
			} else {
				amtx = dxrem;
			}
			mult = ((float)amtx) * amty;
			row->alpha[dx] += mult * a;
			row->red[dx] += mult * r;
			row->green[dx] += mult * g;
			row->blue[dx] += mult * b;
			if ( ( sxrem -= amtx ) == 0 ) {
				sx++;
			}
			if ( ( dxrem -= amtx ) == 0 ) {
				dx++;
				dxrem = srcWidth;
			}
		}
		if ( ( dyrem -= amty ) == 0 ) {
			///////////////////////////////////////////////////////////////////
			dstRowByteIndex = 0;
			for ( i = 0; i < dstWidth; i++ ) {
				mult = (float)srcPixels;
				a_int = (int)roundf( row->alpha[i] / mult );
				if ( a_int <= 0 ) {
					a_int = 0;
				} else if ( a_int >= 255 ) {
					a_int = 255;
				} else {
					// un-premultiply the components (by modifying mult here, we
					// are effectively doing the divide by mult and divide by
					// alpha in the same step)
					mult = row->alpha[i] / 255;
				}
				r_int = (int)roundf( row->red[i] / mult );
				g_int = (int)roundf( row->green[i] / mult );
				b_int = (int)roundf( row->blue[i] / mult );
				
				if ( r_int < 0 ) { 
					r_int = 0; 
				} else if ( r_int > 255 ) { 
					r_int = 255; 
				}
				if ( g_int < 0 ) { 
					g_int = 0; 
				} else if ( g_int > 255 ) { 
					g_int = 255; 
				}
				if ( b_int < 0 ) { 
					b_int = 0; 
				} else if ( b_int > 255 ) { 
					b_int = 255; 
				}
				
				row_data[dstRowByteIndex++] = (jbyte)r_int;
				row_data[dstRowByteIndex++] = (jbyte)g_int;
				row_data[dstRowByteIndex++] = (jbyte)b_int;
				row_data[dstRowByteIndex++] = (jbyte)a_int;
			}
			///////////////////////////////////////////////////////////////////
			do {
				for ( i = 0; i < dstRowByteLength; i++ ) {
					dstBuffer[ dstByteOffset++ ] = row_data[i];
				}
				dy++;
			} while ( ( ( syrem -= amty ) >= amty ) && ( amty == srcHeight ) );
		} else {
			syrem -= amty;
		}
		if ( syrem == 0 ) {
			syrem = dstHeight;
			sy++;
			srcRowByteOffset += srcWidth * srcComponents;
		}
	}
	///////////////////////////////////////////////////////////////////
	free( row_data );
	free( row->red );
	free( row->green );
	free( row->blue );
	free( row->alpha );
	free( row );
}