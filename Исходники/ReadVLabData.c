void mexFunction( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[] )
{
	unsigned short wDataFormat;
	mxArray ** nTestType     = &plhs[0];
	mxArray ** szComment     = &plhs[1];
	mxArray ** nSpikeChannel = &plhs[2];
	mxArray ** aTestType     = &plhs[3];
	mxArray ** aExpParam     = &plhs[4];
	mxArray ** aBehavParam   = &plhs[5];
	mxArray ** aGraphParam   = &plhs[6];
	mxArray ** aTestSeries   = &plhs[7];
	mxArray ** aTrial        = &plhs[8];
	mxArray ** aFOREP        = &plhs[9];
	mxArray ** aResponseTime = &plhs[10];
	mxArray ** aTrialStatus  = &plhs[11];
	mxArray ** aDepth2Match  = &plhs[12];
	mxArray ** aCursorDepth  = &plhs[13];
	mxArray ** ucMajorChannel= &plhs[14];
	mxArray ** nCellNum      = &plhs[15];
	mxArray ** ucElectrodeNum= &plhs[16];
	mxArray ** nElectrodeDepth=&plhs[17];
    mxArray ** fSpikeShape           = &plhs[18];
    mxArray ** nSpikeShapeTimes      = &plhs[19];
    mxArray ** dSpikeShapeTimestamp  = &plhs[20];
    mxArray ** nSpikeShapeSampleRate = &plhs[21];

	int dims[2];
	FILE * fp;
	char * szFileName;
	size_t buflen = mxGetM(prhs[0]) * mxGetN(prhs[0]) + 1;
    unsigned long dwCount;
    int i, j;
    mxArray * array;

	szFileName = mxCalloc( buflen, sizeof(char) );
	mxGetString(prhs[0], szFileName, buflen);

	if( !(fp = fopen( szFileName, "rb" )) )
	{
		printf( "Can't open file!\n" );
		return;
	}
	setvbuf( fp, NULL, _IOFBF, 32000 );

	dims[0] = 1;
	dims[1] = 1;
	*nTestType = mxCreateNumericArray( 2, dims, mxINT32_CLASS, mxREAL );
	*nSpikeChannel = mxCreateNumericArray( 2, dims, mxINT32_CLASS, mxREAL );
	*ucMajorChannel = mxCreateNumericArray( 2, dims, mxUINT8_CLASS, mxREAL );
    *nSpikeShapeSampleRate = mxCreateNumericArray( 2, dims, mxINT32_CLASS, mxREAL );
	dims[1] = 8;
	*nCellNum = mxCreateNumericArray( 2, dims, mxINT16_CLASS, mxREAL );
	*ucElectrodeNum = mxCreateNumericArray( 2, dims, mxUINT8_CLASS, mxREAL );
	*nElectrodeDepth = mxCreateNumericArray( 2, dims, mxINT16_CLASS, mxREAL );

	fread( &wDataFormat, 2, 1, fp );
	if(wDataFormat > 10) {
	    printf("The format of underlining VLab file is newer than expected! !\n");
	    /*this piece of code actually reads data up to wDataFormat = 2*/
	    /*return;*/
	}
	fread( mxGetData(*nTestType), 4, 1, fp );
	if( wDataFormat == 0 || wDataFormat >= 2 )
		*szComment = ReadCString( fp );
	else
		*szComment = mxCreateString( mxCalloc( 1, sizeof(char) ) );
	fread( mxGetData(*nSpikeChannel), 4, 1, fp );
	if( wDataFormat > 0 )
	{
		fread( mxGetData(*ucMajorChannel), 1, 1, fp );
		fread( mxGetData(*nCellNum), 2, 8, fp );
		fread( mxGetData(*ucElectrodeNum), 1, 8, fp );
		fread( mxGetData(*nElectrodeDepth), 2, 8, fp );
	}

	*aTestType = ReadCStringArray( fp );

	ClassName = (char**)mxCalloc( 1, sizeof(char*) );
	sizeClassName = 0;

	*aExpParam = ReadCTypedPtrArray( fp );
	*aBehavParam = ReadCTypedPtrArray( fp );
	*aGraphParam = ReadCTypedPtrArray( fp );
	*aTestSeries = ReadCStringArray( fp );
	*aTrial = ReadCTypedPtrArray( fp );
	*aFOREP = ReadCArray( fp, mxINT32_CLASS );
	*aResponseTime = ReadCArray( fp, mxINT32_CLASS );
	*aTrialStatus = ReadCArray( fp, mxINT32_CLASS );
	*aDepth2Match = ReadCArray( fp, mxINT32_CLASS );
	*aCursorDepth = ReadCArray( fp, mxINT32_CLASS );

    /* spike shape */
    if (wDataFormat >= 10) {
        *fSpikeShape = mxCreateCellMatrix(8, 1);
        *nSpikeShapeTimes = mxCreateCellMatrix(8, 1);
        for (i = 0; i < 8; i ++) {
            dwCount = ReadCount( fp );
            array = mxCreateCellMatrix(dwCount, 1);
            for (j = 0; j < (int)dwCount; j ++)
                mxSetCell( array, j, ReadCArray(fp, mxSINGLE_CLASS));
            mxSetCell(*fSpikeShape, i, array);
            mxSetCell(*nSpikeShapeTimes, i, ReadCArray(fp, mxINT32_CLASS));
        }
        *dSpikeShapeTimestamp = ReadCArray(fp, mxUINT32_CLASS);
        dims[1] = 1;
        *nSpikeShapeSampleRate = mxCreateNumericArray( 2, dims, mxINT32_CLASS, mxREAL );
        fread(mxGetData(*nSpikeShapeSampleRate), 4, 1, fp );
    }
	else
	{
        *fSpikeShape = mxCreateCellMatrix(8, 1);
        *nSpikeShapeTimes = mxCreateCellMatrix(8, 1);
        dims[1] = 1;
        *dSpikeShapeTimestamp = mxCreateNumericArray(2, dims, mxUINT32_CLASS, mxREAL);
        *nSpikeShapeSampleRate = mxCreateNumericArray(2, dims, mxINT32_CLASS, mxREAL);
	}
	fclose( fp );

	mxFree( ClassName );
	ClassName = NULL;
}