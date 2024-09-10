int CPL_STDCALL 
GDALDitherRGB2PCT( GDALRasterBandH hRed, 
                   GDALRasterBandH hGreen, 
                   GDALRasterBandH hBlue, 
                   GDALRasterBandH hTarget, 
                   GDALColorTableH hColorTable,
                   GDALProgressFunc pfnProgress, 
                   void * pProgressArg )

{
    VALIDATE_POINTER1( hRed, "GDALDitherRGB2PCT", CE_Failure );
    VALIDATE_POINTER1( hGreen, "GDALDitherRGB2PCT", CE_Failure );
    VALIDATE_POINTER1( hBlue, "GDALDitherRGB2PCT", CE_Failure );
    VALIDATE_POINTER1( hTarget, "GDALDitherRGB2PCT", CE_Failure );
    VALIDATE_POINTER1( hColorTable, "GDALDitherRGB2PCT", CE_Failure );

    int		nXSize, nYSize;
    CPLErr err = CE_None;
    
/* -------------------------------------------------------------------- */
/*      Validate parameters.                                            */
/* -------------------------------------------------------------------- */
    nXSize = GDALGetRasterBandXSize( hRed );
    nYSize = GDALGetRasterBandYSize( hRed );

    if( GDALGetRasterBandXSize( hGreen ) != nXSize 
        || GDALGetRasterBandYSize( hGreen ) != nYSize 
        || GDALGetRasterBandXSize( hBlue ) != nXSize 
        || GDALGetRasterBandYSize( hBlue ) != nYSize )
    {
        CPLError( CE_Failure, CPLE_IllegalArg,
                  "Green or blue band doesn't match size of red band.\n" );

        return CE_Failure;
    }

    if( GDALGetRasterBandXSize( hTarget ) != nXSize 
        || GDALGetRasterBandYSize( hTarget ) != nYSize )
    {
        CPLError( CE_Failure, CPLE_IllegalArg,
                  "GDALDitherRGB2PCT(): "
                  "Target band doesn't match size of source bands.\n" );

        return CE_Failure;
    }

    if( pfnProgress == NULL )
        pfnProgress = GDALDummyProgress;

/* -------------------------------------------------------------------- */
/*      Setup more direct colormap.                                     */
/* -------------------------------------------------------------------- */
    int		nColors, anPCT[768], iColor;

    nColors = GDALGetColorEntryCount( hColorTable );
    
    if (nColors == 0 )
    {
        CPLError( CE_Failure, CPLE_IllegalArg,
                  "GDALDitherRGB2PCT(): "
                  "Color table must not be empty.\n" );

        return CE_Failure;
    }
    else if (nColors > 256)
    {
        CPLError( CE_Failure, CPLE_IllegalArg,
                  "GDALDitherRGB2PCT(): "
                  "Color table cannot have more than 256 entries.\n" );

        return CE_Failure;
    }
    
    for( iColor = 0; iColor < nColors; iColor++ )
    {
        GDALColorEntry	sEntry;

        GDALGetColorEntryAsRGB( hColorTable, iColor, &sEntry );
        
        anPCT[iColor    ] = sEntry.c1;
        anPCT[iColor+256] = sEntry.c2;
        anPCT[iColor+512] = sEntry.c3;
    }
    
/* -------------------------------------------------------------------- */
/*      Build a 24bit to 8 bit color mapping.                           */
/* -------------------------------------------------------------------- */
    GByte	*pabyColorMap;

    pabyColorMap = (GByte *) CPLMalloc(C_LEVELS * C_LEVELS * C_LEVELS 
                                       * sizeof(int));
    
    FindNearestColor( nColors, anPCT, pabyColorMap );

/* -------------------------------------------------------------------- */
/*      Setup various variables.                                        */
/* -------------------------------------------------------------------- */
    GByte	*pabyRed, *pabyGreen, *pabyBlue, *pabyIndex;
    int		*panError;

    pabyRed = (GByte *) VSIMalloc(nXSize);
    pabyGreen = (GByte *) VSIMalloc(nXSize);
    pabyBlue = (GByte *) VSIMalloc(nXSize);

    pabyIndex = (GByte *) VSIMalloc(nXSize);

    panError = (int *) VSICalloc(sizeof(int),(nXSize+2) * 3);
    
    if (pabyRed == NULL ||
        pabyGreen == NULL ||
        pabyBlue == NULL ||
        pabyIndex == NULL ||
        panError == NULL)
    {
        CPLError( CE_Failure, CPLE_OutOfMemory,
                  "VSIMalloc(): Out of memory in GDALDitherRGB2PCT" );
        err = CE_Failure;
        goto end_and_cleanup;
    }

/* ==================================================================== */
/*      Loop over all scanlines of data to process.                     */
/* ==================================================================== */
    int		iScanline;

    for( iScanline = 0; iScanline < nYSize; iScanline++ )
    {
        int	nLastRedError, nLastGreenError, nLastBlueError, i;

/* -------------------------------------------------------------------- */
/*      Report progress                                                 */
/* -------------------------------------------------------------------- */
        if( !pfnProgress( iScanline / (double) nYSize, NULL, pProgressArg ) )
        {
            CPLError( CE_Failure, CPLE_UserInterrupt, "User Terminated" );
            err = CE_Failure;
            goto end_and_cleanup;
        }

/* -------------------------------------------------------------------- */
/*      Read source data.                                               */
/* -------------------------------------------------------------------- */
        GDALRasterIO( hRed, GF_Read, 0, iScanline, nXSize, 1, 
                      pabyRed, nXSize, 1, GDT_Byte, 0, 0 );
        GDALRasterIO( hGreen, GF_Read, 0, iScanline, nXSize, 1, 
                      pabyGreen, nXSize, 1, GDT_Byte, 0, 0 );
        GDALRasterIO( hBlue, GF_Read, 0, iScanline, nXSize, 1, 
                      pabyBlue, nXSize, 1, GDT_Byte, 0, 0 );

/* -------------------------------------------------------------------- */
/*	Apply the error from the previous line to this one.		*/
/* -------------------------------------------------------------------- */
        for( i = 0; i < nXSize; i++ )
        {
            pabyRed[i] = (GByte)
                MAX(0,MIN(255,(pabyRed[i]   + panError[i*3+0+3])));
            pabyGreen[i] = (GByte)
                MAX(0,MIN(255,(pabyGreen[i] + panError[i*3+1+3])));
            pabyBlue[i] =  (GByte)
                MAX(0,MIN(255,(pabyBlue[i]  + panError[i*3+2+3])));
        }

        memset( panError, 0, sizeof(int) * (nXSize+2) * 3 );

/* -------------------------------------------------------------------- */
/*	Figure out the nearest color to the RGB value.			*/
/* -------------------------------------------------------------------- */
        nLastRedError = 0;
        nLastGreenError = 0;
        nLastBlueError = 0;

        for( i = 0; i < nXSize; i++ )
        {
            int		iIndex, nError, nSixth, iRed, iGreen, iBlue;
            int		nRedValue, nGreenValue, nBlueValue;

            nRedValue =   MAX(0,MIN(255, pabyRed[i]   + nLastRedError));
            nGreenValue = MAX(0,MIN(255, pabyGreen[i] + nLastGreenError));
            nBlueValue =  MAX(0,MIN(255, pabyBlue[i]  + nLastBlueError));

            iRed   = nRedValue *   C_LEVELS   / 256;
            iGreen = nGreenValue * C_LEVELS / 256;
            iBlue  = nBlueValue *  C_LEVELS  / 256;
            
            iIndex = pabyColorMap[iRed + iGreen * C_LEVELS 
                                 + iBlue * C_LEVELS * C_LEVELS];
	
            pabyIndex[i] = (GByte) iIndex;

/* -------------------------------------------------------------------- */
/*      Compute Red error, and carry it on to the next error line.      */
/* -------------------------------------------------------------------- */
            nError = nRedValue - anPCT[iIndex    ];
            nSixth = nError / 6;
            
            panError[i*3    ] += nSixth;
            panError[i*3+6  ] = nSixth;
            panError[i*3+3  ] += nError - 5 * nSixth;
            
            nLastRedError = 2 * nSixth;

/* -------------------------------------------------------------------- */
/*      Compute Green error, and carry it on to the next error line.    */
/* -------------------------------------------------------------------- */
            nError = nGreenValue - anPCT[iIndex+256];
            nSixth = nError / 6;

            panError[i*3  +1] += nSixth;
            panError[i*3+6+1] = nSixth;
            panError[i*3+3+1] += nError - 5 * nSixth;
            
            nLastGreenError = 2 * nSixth;

/* -------------------------------------------------------------------- */
/*      Compute Blue error, and carry it on to the next error line.     */
/* -------------------------------------------------------------------- */
            nError = nBlueValue - anPCT[iIndex+512];
            nSixth = nError / 6;
            
            panError[i*3  +2] += nSixth;
            panError[i*3+6+2] = nSixth;
            panError[i*3+3+2] += nError - 5 * nSixth;
            
            nLastBlueError = 2 * nSixth;
        }

/* -------------------------------------------------------------------- */
/*      Write results.                                                  */
/* -------------------------------------------------------------------- */
        GDALRasterIO( hTarget, GF_Write, 0, iScanline, nXSize, 1, 
                      pabyIndex, nXSize, 1, GDT_Byte, 0, 0 );
    }

    pfnProgress( 1.0, NULL, pProgressArg );

/* -------------------------------------------------------------------- */
/*      Cleanup                                                         */
/* -------------------------------------------------------------------- */
end_and_cleanup:
    CPLFree( pabyRed );
    CPLFree( pabyGreen );
    CPLFree( pabyBlue );
    CPLFree( pabyIndex );
    CPLFree( panError );
    CPLFree( pabyColorMap );

    return err;
}