void TreeSegGeo::constructGeometryData(Quaternion orient, bool topPlane, bool bottomPlane)
{
	int numVerts = mSegmentsW * (mSegmentsH + 1) + 2;

	// positionData
	mGeoData.posData.push_back(Vector3::Zero);
	mGeoData.posData.push_back(Vector3(0, mLength, 0));

	float heightDelta = mLength / mSegmentsH;
	float deltaTheta = 2*PI / mSegmentsW;

	for(int i = 0; i <= mSegmentsH; ++i)
	{
		float circleHeight = i * heightDelta;
		float circleRadius = mRadius[i];
		for(int j = 0; j < mSegmentsW; ++j)
		{
			float x = circleRadius * cos(j*deltaTheta);
			float z = circleRadius * sin(j*deltaTheta);

			Vector3 vertPos(x, circleHeight, z);
			if(i == 0)
				vertPos = vertPos * orient.Conjugate();

			mGeoData.posData.push_back(vertPos);
		}
	}

	// verts
	for(size_t i = 0; i < mGeoData.posData.size(); ++i)
	{
		Vert vert(i);
		mGeoData.verts.push_back(vert);
	}

	// triangles
	if(bottomPlane)
	{
		for(int i = 0; i < mSegmentsW; ++i)		// 底圆面
		{
			// 顶点索引为2 ~ sw+1
			Triangle triangle(0, 2+i, 2 + (i + 1) % mSegmentsW);
			mGeoData.tris.push_back(triangle);
		}
	}

	if(topPlane)
	{
		for(int i = 0; i < mSegmentsW; ++i)		// 顶圆面
		{
			// 顶点索引为sw*sh + 2 ~ sw*(sh + 1) + 1
			Triangle triangle(1, mSegmentsW*mSegmentsH + 2 + (i + 1) % mSegmentsW, mSegmentsW*mSegmentsH + 2 + i);
			mGeoData.tris.push_back(triangle);
		}
	}

	for(int i = 0; i < mSegmentsH; ++i)		// 柱面
	{
		for(int j = 0; j < mSegmentsW; ++j)		
		{
			Triangle tri1;
			Triangle tri2;

			tri1.vertexIndex[0] = mSegmentsW * i + j + 2;
			tri1.vertexIndex[1] = mSegmentsW * (i + 1) + j + 2;
			tri1.vertexIndex[2] = mSegmentsW * i + (j + 1)%mSegmentsW + 2;

			tri2.vertexIndex[0] = mSegmentsW * (i + 1) + j + 2;
			tri2.vertexIndex[1] = mSegmentsW * (i + 1) + (j + 1)%mSegmentsW + 2;
			tri2.vertexIndex[2] = mSegmentsW * i + (j + 1)%mSegmentsW + 2;

			_Assert(tri1.vertexIndex[0] < mSegmentsW * (mSegmentsH + 1) + 2);
			_Assert(tri1.vertexIndex[1] < mSegmentsW * (mSegmentsH + 1) + 2);
			_Assert(tri1.vertexIndex[2] < mSegmentsW * (mSegmentsH + 1) + 2);

			_Assert(tri2.vertexIndex[0] < mSegmentsW * (mSegmentsH + 1) + 2);
			_Assert(tri2.vertexIndex[1] < mSegmentsW * (mSegmentsH + 1) + 2);
			_Assert(tri2.vertexIndex[2] < mSegmentsW * (mSegmentsH + 1) + 2);

			mGeoData.tris.push_back(tri1);
			mGeoData.tris.push_back(tri2);
		}
	}
}