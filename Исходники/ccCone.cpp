bool ccCone::buildUp()
{
	if (m_drawPrecision < MIN_DRAWING_PRECISION)
		return false;

	//invalid dimensions?
	if (m_height < ZERO_TOLERANCE || m_bottomRadius + m_topRadius < ZERO_TOLERANCE)
		return false;

	//topology
	bool singlePointBottom = (m_bottomRadius < ZERO_TOLERANCE);
	bool singlePointTop = (m_topRadius < ZERO_TOLERANCE);
	assert(!singlePointBottom || !singlePointTop);

	unsigned steps = m_drawPrecision;

	//vertices
	unsigned vertCount = 2;
	if (!singlePointBottom)
		vertCount += steps;
	if (!singlePointTop)
		vertCount += steps;
	//normals
	unsigned faceNormCounts = steps+2;
	//vertices
	unsigned facesCount = steps;
	if (!singlePointBottom)
		facesCount += steps;
	if (!singlePointTop)
		facesCount += steps;
	if (!singlePointBottom && !singlePointTop)
		facesCount += steps;

	//allocate (& clear) structures
	if (!init(vertCount,false,facesCount,faceNormCounts))
	{
		ccLog::Error("[ccCone::buildUp] Not enough memory");
		return false;
	}

	ccPointCloud* verts = vertices();
	assert(verts);
	assert(m_triNormals);

	//2 first points: centers of the top & bottom surfaces
	CCVector3 bottomCenter = CCVector3(m_xOff,m_yOff,-m_height)/2;
	CCVector3 topCenter = CCVector3(-m_xOff,-m_yOff,m_height)/2;
	{
		//bottom center
		verts->addPoint(bottomCenter);
		CompressedNormType nIndex = ccNormalVectors::GetNormIndex(CCVector3(0,0,-1).u);
		m_triNormals->addElement(nIndex);
		//top center
		verts->addPoint(topCenter);
		nIndex = ccNormalVectors::GetNormIndex(CCVector3(0,0,1).u);
		m_triNormals->addElement(nIndex);
	}
	
	//then, angular sweep for top and/or bottom surfaces
	{
		PointCoordinateType angle_rad_step = static_cast<PointCoordinateType>(2.0*M_PI)/static_cast<PointCoordinateType>(steps);
		//bottom surface
		if (!singlePointBottom)
		{
			for (unsigned i=0; i<steps; ++i)
			{
				CCVector3 P(bottomCenter.x + cos(angle_rad_step*i)*m_bottomRadius,
							bottomCenter.y + sin(angle_rad_step*i)*m_bottomRadius,
							bottomCenter.z);
				verts->addPoint(P);
			}
		}
		//top surface
		if (!singlePointTop)
		{
			for (unsigned i=0; i<steps; ++i)
			{
				CCVector3 P(topCenter.x + cos(angle_rad_step*i)*m_topRadius,
							topCenter.y + sin(angle_rad_step*i)*m_topRadius,
							topCenter.z);
				verts->addPoint(P);
			}
		}
		//side normals
		{
			for (unsigned i=0; i<steps; ++i)
			{
				//slope
				CCVector3 u(-sin(angle_rad_step*i),cos(angle_rad_step*i),0);
				CCVector3 v(bottomCenter.x-topCenter.x + u.y*(m_bottomRadius-m_topRadius),
							bottomCenter.y-topCenter.y - u.x*(m_bottomRadius-m_topRadius),
							bottomCenter.z-topCenter.z);
				CCVector3 N = v.cross(u);
				N.normalize();

				CompressedNormType nIndex = ccNormalVectors::GetNormIndex(N.u);
				m_triNormals->addElement(nIndex);
			}
		}
	}
	
	//mesh faces
	{
		assert(m_triVertIndexes);

		unsigned bottomIndex = 2;
		unsigned topIndex = 2+(singlePointBottom ? 0 : steps);

		//bottom surface
		if (!singlePointBottom)
		{
			for (unsigned i=0;i<steps;++i)
			{
				addTriangle(0,bottomIndex+(i+1)%steps,bottomIndex+i);
				addTriangleNormalIndexes(0,0,0);
			}
		}
		//top surface
		if (!singlePointTop)
		{
			for (unsigned i=0;i<steps;++i)
			{
				addTriangle(1,topIndex+i,topIndex+(i+1)%steps);
				addTriangleNormalIndexes(1,1,1);
			}
		}

		if (!singlePointBottom && !singlePointTop)
		{
			for (unsigned i=0;i<steps;++i)
			{
				unsigned iNext = (i+1)%steps;
				addTriangle(bottomIndex+i,bottomIndex+iNext,topIndex+i);
				addTriangleNormalIndexes(2+i,2+iNext,2+i);
				addTriangle(topIndex+i,bottomIndex+iNext,topIndex+iNext);
				addTriangleNormalIndexes(2+i,2+iNext,2+iNext);
			}
		}
		else if (!singlePointTop)
		{
			for (unsigned i=0;i<steps;++i)
			{
				unsigned iNext = (i+1)%steps;
				addTriangle(topIndex+i,0,topIndex+iNext);
				addTriangleNormalIndexes(2+i,2+iNext,2+iNext); //TODO: middle normal should be halfbetween?!
			}
		}
		else //if (!singlePointBottom)
		{
			for (unsigned i=0;i<steps;++i)
			{
				unsigned iNext = (i+1)%steps;
				addTriangle(bottomIndex+i,bottomIndex+iNext,1);
				addTriangleNormalIndexes(2+i,2+iNext,2+i); //TODO: last normal should be halfbetween?!
			}
		}
	}

	notifyGeometryUpdate();
	showTriNorms(true);

	return true;
}