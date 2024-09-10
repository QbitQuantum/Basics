/* Matlab Gateway routine */
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
	int	nXYSize;
	double	adfGeoTransform[6] = {0,1,0,0,0,1}, adfDstGeoTransform[6];
	char	*pszSRS_WKT = NULL;
	char	**papszWarpOptions = NULL;
	GDALDatasetH	hSrcDS, hDstDS;
	GDALDriverH	hDriver;
	GDALRasterBandH hBand;
	GDALColorTableH	hColorTable = NULL;
	OGRSpatialReference oSrcSRS, oDstSRS; 
	GDALResampleAlg	interpMethod = GRA_NearestNeighbour;
	GDALTransformerFunc pfnTransformer = NULL;
	CPLErr		eErr;
	GDAL_GCP	*pasGCPs = NULL;
	static int runed_once = FALSE;	/* It will be set to true if reaches end of main */

	const int *dim_array;
	int	nx, ny, i, j, m, n, c, nBands, registration = 1;
	int	n_dims, typeCLASS, nBytes;
	char	*pszSrcSRS = NULL, *pszSrcWKT = NULL;
	char	*pszDstSRS = NULL, *pszDstWKT = NULL;
	void	*in_data;
	mxArray	*mx_ptr;

	unsigned char *tmpByte, *outByte;
	unsigned short int *tmpUI16, *outUI16;
	short int *tmpI16, *outI16;
	int	*tmpI32, *outI32;
	int	nPixels=0, nLines=0, nForceWidth=0, nForceHeight=0;
	int	nGCPCount = 0, nOrder = 0;
	unsigned int *tmpUI32, *outUI32;
	float	*tmpF32, *outF32;
	double	*tmpF64, *outF64, *ptr_d;
	double	dfMinX=0, dfMaxX=0, dfMinY=0, dfMaxY=0, dfResX=0, dfResY=0;
	double	adfExtent[4];
	double	dfXRes=0.0, dfYRes=0.0;
	double	dfWarpMemoryLimit = 0.0;
	double	*pdfDstNodata = NULL; 
	char	**papszMetadataOptions = NULL;
	char	*tmp, *txt;


	if (nrhs == 2 && mxIsStruct(prhs[1])) {
		mx_ptr = mxGetField(prhs[1], 0, "ULx");
		if (mx_ptr == NULL)
			mexErrMsgTxt("GDALWARP 'ULx' field not provided");
		ptr_d = mxGetPr(mx_ptr);
		adfGeoTransform[0] = *ptr_d;

		mx_ptr = mxGetField(prhs[1], 0, "Xinc");
		if (mx_ptr == NULL)
			mexErrMsgTxt("GDALWARP 'Xinc' field not provided");
		ptr_d = mxGetPr(mx_ptr);
		adfGeoTransform[1] = *ptr_d;

		mx_ptr = mxGetField(prhs[1], 0, "ULy");
		if (mx_ptr == NULL)
			mexErrMsgTxt("GDALWARP 'ULy' field not provided");
		ptr_d = mxGetPr(mx_ptr);
		adfGeoTransform[3] = *ptr_d;

		mx_ptr = mxGetField(prhs[1], 0, "Yinc");
		if (mx_ptr == NULL)
			mexErrMsgTxt("GDALWARP 'Yinc' field not provided");
		ptr_d = mxGetPr(mx_ptr);
		adfGeoTransform[5] = -*ptr_d;

		/* -------- See for resolution requests ------------ */
		mx_ptr = mxGetField(prhs[1], 0, "t_size");
		if (mx_ptr != NULL) {
			ptr_d = mxGetPr(mx_ptr);
			if (mxGetN(mx_ptr) == 2) {
				nForceWidth  = (int)ptr_d[0];
				nForceHeight = (int)ptr_d[1];
			}
			else if (mxGetN(mx_ptr) == 1) {	/* pick max(nrow,ncol) */
				if (mxGetM(prhs[0]) > getNK(prhs[0],1))
					nForceHeight = mxGetM(prhs[0]);
				else
					nForceWidth  = getNK(prhs[0], 1);
			}
			else {
				nForceHeight = mxGetM(prhs[0]);
				nForceWidth  = getNK(prhs[0], 1);
			}
		}

		mx_ptr = mxGetField(prhs[1], 0, "t_res");
		if (mx_ptr != NULL) {
			ptr_d = mxGetPr(mx_ptr);
			if (mxGetN(mx_ptr) == 2) {
				dfXRes = ptr_d[0];
				dfYRes = ptr_d[1];
			}
			else if (mxGetN(mx_ptr) == 1) {
				dfXRes = dfYRes = ptr_d[0];
			}
		}
		/* -------------------------------------------------- */

		/* -------- Change Warping cache size?  ------------ */
		mx_ptr = mxGetField(prhs[1], 0, "wm");
		if (mx_ptr != NULL) {
			ptr_d = mxGetPr(mx_ptr);
			dfWarpMemoryLimit = *ptr_d * 1024 * 1024;
		}
		/* -------------------------------------------------- */

		/* -------- Have a nodata value order? -------------- */
		mx_ptr = mxGetField(prhs[1], 0, "nodata");
		if (mx_ptr != NULL) {
			pdfDstNodata = mxGetPr(mx_ptr);
		}
		/* -------------------------------------------------- */

		/* -------- See for projection stuff ---------------- */
		mx_ptr = mxGetField(prhs[1], 0, "SrcProjSRS");
		if (mx_ptr != NULL)
			pszSrcSRS = (char *)mxArrayToString(mx_ptr);

		mx_ptr = mxGetField(prhs[1], 0, "SrcProjWKT");
		if (mx_ptr != NULL)
			pszSrcWKT = (char *)mxArrayToString(mx_ptr);

		mx_ptr = mxGetField(prhs[1], 0, "DstProjSRS");
		if (mx_ptr != NULL)
			pszDstSRS = (char *)mxArrayToString(mx_ptr);

		mx_ptr = mxGetField(prhs[1], 0, "DstProjWKT");
		if (mx_ptr != NULL)
			pszDstWKT = (char *)mxArrayToString(mx_ptr);
		/* -------------------------------------------------- */

		/* -------- Do we have GCPs? ----------------------- */
		mx_ptr = mxGetField(prhs[1], 0, "gcp");
		if (mx_ptr != NULL) {
			nGCPCount = mxGetM(mx_ptr);
			if (mxGetN(mx_ptr) != 4)
				mexErrMsgTxt("GDALWARP: GCPs must be a Mx4 array");
			ptr_d = mxGetPr(mx_ptr);
			pasGCPs = (GDAL_GCP *) mxCalloc( nGCPCount, sizeof(GDAL_GCP) );
			GDALInitGCPs( 1, pasGCPs + nGCPCount - 1 );
			for (i = 0; i < nGCPCount; i++) {
				pasGCPs[i].dfGCPPixel = ptr_d[i];
				pasGCPs[i].dfGCPLine = ptr_d[i+nGCPCount];
				pasGCPs[i].dfGCPX = ptr_d[i+2*nGCPCount];
				pasGCPs[i].dfGCPY = ptr_d[i+3*nGCPCount];
				pasGCPs[i].dfGCPZ = 0;
			}
		}
			/* ---- Have we an order request? --- */
		mx_ptr = mxGetField(prhs[1], 0, "order");
		if (mx_ptr != NULL) {
			ptr_d = mxGetPr(mx_ptr);
			nOrder = (int)*ptr_d;
			if (nOrder != -1 || nOrder != 0 || nOrder != 1 || nOrder != 2 || nOrder != 3)
				nOrder = 0;
		}
		/* -------------------------------------------------- */

		mx_ptr = mxGetField(prhs[1], 0, "ResampleAlg");
		if (mx_ptr != NULL) {
			txt = (char *)mxArrayToString(mx_ptr);
			if (!strcmp(txt,"nearest"))
				interpMethod = GRA_NearestNeighbour;
			else if (!strcmp(txt,"bilinear"))
				interpMethod = GRA_Bilinear;
			else if (!strcmp(txt,"cubic") || !strcmp(txt,"bicubic"))
				interpMethod = GRA_Cubic;
			else if (!strcmp(txt,"spline"))
				interpMethod = GRA_CubicSpline;
		}

		/* If grid limits were in grid registration, convert them to pixel reg */
		mx_ptr = mxGetField(prhs[1], 0, "Reg");
		if (mx_ptr != NULL) {
			ptr_d = mxGetPr(mx_ptr);
			registration = (int)ptr_d[0];
		}

		if (registration == 0) {
			adfGeoTransform[0] -= adfGeoTransform[1]/2.;
			adfGeoTransform[3] -= adfGeoTransform[5]/2.;
		}
	}
	else {
		mexPrintf("Usage: B = gdalwarp_mex(IMG,HDR_STRUCT)\n\n");
		mexPrintf("\tIMG -> is a Mx2 or Mx3 array with an grid/image data to reproject\n");
		mexPrintf("\tHDR_STRUCT -> is a structure with the following fields:\n");
		mexPrintf("\t\t'ULx' X coordinate of the uper left corner\n");
		mexPrintf("\t\t'ULy' Y coordinate of the uper left corner\n");
		mexPrintf("\t\t'Xinc' distance between columns in target grid/image coordinates\n");
		mexPrintf("\t\t'Yinc' distance between rows in target grid/image coordinates\n");
		mexPrintf("\t\t'SrcProjSRS', 'SrcProjWKT' -> Source projection string\n");
		mexPrintf("\t\t'DstProjSRS', 'DstProjWKT' -> Target projection string\n");
		mexPrintf("\t\t\tSRS stands for a string of the type used by proj4\n");
		mexPrintf("\t\t\tWKT stands for a string on the 'Well Known Text' format\n\n");
		mexPrintf("\t\t\tIf one of the Src or Dst fields is absent a GEOGRAPHIC WGS84 is assumed\n");
		mexPrintf("\nOPTIONS\n");
		mexPrintf("\t\t'gcp' a [Mx4] array with Ground Control Points\n");
		mexPrintf("\t\t't_size' a [width height] vector to set output file size in pixels\n");
		mexPrintf("\t\t't_res' a [xres yres] vector to set output file resolution (in target georeferenced units)\n");
		mexPrintf("\t\t'wm' amount of memory (in megabytes) that the warp API is allowed to use for caching\n");
		mexPrintf("\t\t'nodata' Set nodata values for output bands.\n");
		mexPrintf("\t\t'ResampleAlg' To set up the algorithm used during warp operation. Options are: \n");
		mexPrintf("\t\t\t'nearest' Use nearest neighbour resampling (default, fastest algorithm, worst interpolation quality).\n");
		mexPrintf("\t\t\t'bilinear' Use bilinear resampling.\n");
		mexPrintf("\t\t\t'cubic' Use cubic resampling.\n");
		mexPrintf("\t\t\t'spline' Use cubic spline resampling.\n\n");

		if (!runed_once)		/* Do next call only at first time this MEX is loaded */
			GDALAllRegister();

        	mexPrintf( "The following format drivers are configured and support Create() method:\n" );
        	for( i = 0; i < GDALGetDriverCount(); i++ ) {
			hDriver = GDALGetDriver(i);
			if( GDALGetMetadataItem( hDriver, GDAL_DCAP_CREATE, NULL ) != NULL)
				mexPrintf("%s: %s\n", GDALGetDriverShortName(hDriver), 
							GDALGetDriverLongName(hDriver));
		}
		return;
	}

	n_dims = mxGetNumberOfDimensions(prhs[0]);
	dim_array=mxGetDimensions(prhs[0]);
	ny = dim_array[0];
	nx = dim_array[1];
	nBands = dim_array[2];

	if (n_dims == 2)	/* Otherwise it would stay undefined */
		nBands = 1;

	/* Find out in which data type was given the input array */
	if (mxIsUint8(prhs[0])) {
		typeCLASS = GDT_Byte;		nBytes = 1;
		outByte = (unsigned char *)mxMalloc (nx*ny * sizeof(unsigned char));
	}
	else if (mxIsUint16(prhs[0])) {
		typeCLASS = GDT_UInt16;		nBytes = 2;
		outUI16 = (unsigned short int *)mxMalloc (nx*ny * sizeof(short int));
	}
	else if (mxIsInt16(prhs[0])) {
		typeCLASS = GDT_Int16;		nBytes = 2;
		outI16 = (short int *)mxMalloc (nx*ny * sizeof(short int));
	}
	else if (mxIsInt32(prhs[0])) {
		typeCLASS = GDT_Int32;		nBytes = 4;
		outI32 = (int *)mxMalloc (nx*ny * sizeof(int));
	}
	else if (mxIsUint32(prhs[0])) {
		typeCLASS = GDT_UInt32;		nBytes = 4;
		outUI32 = (unsigned int *)mxMalloc (nx*ny * sizeof(int));
	}
	else if (mxIsSingle(prhs[0])) {
		typeCLASS = GDT_Float32;	nBytes = 4;
		outF32 = (float *)mxMalloc (nx*ny * sizeof(float));
	}
	else if (mxIsDouble(prhs[0])) {
		typeCLASS = GDT_Float64;	nBytes = 8;
		outF64 = (double *)mxMalloc (nx*ny * sizeof(double));
	}
	else
		mexErrMsgTxt("GDALWARP Unknown input data class!");


	in_data = (void *)mxGetData(prhs[0]);

	if (!runed_once)		/* Do next call only at first time this MEX is loaded */
		GDALAllRegister();

	hDriver = GDALGetDriverByName( "MEM" ); 

	hSrcDS = GDALCreate( hDriver, "mem", nx, ny, nBands, (GDALDataType)typeCLASS, NULL );
	if (hSrcDS == NULL) {
		mexPrintf ("GDALOpen failed - %d\n%s\n", CPLGetLastErrorNo(), CPLGetLastErrorMsg());
		return;
	}
	GDALSetGeoTransform( hSrcDS, adfGeoTransform ); 

	/* ---------- Set the Source projection ---------------------------- */
	/* If it was not provided assume it is Geog WGS84 */
	if (pszSrcSRS == NULL && pszSrcWKT == NULL)
		oSrcSRS.SetWellKnownGeogCS( "WGS84" ); 
	else if (pszSrcWKT != NULL)
		oSrcSRS.importFromWkt( &pszSrcWKT );

	else {
		if( oSrcSRS.SetFromUserInput( pszSrcSRS ) != OGRERR_NONE )
			mexErrMsgTxt("GDAL_WARP_MEX: Translating source SRS failed.");
	}
	if (pszSrcWKT == NULL)
		oSrcSRS.exportToWkt( &pszSrcWKT );

	GDALSetProjection( hSrcDS, pszSrcWKT );	
	//pszSrcWKT = (char *)GDALGetProjectionRef( hSrcDS );
	CPLAssert( pszSrcWKT != NULL && strlen(pszSrcWKT) > 0 );
	/* ------------------------------------------------------------------ */


	/* -------------- Copy input data into the hSrcDS dataset ----------- */
	for (i = 1; i <= nBands; i++) {
		hBand = GDALGetRasterBand( hSrcDS, i ); 
		nXYSize = (i-1)*nx*ny;
		switch( typeCLASS ) {
			case GDT_Byte:
			 	tmpByte = (unsigned char *)in_data;	
				for (m = ny-1, c = 0; m >= 0; m--) for (n = 0; n < nx; n++)
					outByte[c++] = tmpByte[m + n*ny + nXYSize];
				GDALRasterIO( hBand, GF_Write, 0, 0, nx, ny,outByte, nx, ny, (GDALDataType)typeCLASS, 0, 0 );
				break;
			case GDT_UInt16:
			 	tmpUI16 = (unsigned short int *)in_data;	
				for (m = ny-1, c = 0; m >= 0; m--) for (n = 0; n < nx; n++)
					outUI16[c++] = tmpUI16[m + n*ny + nXYSize];
				GDALRasterIO( hBand, GF_Write, 0, 0, nx, ny,outUI16, nx, ny, (GDALDataType)typeCLASS, 0, 0 );
				break;
			case GDT_Int16:
			 	tmpI16 = (short int *)in_data;	
				for (m = ny-1, c = 0; m >= 0; m--) for (n = 0; n < nx; n++)
					outI16[c++] = tmpI16[m + n*ny + nXYSize];
				GDALRasterIO( hBand, GF_Write, 0, 0, nx, ny,outI16, nx, ny, (GDALDataType)typeCLASS, 0, 0 );
				break;
			case GDT_UInt32:
			 	tmpUI32 = (unsigned int *)in_data;	
				for (m = ny-1, c = 0; m >= 0; m--) for (n = 0; n < nx; n++)
					outUI32[c++] = tmpUI32[m + n*ny + nXYSize];
				GDALRasterIO( hBand, GF_Write, 0, 0, nx, ny,outUI32, nx, ny, (GDALDataType)typeCLASS, 0, 0 );
				break;
			case GDT_Int32:
			 	tmpI32 = (int *)in_data;	
				for (m = ny-1, c = 0; m >= 0; m--) for (n = 0; n < nx; n++)
					outI32[c++] = tmpI32[m + n*ny + nXYSize];
				GDALRasterIO( hBand, GF_Write, 0, 0, nx, ny,outI32, nx, ny, (GDALDataType)typeCLASS, 0, 0 );
				break;
			case GDT_Float32:
			 	tmpF32 = (float *)in_data;	
				for (m = ny-1, c = 0; m >= 0; m--) for (n = 0; n < nx; n++)
					outF32[c++] = tmpF32[m + n*ny + nXYSize];
				GDALRasterIO( hBand, GF_Write, 0, 0, nx, ny,outF32, nx, ny, (GDALDataType)typeCLASS, 0, 0 );
				break;
			case GDT_Float64:
			 	tmpF64 = (double *)in_data;	
				for (m = ny-1, c = 0; m >= 0; m--) for (n = 0; n < nx; n++)
					outF64[c++] = tmpF64[m + n*ny + nXYSize];
				GDALRasterIO( hBand, GF_Write, 0, 0, nx, ny,outF64, nx, ny, (GDALDataType)typeCLASS, 0, 0 );
				break;
		}
	}

	/* ---------- Set up the Target coordinate system ------------------- */
	/* If it was not provided assume it is Geog WGS84 */
	CPLErrorReset();
	if (pszDstSRS == NULL && pszDstWKT == NULL)
		oDstSRS.SetWellKnownGeogCS( "WGS84" ); 
	else if (pszDstWKT != NULL)
		oDstSRS.importFromWkt( &pszDstWKT );
	else {
		if( oDstSRS.SetFromUserInput( pszDstSRS ) != OGRERR_NONE )
			mexErrMsgTxt("GDAL_WARP_MEX: Translating target SRS failed.");
	}
	if (pszDstWKT == NULL)
		oDstSRS.exportToWkt( &pszDstWKT );
	/* ------------------------------------------------------------------ */

	if ( nGCPCount != 0 ) {
		if (GDALSetGCPs(hSrcDS, nGCPCount, pasGCPs, "") != CE_None)
			mexPrintf("GDALWARP WARNING: writing GCPs failed.\n");
	}

	/* Create a transformer that maps from source pixel/line coordinates
	   to destination georeferenced coordinates (not destination pixel line) 
	   We do that by omitting the destination dataset handle (setting it to NULL). */

	void *hTransformArg;

	hTransformArg = GDALCreateGenImgProjTransformer(hSrcDS, pszSrcWKT, NULL, pszDstWKT, 
											nGCPCount == 0 ? FALSE : TRUE, 0, nOrder);
	if( hTransformArg == NULL )
		mexErrMsgTxt("GDALTRANSFORM: Generating transformer failed.");

	GDALTransformerInfo *psInfo = (GDALTransformerInfo*)hTransformArg;

	/* -------------------------------------------------------------------------- */
	/*      Get approximate output georeferenced bounds and resolution for file
	/* -------------------------------------------------------------------------- */
	if (GDALSuggestedWarpOutput2(hSrcDS, GDALGenImgProjTransform, hTransformArg, 
	                             adfDstGeoTransform, &nPixels, &nLines, adfExtent,
	                             0) != CE_None ) {
	    GDALClose(hSrcDS);
		mexErrMsgTxt("GDALWARP: GDALSuggestedWarpOutput2 failed.");
	}

	if (CPLGetConfigOption( "CHECK_WITH_INVERT_PROJ", NULL ) == NULL) {
		double MinX = adfExtent[0];
		double MaxX = adfExtent[2];
		double MaxY = adfExtent[3];
		double MinY = adfExtent[1];
		int bSuccess = TRUE;
            
		/* Check that the the edges of the target image are in the validity area */
		/* of the target projection */
#define N_STEPS 20
		for (i = 0; i <= N_STEPS && bSuccess; i++) {
			for (j = 0; j <= N_STEPS && bSuccess; j++) {
				double dfRatioI = i * 1.0 / N_STEPS;
				double dfRatioJ = j * 1.0 / N_STEPS;
				double expected_x = (1 - dfRatioI) * MinX + dfRatioI * MaxX;
				double expected_y = (1 - dfRatioJ) * MinY + dfRatioJ * MaxY;
				double x = expected_x;
				double y = expected_y;
				double z = 0;
				/* Target SRS coordinates to source image pixel coordinates */
				if (!psInfo->pfnTransform(hTransformArg, TRUE, 1, &x, &y, &z, &bSuccess) || !bSuccess)
					bSuccess = FALSE;
				/* Source image pixel coordinates to target SRS coordinates */
				if (!psInfo->pfnTransform(hTransformArg, FALSE, 1, &x, &y, &z, &bSuccess) || !bSuccess)
					bSuccess = FALSE;
				if (fabs(x - expected_x) > (MaxX - MinX) / nPixels ||
					fabs(y - expected_y) > (MaxY - MinY) / nLines)
					bSuccess = FALSE;
			}
		}
            
		/* If not, retry with CHECK_WITH_INVERT_PROJ=TRUE that forces ogrct.cpp */
		/* to check the consistency of each requested projection result with the */
		/* invert projection */
		if (!bSuccess) {
			CPLSetConfigOption( "CHECK_WITH_INVERT_PROJ", "TRUE" );
			CPLDebug("WARP", "Recompute out extent with CHECK_WITH_INVERT_PROJ=TRUE");

			if (GDALSuggestedWarpOutput2(hSrcDS, GDALGenImgProjTransform, hTransformArg, 
			                             adfDstGeoTransform, &nPixels, &nLines, adfExtent,
			                              0) != CE_None ) {
			    GDALClose(hSrcDS);
				mexErrMsgTxt("GDALWARO: GDALSuggestedWarpOutput2 failed.");
			}
		}
	}

	/* -------------------------------------------------------------------- */
	/*      Expand the working bounds to include this region, ensure the    */
	/*      working resolution is no more than this resolution.             */
	/* -------------------------------------------------------------------- */
	if( dfMaxX == 0.0 && dfMinX == 0.0 ) {
		dfMinX = adfExtent[0];
		dfMaxX = adfExtent[2];
		dfMaxY = adfExtent[3];
		dfMinY = adfExtent[1];
		dfResX = adfDstGeoTransform[1];
		dfResY = ABS(adfDstGeoTransform[5]);
	}
	else {
		dfMinX = MIN(dfMinX,adfExtent[0]);
		dfMaxX = MAX(dfMaxX,adfExtent[2]);
		dfMaxY = MAX(dfMaxY,adfExtent[3]);
		dfMinY = MIN(dfMinY,adfExtent[1]);
		dfResX = MIN(dfResX,adfDstGeoTransform[1]);
		dfResY = MIN(dfResY,ABS(adfDstGeoTransform[5]));
	}

	GDALDestroyGenImgProjTransformer( hTransformArg );

	/* -------------------------------------------------------------------- */
	/*      Turn the suggested region into a geotransform and suggested     */
	/*      number of pixels and lines.                                     */
	/* -------------------------------------------------------------------- */

	adfDstGeoTransform[0] = dfMinX;
	adfDstGeoTransform[1] = dfResX;
	adfDstGeoTransform[2] = 0.0;
	adfDstGeoTransform[3] = dfMaxY;
	adfDstGeoTransform[4] = 0.0;
	adfDstGeoTransform[5] = -1 * dfResY;

	nPixels = (int) ((dfMaxX - dfMinX) / dfResX + 0.5);
	nLines  = (int) ((dfMaxY - dfMinY) / dfResY + 0.5);

	/* -------------------------------------------------------------------- */
	/*      Did the user override some parameters?                          */
	/* -------------------------------------------------------------------- */
	if( dfXRes != 0.0 && dfYRes != 0.0 ) {
		dfMinX = adfDstGeoTransform[0];
		dfMaxX = adfDstGeoTransform[0] + adfDstGeoTransform[1] * nPixels;
		dfMaxY = adfDstGeoTransform[3];
		dfMinY = adfDstGeoTransform[3] + adfDstGeoTransform[5] * nLines;

		nPixels = (int) ((dfMaxX - dfMinX + (dfXRes/2.0)) / dfXRes);
		nLines = (int) ((dfMaxY - dfMinY + (dfYRes/2.0)) / dfYRes);
		adfDstGeoTransform[0] = dfMinX;
		adfDstGeoTransform[3] = dfMaxY;
		adfDstGeoTransform[1] = dfXRes;
		adfDstGeoTransform[5] = -dfYRes;
	}
	else if( nForceWidth != 0 && nForceHeight != 0 ) {
		dfXRes = (dfMaxX - dfMinX) / nForceWidth;
		dfYRes = (dfMaxY - dfMinY) / nForceHeight;

		adfDstGeoTransform[0] = dfMinX;
		adfDstGeoTransform[3] = dfMaxY;
		adfDstGeoTransform[1] = dfXRes;
		adfDstGeoTransform[5] = -dfYRes;

		nPixels = nForceWidth;
		nLines = nForceHeight;
	}
	else if( nForceWidth != 0) {
		dfXRes = (dfMaxX - dfMinX) / nForceWidth;
		dfYRes = dfXRes;

		adfDstGeoTransform[0] = dfMinX;
		adfDstGeoTransform[3] = dfMaxY;
		adfDstGeoTransform[1] = dfXRes;
		adfDstGeoTransform[5] = -dfYRes;

		nPixels = nForceWidth;
		nLines = (int) ((dfMaxY - dfMinY + (dfYRes/2.0)) / dfYRes);
	}
	else if( nForceHeight != 0) {
		dfYRes = (dfMaxY - dfMinY) / nForceHeight;
		dfXRes = dfYRes;

		adfDstGeoTransform[0] = dfMinX;
		adfDstGeoTransform[3] = dfMaxY;
		adfDstGeoTransform[1] = dfXRes;
		adfDstGeoTransform[5] = -dfYRes;

		nPixels = (int) ((dfMaxX - dfMinX + (dfXRes/2.0)) / dfXRes);
		nLines = nForceHeight;
	}

	/* --------------------- Create the output --------------------------- */
	hDstDS = GDALCreate( hDriver, "mem", nPixels, nLines, 
			GDALGetRasterCount(hSrcDS), (GDALDataType)typeCLASS, NULL );
    
	CPLAssert( hDstDS != NULL );

	/* -------------- Write out the projection definition ---------------- */
	GDALSetProjection( hDstDS, pszDstWKT );
	GDALSetGeoTransform( hDstDS, adfDstGeoTransform );

	/* --------------------- Setup warp options -------------------------- */
	GDALWarpOptions *psWO = GDALCreateWarpOptions();

	psWO->hSrcDS = hSrcDS;
	psWO->hDstDS = hDstDS;

	psWO->nBandCount = nBands;
	psWO->panSrcBands = (int *) CPLMalloc(psWO->nBandCount * sizeof(int) );
	psWO->panDstBands = (int *) CPLMalloc(psWO->nBandCount * sizeof(int) );
	for( i = 0; i < nBands; i++ ) {
		psWO->panSrcBands[i] = i+1;
		psWO->panDstBands[i] = i+1;
	}

	if( dfWarpMemoryLimit != 0.0 )
		psWO->dfWarpMemoryLimit = dfWarpMemoryLimit;

	/* --------------------- Setup the Resampling Algo ------------------- */
	psWO->eResampleAlg = interpMethod;


	/* --------------------- Setup NODATA options ------------------------ */
	papszWarpOptions = CSLSetNameValue(papszWarpOptions, "INIT_DEST", "NO_DATA" );

	if ( pdfDstNodata == NULL && (typeCLASS == GDT_Float32 || typeCLASS == GDT_Float64) ) {
		pdfDstNodata = (double *) mxCalloc((size_t)1, sizeof(double));
		*pdfDstNodata = mxGetNaN();
	}
	else if (pdfDstNodata != NULL) {
#define CLAMP(val,type,minval,maxval) \
    do { if (val < minval) { val = minval; } \
    else if (val > maxval) { val = maxval; } \
    else if (val != (type)val) { val = (type)(val + 0.5); } } \
    while(0)
		switch( typeCLASS ) {
			case GDT_Byte:
				CLAMP(pdfDstNodata[0], GByte, 0.0, 255.0);
				break;
			case GDT_UInt16:
				CLAMP(pdfDstNodata[0], GInt16, -32768.0, 32767.0);
				break;
			case GDT_Int16:
				CLAMP(pdfDstNodata[0], GUInt16, 0.0, 65535.0);
				break;
			case GDT_UInt32:
				CLAMP(pdfDstNodata[0], GInt32, -2147483648.0, 2147483647.0);
				break;
			case GDT_Int32:
				CLAMP(pdfDstNodata[0], GUInt32, 0.0, 4294967295.0);
				break;
			default:
				break;
		}
	}

	psWO->papszWarpOptions = CSLDuplicate(papszWarpOptions);

	if (pdfDstNodata != NULL) {
		psWO->padfDstNoDataReal = (double *) CPLMalloc(psWO->nBandCount*sizeof(double));
		psWO->padfDstNoDataImag = (double *) CPLMalloc(psWO->nBandCount*sizeof(double));
		for (i = 0; i < nBands; i++) {
                        psWO->padfDstNoDataReal[i] = pdfDstNodata[0];
                        psWO->padfDstNoDataImag[i] = 0.0;
			GDALSetRasterNoDataValue( GDALGetRasterBand(hDstDS, i+1), pdfDstNodata[0]);
		}
	}

	/* ------------ Establish reprojection transformer ------------------- */
	psWO->pTransformerArg = GDALCreateGenImgProjTransformer( hSrcDS, GDALGetProjectionRef(hSrcDS), 
							hDstDS, GDALGetProjectionRef(hDstDS), 
							nGCPCount == 0 ? FALSE : TRUE, 0.0, nOrder );
	psWO->pfnTransformer = GDALGenImgProjTransform;

	/* ----------- Initialize and execute the warp operation ------------- */
	GDALWarpOperation oOperation;

	oOperation.Initialize( psWO );
	eErr = oOperation.ChunkAndWarpImage( 0, 0, GDALGetRasterXSize( hDstDS ),
						GDALGetRasterYSize( hDstDS ) );
	CPLAssert( eErr == CE_None );

	GDALDestroyGenImgProjTransformer( psWO->pTransformerArg );
	GDALDestroyWarpOptions( psWO );
	GDALClose( hSrcDS );

	/* ------------ Free memory used to fill the hSrcDS dataset ---------- */
	switch( typeCLASS ) {
		case GDT_Byte:		mxFree((void *)outByte);	break;
		case GDT_UInt16:	mxFree((void *)outUI16);	break; 
		case GDT_Int16:		mxFree((void *)outI16);		break; 
		case GDT_UInt32:	mxFree((void *)outUI32);	break; 
		case GDT_Int32:		mxFree((void *)outI32);		break; 
		case GDT_Float32:	mxFree((void *)outF32);		break; 
		case GDT_Float64:	mxFree((void *)outF64);		break; 
	}

	int out_dims[3];
	out_dims[0] = nLines;
	out_dims[1] = nPixels;
	out_dims[2] = nBands;
	plhs[0] = mxCreateNumericArray (n_dims,out_dims,mxGetClassID(prhs[0]), mxREAL);
	tmp = (char *)mxCalloc(nPixels * nLines, nBytes);

	/* ------ Allocate memory to be used in filling the hDstDS dataset ---- */
	switch( typeCLASS ) {
		case GDT_Byte:
			outByte = (unsigned char *)mxGetData(plhs[0]);		break;
		case GDT_UInt16:
			outUI16 = (unsigned short int *)mxGetData(plhs[0]);	break;
		case GDT_Int16:
			outI16 = (short int *)mxGetData(plhs[0]);		break;
		case GDT_UInt32:
			outUI32 = (unsigned int *)mxGetData(plhs[0]);		break;
		case GDT_Int32:
			outI32 = (int *)mxGetData(plhs[0]);			break;
		case GDT_Float32:
			outF32 = (float *)mxGetData(plhs[0]);			break;
		case GDT_Float64:
			outF64 = (double *)mxGetData(plhs[0]);			break;
	}

	/* ----------- Copy the output hSrcDS dataset data into plhs  ---------- */
	for (i = 1; i <= nBands; i++) {
		hBand = GDALGetRasterBand( hDstDS, i ); 
		GDALRasterIO( hBand, GF_Read, 0, 0, nPixels, nLines, tmp, nPixels, nLines,
				(GDALDataType)typeCLASS, 0, 0 );
		nXYSize = (i-1) * nPixels * nLines;
		switch( typeCLASS ) {
			case GDT_Byte:
				for (m = nLines-1, c = 0; m >= 0; m--) for (n = 0; n < nPixels; n++)
					outByte[m + n*nLines + nXYSize] = tmp[c++];
				break;
			case GDT_UInt16:
				tmpUI16 = (GUInt16 *) tmp;
				for (m = nLines-1, c = 0; m >= 0; m--) for (n = 0; n < nPixels; n++)
					outUI16[m + n*nLines + nXYSize] = tmpUI16[c++];
				break;
			case GDT_Int16:
				tmpI16 = (GInt16 *) tmp;
				for (m = nLines-1, c = 0; m >= 0; m--) for (n = 0; n < nPixels; n++)
					outI16[m + n*nLines + nXYSize] = tmpI16[c++];
				break;
			case GDT_UInt32:
				tmpUI32 = (GUInt32 *) tmp;
				for (m = nLines-1, c = 0; m >= 0; m--) for (n = 0; n < nPixels; n++)
					outUI32[m + n*nLines + nXYSize] = tmpUI32[c++];
				break;
			case GDT_Int32:
				tmpI32 = (GInt32 *) tmp;
				for (m = nLines-1, c = 0; m >= 0; m--) for (n = 0; n < nPixels; n++)
					outI32[m + n*nLines + nXYSize] = tmpI32[c++];
				break;
			case GDT_Float32:
				tmpF32 = (float *) tmp;
				for (m = nLines-1, c = 0; m >= 0; m--) for (n = 0; n < nPixels; n++)
					outF32[m + n*nLines + nXYSize] = tmpF32[c++];
				break;
			case GDT_Float64:
				tmpF64 = (double *) tmp;
				for (m = nLines-1, c = 0; m >= 0; m--) for (n = 0; n < nPixels; n++)
					outF64[m + n*nLines + nXYSize] = tmpF64[c++];
				break;
		}
	}

	mxFree(tmp);
	if (nGCPCount) {
		GDALDeinitGCPs( nGCPCount, pasGCPs );	/* makes this mex crash in the next call - Is it still true??? */
		mxFree((void *) pasGCPs );
	}

	if (nlhs == 2)
		plhs[1] = populate_metadata_struct (hDstDS, 1);

	runed_once = TRUE;	/* Signals that next call won't need to call GDALAllRegister() again */

	/*GDALDestroyDriverManager();
	OGRFree(pszDstWKT);*/
	GDALClose( hDstDS );
	CSLDestroy( papszWarpOptions );
	if (pszDstWKT && strlen(pszDstWKT) > 1 ) OGRFree(pszDstWKT);	
	if (pszSrcWKT && strlen(pszSrcWKT) > 1 ) OGRFree(pszSrcWKT);
}