// ChoosePFD
//
// Helper function that replaces ChoosePixelFormat.
//
static int GLW_ChoosePFD( HDC hDC, PIXELFORMATDESCRIPTOR *pPFD )
{
	#define MAX_PFDS 256

	PIXELFORMATDESCRIPTOR pfds[MAX_PFDS+1];
	int maxPFD = 0;
	int i;
	int bestMatch = 0;

	OutputDebugString( va("...GLW_ChoosePFD( %d, %d, %d )\n", ( int ) pPFD->cColorBits, ( int ) pPFD->cDepthBits, ( int ) pPFD->cStencilBits) );

	// count number of PFDs
	//
	maxPFD = DescribePixelFormat( hDC, 1, sizeof( PIXELFORMATDESCRIPTOR ), &pfds[0] );

	if ( maxPFD > MAX_PFDS )
	{
		OutputDebugString( va( "...numPFDs > MAX_PFDS (%d > %d)\n", maxPFD, MAX_PFDS) );
		maxPFD = MAX_PFDS;
	}

	OutputDebugString( va("...%d PFDs found\n", maxPFD - 1) );

	FILE *handle = fopen("c:\\ModView_GL_report.txt","wt");
	if ( !handle )
		return 0;

	fprintf(handle,"Total PFDs: %d\n\n",maxPFD);

	// grab information
	for ( i = 1; i <= maxPFD; i++ )
	{
		DescribePixelFormat( hDC, i, sizeof( PIXELFORMATDESCRIPTOR ), &pfds[i] );

		fprintf(handle,"PFD %d/%d\n",i,maxPFD);
		fprintf(handle,"=========\n");		

#define FLAGDUMP(flag) if ( (pfds[i].dwFlags & flag ) != 0 ) fprintf(handle,"(flag: %s)\n",#flag);

		FLAGDUMP( PFD_DOUBLEBUFFER            );
		FLAGDUMP( PFD_STEREO                  );
		FLAGDUMP( PFD_DRAW_TO_WINDOW          );
		FLAGDUMP( PFD_DRAW_TO_BITMAP          );
		FLAGDUMP( PFD_SUPPORT_GDI             );
		FLAGDUMP( PFD_SUPPORT_OPENGL          );
		FLAGDUMP( PFD_GENERIC_FORMAT          );
		FLAGDUMP( PFD_NEED_PALETTE            );
		FLAGDUMP( PFD_NEED_SYSTEM_PALETTE     );
		FLAGDUMP( PFD_SWAP_EXCHANGE           );
		FLAGDUMP( PFD_SWAP_COPY               );
		FLAGDUMP( PFD_SWAP_LAYER_BUFFERS      );
		FLAGDUMP( PFD_GENERIC_ACCELERATED     );
		FLAGDUMP( PFD_SUPPORT_DIRECTDRAW      );

		if ( pfds[i].iPixelType == PFD_TYPE_RGBA )
		{
//			fprintf(handle,"RGBA mode\n");
		}
		else
		{
			fprintf(handle,"NOT RGBA mode!!!!!!!!!!!!\n");
		}

		fprintf(handle, "Colour bits: %d\n",pfds[i].cColorBits);
		fprintf(handle, "Depth  bits: %d\n",pfds[i].cDepthBits);

		fprintf(handle,"\n");
	}
	

	// look for a best match
	for ( i = 1; i <= maxPFD; i++ )
	{
		fprintf(handle,"(bestMatch: %d)\n",bestMatch );

		//
		// make sure this has hardware acceleration
		//
		if ( ( pfds[i].dwFlags & PFD_GENERIC_FORMAT ) != 0 ) 
		{
//			if ( !r_allowSoftwareGL->integer )
			{
//				if ( r_verbose->integer )
				{
					fprintf(handle,//OutputDebugString(
						 va ("...PFD %d rejected, software acceleration\n", i ));
				}
				continue;
			}
		}

		// verify pixel type
		if ( pfds[i].iPixelType != PFD_TYPE_RGBA )
		{
//			if ( r_verbose->integer )
			{
				fprintf(handle,//OutputDebugString(
					va("...PFD %d rejected, not RGBA\n", i) );
			}
			continue;
		}

		// verify proper flags
		if ( ( ( pfds[i].dwFlags & pPFD->dwFlags ) & pPFD->dwFlags ) != pPFD->dwFlags ) 
		{
//			if ( r_verbose->integer )
			{
				fprintf(handle,//OutputDebugString(
					va("...PFD %d rejected, improper flags (0x%x instead of 0x%x)\n", i, pfds[i].dwFlags, pPFD->dwFlags) );
			}
			continue;
		}

		// verify enough bits
		if ( pfds[i].cDepthBits < 15 )
		{
			fprintf(handle,va("...PFD %d rejected, depth bits only %d (<15)\n", i, pfds[i].cDepthBits) );
			continue;
		}
/*		if ( ( pfds[i].cStencilBits < 4 ) && ( pPFD->cStencilBits > 0 ) )
		{
			continue;
		}
*/
		//
		// selection criteria (in order of priority):
		// 
		//  PFD_STEREO
		//  colorBits
		//  depthBits
		//  stencilBits
		//
		if ( bestMatch )
		{
/*
			// check stereo
			if ( ( pfds[i].dwFlags & PFD_STEREO ) && ( !( pfds[bestMatch].dwFlags & PFD_STEREO ) ) && ( pPFD->dwFlags & PFD_STEREO ) )
			{
				bestMatch = i;
				continue;
			}
			
			if ( !( pfds[i].dwFlags & PFD_STEREO ) && ( pfds[bestMatch].dwFlags & PFD_STEREO ) && ( pPFD->dwFlags & PFD_STEREO ) )
			{
				bestMatch = i;
				continue;
			}
*/
			// check color
			if ( pfds[bestMatch].cColorBits != pPFD->cColorBits )
			{
				// prefer perfect match
				if ( pfds[i].cColorBits == pPFD->cColorBits )
				{
					bestMatch = i;
					continue;
				}
				// otherwise if this PFD has more bits than our best, use it
				else if ( pfds[i].cColorBits > pfds[bestMatch].cColorBits )
				{
					bestMatch = i;
					continue;
				}
			}

			// check depth
			if ( pfds[bestMatch].cDepthBits != pPFD->cDepthBits )
			{
				// prefer perfect match
				if ( pfds[i].cDepthBits == pPFD->cDepthBits )
				{
					bestMatch = i;
					continue;
				}
				// otherwise if this PFD has more bits than our best, use it
				else if ( pfds[i].cDepthBits > pfds[bestMatch].cDepthBits )
				{
					bestMatch = i;
					continue;
				}
			}
/*
			// check stencil
			if ( pfds[bestMatch].cStencilBits != pPFD->cStencilBits )
			{
				// prefer perfect match
				if ( pfds[i].cStencilBits == pPFD->cStencilBits )
				{
					bestMatch = i;
					continue;
				}
				// otherwise if this PFD has more bits than our best, use it
				else if ( ( pfds[i].cStencilBits > pfds[bestMatch].cStencilBits ) && 
					 ( pPFD->cStencilBits > 0 ) )
				{
					bestMatch = i;
					continue;
				}
			}
*/
		}
		else
		{
			bestMatch = i;
		}
	}

	fprintf(handle,"Bestmode: %d\n",bestMatch);
	
	if ( !bestMatch )
	{
		fprintf(handle,"No decent mode found!\n");
		fclose(handle);
		return 0;
	}

	if ( ( pfds[bestMatch].dwFlags & PFD_GENERIC_FORMAT ) != 0 )
	{
//		if ( !r_allowSoftwareGL->integer )
//		{
//			ri.Printf( PRINT_ALL, "...no hardware acceleration found\n" );
//			return 0;
//		}
//		else
		{
			fprintf(handle,//OutputDebugString(
				"...using software emulation\n" );
		}
	}
	else if ( pfds[bestMatch].dwFlags & PFD_GENERIC_ACCELERATED )
	{
		fprintf(handle,//OutputDebugString(
			"...MCD acceleration found\n" );
	}
	else
	{
		fprintf(handle,//OutputDebugString(
			"...hardware acceleration found\n" );
	}

	*pPFD = pfds[bestMatch];

	fclose(handle);

	return bestMatch;
}