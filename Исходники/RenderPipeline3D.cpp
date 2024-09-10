void IRenderPipeline3D::RasterizeTriangles()
{
	for (UINT tri = 0;tri < m_pIB_HomoSpace_Clipped->size() - 2;tri += 3)
	{
		UINT idx1 = m_pIB_HomoSpace_Clipped->at(tri);
		UINT idx2 = m_pIB_HomoSpace_Clipped->at(tri + 1);
		UINT idx3 = m_pIB_HomoSpace_Clipped->at(tri + 2);

		RasterizedFragment outVertex;

		//3 vertices of triangles ( in homogeneous space , [-1,1]x[-1,1])
		const auto& v1 = m_pVB_HomoSpace_Clipped->at(idx1);
		const auto& v2 = m_pVB_HomoSpace_Clipped->at(idx2);
		const auto& v3 = m_pVB_HomoSpace_Clipped->at(idx3);


		//convert to pixel space
		auto convertToPixelSpace = [&](const VertexShaderOutput_Vertex& v, VECTOR2& outV)
		{
			outV.x = float(mBufferWidth) * (v.posH.x + 1.0f) / 2.0f;
			outV.y = float(mBufferHeight) * (-v.posH.y + 1.0f) / 2.0f;
		};

		VECTOR2 v1_pixel, v2_pixel, v3_pixel;//pixel space
		convertToPixelSpace(v1, v1_pixel);
		convertToPixelSpace(v2, v2_pixel);
		convertToPixelSpace(v3, v3_pixel);

		//Basis Vector, used to compute the bilinear interpolation coord (s,t) of current pixel
		VECTOR2 basisVector1 = v2_pixel - v1_pixel;
		VECTOR2 basisVector2 = v3_pixel - v1_pixel;

		//a determinant to solve B-Lerp Coord equation
		//refer to doc for more math detail.
		float D = basisVector1.x*basisVector2.y - basisVector2.x*basisVector1.y;

		//in such circumstances,A B C lie on the same line.
		//------well , use THE SIGN OF D can implement BACKFACE CULLING--------
		if (D == 0)return;

		//scanline rasterization , generate pixels ROW-BY-ROW
		float minY = Clamp(min(min(v1_pixel.y, v2_pixel.y), v3_pixel.y), 0, float(mBufferHeight - 1));
		float maxY = Clamp(max(max(v1_pixel.y, v2_pixel.y), v3_pixel.y), 0, float(mBufferHeight - 1));

		//------------ horizontal scan line Intersection ------------
		for (int j = int(minY);j < int(maxY) + 1;++j)
		{
			BOOL intersectSucceeded = FALSE;
			UINT x1 = 0, x2 = 0;
			intersectSucceeded =
				mFunction_HorizontalIntersect(float(j), v1_pixel, v2_pixel, v3_pixel, x1, x2);

			//x1 = Clamp(x1, 0, mBufferWidth - 1);
			//x2 = Clamp(x2, 0, mBufferWidth - 1);

			//if intersect succeed, we will get X region [x1,x2] which indicate the range of pixels to fill
			if (intersectSucceeded == TRUE)
			{
				//-----------------FOR EACH RASTERIZED FRAGMENT----------------
				for (UINT i = x1;i <= x2;++i)
				{
					if (i >= mBufferWidth || j >= mBufferHeight)
					{
						break;
					}

					//pixel coord of current processing pixel
					VECTOR2 currentPoint_pixel = VECTOR2(float(i) + 0.5f, float(j) + 0.5f);

					//v1 (A) is the orginal point of basis, calculate the relative pixel coordinate
					VECTOR2 currentPointLocal_pixel = currentPoint_pixel - v1_pixel;

					//calculate the bilinear interpolation ratio coordinate (s,t)
					// (->localP) = s (->V1) + t(->V2)
					float s = (currentPointLocal_pixel.x*basisVector2.y - currentPointLocal_pixel.y*basisVector2.x) / D;
					float t = (basisVector1.x*currentPointLocal_pixel.y - basisVector1.y*currentPointLocal_pixel.x) / D;

					//depth correct interpolation ,then perform depth test
					float depth = 1.0f / (s / v2.posH.z + t / v3.posH.z + (1 - s - t) / v1.posH.z);
					if (mFunction_DepthTest(i, j, depth) == FALSE)goto label_nextPixel;

					//I will use normal bilinear interpolation to see the result first
					outVertex.pixelX = i;
					outVertex.pixelY = j;

					//perspective correct interpolation
					outVertex.color =
						(s / v2.posH.z* v2.color +
							t / v3.posH.z *v3.color +
							(1 - s - t) / v1.posH.z *v1.color)*depth;

					outVertex.texcoord =
						(s / v2.posH.z * v2.texcoord +
							t / v3.posH.z * v3.texcoord +
							(1 - s - t) / v1.posH.z * v1.texcoord)*depth;


					m_pVB_Rasterized->push_back(outVertex);
				label_nextPixel:;
				}//for each x (column)
			}//if horizontal intersect succeed

		}//for each y (row)
	}//for each homogeneous clip space triangle
}