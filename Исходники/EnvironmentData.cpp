RESLT CEnvironmentData::LoadFromTextFile(FILE *fd, BOOL NegateMag)
{
	// Floats must be used for scanf.
	float x=0,   y=0,  z=0,  v=0;	// x,y,z and data values (v) read in.
	float prevX=0, prevY=0, prevZ=0;	// previous x,y,z and values read in.
	TCHAR  buff[256];
	int	  sscanfConvCnt, sscanfRequiredConvCnt;
	double dVal;
	int lineCount = 0;


	_ASSERT(m_dimensionType == ENVDAT_UNINITIALIZED || m_dimensionType == ENVDAT_3D || m_dimensionType == ENVDAT_4D);
	if(m_dimensionType == ENVDAT_3Dx2V)
		return WRONGENVDATATYPE_ERROR; // This enviornmental data type isn't allowed (currently) to load or save from/to file.

	// Make sure this instance hasn't already loaded in data.
	if(m_dimensionType != ENVDAT_UNINITIALIZED)
		ClearData();

	//----------------------------------------------------------------------------------//
	// (1) Determine dimensionality of the file.
	//------------------------------------------//
	// Scan in the first line of the file to determine if it is 3 dimension (as in lat,
	// lon, depth) or 4 dimension (as in lat, lon, depth, termperature (at depth).
	// Rewind after scaning first line because will restart the scan from the top after
	// determining the dimensionality of the file.
	// Return error if not 3-D or 4-D data.
	fgets(buff, 256, fd);
	sscanfConvCnt = sscanf_s(buff, "%f %f %f %f",&v, &v, &v, &v);
	rewind(fd);
	sscanfRequiredConvCnt = sscanfConvCnt;
	if(sscanfConvCnt < 3 || sscanfConvCnt > 4)
	{
		ClearData();
		return FILEFORMAT_ERROR;
	}

	//----------------------------------------------------------------------------------//
	// (2) Determine the length of each dimension
	//------------------------------------------//
	// Read in the first line of the environmental data file.
	if(sscanfConvCnt == 3)
	{
		m_dimensionType = ENVDAT_3D; // The data occupies a plane (3-Dimensional)
		if(3 != fscanf_s(fd, "%f %f %f",&x, &y, &v))
		{
			ClearData();
			return FILEFORMAT_ERROR;
		}
		lineCount = 1;
		prevZ = z = 0;
	}
	else if(sscanfConvCnt == 4)
	{
		m_dimensionType = ENVDAT_4D; // The data occupies a volume (4-Dimensional)
		if(4 != fscanf_s(fd, "%f %f %f %f",&x, &y, &z, &v))
		{
			ClearData();
			return FILEFORMAT_ERROR;
		}
		lineCount = 1;
		prevZ = z-1;
	}

	// make previous values different from just-read-in values so they count properly in
	// the following while-loop.
	prevX = x - 1; prevY = y - 1;
	while(sscanfConvCnt == sscanfRequiredConvCnt)
	{
		if(x != prevX)
		{
			m_nXlen++;
			m_nYlen = m_nZlen = 0;
		}
		
		if(y != prevY)
		{
			m_nYlen++;
			m_nZlen = 0;
		}

		if(z != prevZ)
		{
			m_nZlen++;
		}

		if(x != prevX || y != prevY || z != prevZ)
			m_nVlen++;
		else
			m_nVlen = m_nVlen;

		prevX = x; prevY = y; prevZ = z;


		switch(m_dimensionType)
		{
		case ENVDAT_3D:
			x = y = z = 0;
			sscanfConvCnt = fscanf_s(fd, "%f %f %f",&x, &y, &v);
			lineCount++;
			break;
		case ENVDAT_4D:
			sscanfConvCnt = fscanf_s(fd, "%f %f %f %f",&x, &y, &z, &v);
			lineCount++;
			break;
		}
	}

	// Verify proper file format.  The length of each dimension mulitplied together must
	// equate to the length of the value vector (m_nVlen).
	switch(m_dimensionType)
	{
	case ENVDAT_3D:
		if(m_nXlen * m_nYlen != m_nVlen)
		{
			ClearData();
			return FILEFORMAT_ERROR;
		}
		break;
	case ENVDAT_4D:
		if(m_nXlen * m_nYlen * m_nZlen != m_nVlen)
		{
			ClearData();
			return FILEFORMAT_ERROR;
		}
		break;
	}


	//----------------------------------------------------------------------------------//
	// (3) Allocate Memory for the arrays that hold the data read in.
	//--------------------------------------------------------------//
	// The length of each dimension is now known so required memory can now be allocated.
	if(NULL == (m_fX = new double[m_nXlen]))
	{
		ClearData();
		return MEMALLOC_ERROR;
	}

	if(NULL == (m_fY = new double[m_nYlen]))
	{
		ClearData();
		return MEMALLOC_ERROR;
	}

	if(NULL == (m_fV1 = new double[m_nVlen]))
	{
		ClearData();
		return MEMALLOC_ERROR;
	}

	if(m_nZlen > 0 && (NULL == (m_fZ = new double[m_nZlen])))
	{
		ClearData();
		return MEMALLOC_ERROR;
	}

	//----------------------------------------------------------------------------------//
	// (4) Read the data from the file into the allocated buffers.
	//-----------------------------------------------------------//
	rewind(fd);
	m_nXlen = m_nYlen = m_nZlen = m_nVlen = 0;

	// Read in the first line to start the while loop below.
	switch(m_dimensionType)
	{
	case ENVDAT_3D:
		sscanfConvCnt = fscanf_s(fd, "%f %f %f",&x, &y, &v);
		prevZ = z = 0;
		m_minX = m_maxX = x;
		m_minY = m_maxY = y;
		m_minZ = m_maxZ = 0;
		m_minV1 = m_maxV1 = v;
		break;

	case ENVDAT_4D:
		sscanfConvCnt = fscanf_s(fd, "%f %f %f %f",&x, &y, &z, &v);
		prevZ = z - 1;
		m_minX = m_maxX = x;
		m_minY = m_maxY = y;
		m_minZ = m_maxZ = z;
		m_minV1 = m_maxV1 = v;
		break;
	}

	// The following loop continues until the last line.  Before entering the loop, make
	// previous  (prevX, prevY, and prevZ) different from just-read-in values so they count
	// properly.
	prevX = x - 1; prevY = y - 1;
	while(sscanfConvCnt == sscanfRequiredConvCnt)
	{
		if(x != prevX)
		{
			m_fX[m_nXlen++] = x;
			m_nYlen = m_nZlen = 0;

			if(x < m_minX)
				m_minX = x;
			else if(x > m_maxX)
				m_maxX = x;
		}
		
		if(y != prevY)
		{
			m_fY[m_nYlen++] = y;
			m_nZlen = 0;

			if(y < m_minY)
				m_minY = y;
			else if(y > m_maxY)
				m_maxY = y;
		}

		if(z != prevZ)
		{
			m_fZ[m_nZlen++] = z;

			if(z < m_minZ)
				m_minZ = z;
			else if(z > m_maxZ)
				m_maxZ = z;

		}

		if(x != prevX || y != prevY || z != prevZ)
		{
			if(NegateMag == FALSE)
				m_fV1[m_nVlen] = v;
			else
				m_fV1[m_nVlen] = -v;

			m_nVlen++;

			if(v < m_minV1)
				m_minV1 = v;
			else if(v > m_maxV1)
				m_maxV1 = v;

		}

		prevX = x; prevY = y; prevZ = z;

		if(m_dimensionType == ENVDAT_3D)
			sscanfConvCnt = fscanf_s(fd, "%f %f %f", &x, &y, &v);
		else
			sscanfConvCnt = fscanf_s(fd, "%f %f %f %f", &x, &y, &z, &v);

	}

	if(NegateMag == TRUE)
	{
		dVal = m_maxV1;
		m_maxV1 = m_minV1;
		m_minV1 = dVal;

		m_minV1 = -m_minV1;
		m_maxV1 = -m_maxV1;

	}
	else
	{
		m_maxV1 = m_maxV1;
		m_minV1 = m_minV1;
	}

//	GetSlopeHeadingFromCrossProduct();
#if 0 // debug
	ENVMINMAX m = GetExtremes();
	CalculateSurfaceAreaAtPlane(m.xMin, m.yMin, m.xMax, m.yMax, -2.0);
#endif
	m_bathyConstantSet = FALSE;

	return OK;
}