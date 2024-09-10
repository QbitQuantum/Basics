//-----------------------------------------------------------------------------------------
// Rasterize the occludee AABB and depth test it against the CPU rasterized depth buffer
// If any of the rasterized AABB pixels passes the depth test exit early and mark the occludee
// as visible. If all rasterized AABB pixels are occluded then the occludee is culled
//-----------------------------------------------------------------------------------------
bool TransformedAABBoxAVX::RasterizeAndDepthTestAABBox(UINT *pRenderTargetPixels, const __m128 pXformedPos[], UINT idx)
{
	// Set DAZ and FZ MXCSR bits to flush denormals to zero (i.e., make it faster)
	// Denormal are zero (DAZ) is bit 6 and Flush to zero (FZ) is bit 15. 
	// so to enable the two to have to set bits 6 and 15 which 1000 0000 0100 0000 = 0x8040
	_mm_setcsr( _mm_getcsr() | 0x8040 );

	__m256i colOffset = _mm256_setr_epi32(0, 1, 2, 3, 0, 1, 2, 3);
	__m256i rowOffset = _mm256_setr_epi32(0, 0, 0, 0, 1, 1, 1, 1);
	float* pDepthBuffer = (float*)pRenderTargetPixels;
	
	// Rasterize the AABB triangles 4 at a time
	for(UINT i = 0; i < AABB_TRIANGLES; i += SSE)
	{
		vFloat4 xformedPos[3];
		Gather(xformedPos, i, pXformedPos, idx);

		// use fixed-point only for X and Y.  Avoid work for Z and W.
        __m128i fxPtX[3], fxPtY[3];
		for(int m = 0; m < 3; m++)
		{
			fxPtX[m] = _mm_cvtps_epi32(xformedPos[m].X);
			fxPtY[m] = _mm_cvtps_epi32(xformedPos[m].Y);
		}

		// Fab(x, y) =     Ax       +       By     +      C              = 0
		// Fab(x, y) = (ya - yb)x   +   (xb - xa)y + (xa * yb - xb * ya) = 0
		// Compute A = (ya - yb) for the 3 line segments that make up each triangle
		__m128i A0 = _mm_sub_epi32(fxPtY[1], fxPtY[2]);
		__m128i A1 = _mm_sub_epi32(fxPtY[2], fxPtY[0]);
		__m128i A2 = _mm_sub_epi32(fxPtY[0], fxPtY[1]);

		// Compute B = (xb - xa) for the 3 line segments that make up each triangle
		__m128i B0 = _mm_sub_epi32(fxPtX[2], fxPtX[1]);
		__m128i B1 = _mm_sub_epi32(fxPtX[0], fxPtX[2]);
		__m128i B2 = _mm_sub_epi32(fxPtX[1], fxPtX[0]);

		// Compute C = (xa * yb - xb * ya) for the 3 line segments that make up each triangle
		__m128i C0 = _mm_sub_epi32(_mm_mullo_epi32(fxPtX[1], fxPtY[2]), _mm_mullo_epi32(fxPtX[2], fxPtY[1]));
		__m128i C1 = _mm_sub_epi32(_mm_mullo_epi32(fxPtX[2], fxPtY[0]), _mm_mullo_epi32(fxPtX[0], fxPtY[2]));
		__m128i C2 = _mm_sub_epi32(_mm_mullo_epi32(fxPtX[0], fxPtY[1]), _mm_mullo_epi32(fxPtX[1], fxPtY[0]));

		// Compute triangle area
		__m128i triArea = _mm_mullo_epi32(B2, A1);
		triArea = _mm_sub_epi32(triArea, _mm_mullo_epi32(B1, A2));
		__m128 oneOverTriArea = _mm_rcp_ps(_mm_cvtepi32_ps(triArea));

		__m128 Z[3];
		Z[0] = xformedPos[0].Z;
		Z[1] = _mm_mul_ps(_mm_sub_ps(xformedPos[1].Z, Z[0]), oneOverTriArea);
		Z[2] = _mm_mul_ps(_mm_sub_ps(xformedPos[2].Z, Z[0]), oneOverTriArea);
		
		// Use bounding box traversal strategy to determine which pixels to rasterize 
		//__m128i startX = _mm_and_si128(HelperSSE::Max(HelperSSE::Min(HelperSSE::Min(fxPtX[0], fxPtX[1]), fxPtX[2]), _mm_set1_epi32(0)), _mm_set1_epi32(~1));
		__m128i startX = _mm_and_si128(HelperSSE::Max(HelperSSE::Min(HelperSSE::Min(fxPtX[0], fxPtX[1]), fxPtX[2]), _mm_set1_epi32(0)), _mm_set1_epi32(~3));
		__m128i endX = HelperSSE::Min(HelperSSE::Max(HelperSSE::Max(fxPtX[0], fxPtX[1]), fxPtX[2]), _mm_set1_epi32(SCREENW - 1));

		__m128i startY = _mm_and_si128(HelperSSE::Max(HelperSSE::Min(HelperSSE::Min(fxPtY[0], fxPtY[1]), fxPtY[2]), _mm_set1_epi32(0)), _mm_set1_epi32(~1));
		__m128i endY = HelperSSE::Min(HelperSSE::Max(HelperSSE::Max(fxPtY[0], fxPtY[1]), fxPtY[2]), _mm_set1_epi32(SCREENH - 1));

		// Now we have 4 triangles set up.  Rasterize them each individually.
        for(int lane=0; lane < SSE; lane++)
        {
			// Skip triangle if area is zero 
			if(triArea.m128i_i32[lane] <= 0)
			{
				continue;
			}

			// Extract this triangle's properties from the SIMD versions
			__m256 zz[3];
			for (int vv = 0; vv < 3; vv++)
			{
				zz[vv] = _mm256_set1_ps(Z[vv].m128_f32[lane]);
			}

			int startXx = startX.m128i_i32[lane];
			int endXx = endX.m128i_i32[lane];
			int startYy = startY.m128i_i32[lane];
			int endYy = endY.m128i_i32[lane];

			__m256i aa0 = _mm256_set1_epi32(A0.m128i_i32[lane]);
			__m256i aa1 = _mm256_set1_epi32(A1.m128i_i32[lane]);
			__m256i aa2 = _mm256_set1_epi32(A2.m128i_i32[lane]);

			__m256i bb0 = _mm256_set1_epi32(B0.m128i_i32[lane]);
			__m256i bb1 = _mm256_set1_epi32(B1.m128i_i32[lane]);
			__m256i bb2 = _mm256_set1_epi32(B2.m128i_i32[lane]);

			__m256i aa0Inc = _mm256_slli_epi32(aa0, 2);
			__m256i aa1Inc = _mm256_slli_epi32(aa1, 2);
			__m256i aa2Inc = _mm256_slli_epi32(aa2, 2);

			__m256i bb0Inc = _mm256_slli_epi32(bb0, 1);
			__m256i bb1Inc = _mm256_slli_epi32(bb1, 1);
			__m256i bb2Inc = _mm256_slli_epi32(bb2, 1);

			__m256i row, col;

			// Traverse pixels in 2x4 blocks and store 2x4 pixel quad depths contiguously in memory ==> 2*X
			// This method provides better performance
			int	rowIdx = (startYy * SCREENW + 2 * startXx);

			col = _mm256_add_epi32(colOffset, _mm256_set1_epi32(startXx));
			__m256i aa0Col = _mm256_mullo_epi32(aa0, col);
			__m256i aa1Col = _mm256_mullo_epi32(aa1, col);
			__m256i aa2Col = _mm256_mullo_epi32(aa2, col);

			row = _mm256_add_epi32(rowOffset, _mm256_set1_epi32(startYy));
			__m256i bb0Row = _mm256_add_epi32(_mm256_mullo_epi32(bb0, row), _mm256_set1_epi32(C0.m128i_i32[lane]));
			__m256i bb1Row = _mm256_add_epi32(_mm256_mullo_epi32(bb1, row), _mm256_set1_epi32(C1.m128i_i32[lane]));
			__m256i bb2Row = _mm256_add_epi32(_mm256_mullo_epi32(bb2, row), _mm256_set1_epi32(C2.m128i_i32[lane]));

			__m256i sum0Row = _mm256_add_epi32(aa0Col, bb0Row);
			__m256i sum1Row = _mm256_add_epi32(aa1Col, bb1Row);
			__m256i sum2Row = _mm256_add_epi32(aa2Col, bb2Row);

			__m256 zx = _mm256_mul_ps(_mm256_cvtepi32_ps(aa1Inc), zz[1]);
			zx = _mm256_add_ps(zx, _mm256_mul_ps(_mm256_cvtepi32_ps(aa2Inc), zz[2]));

			// Incrementally compute Fab(x, y) for all the pixels inside the bounding box formed by (startX, endX) and (startY, endY)
			for (int r = startYy; r < endYy; r += 2,
				rowIdx += 2 * SCREENW,
				sum0Row = _mm256_add_epi32(sum0Row, bb0Inc),
				sum1Row = _mm256_add_epi32(sum1Row, bb1Inc),
				sum2Row = _mm256_add_epi32(sum2Row, bb2Inc))
			{
				// Compute barycentric coordinates 
				int index = rowIdx;
				__m256i alpha = sum0Row;
				__m256i beta = sum1Row;
				__m256i gama = sum2Row;

				//Compute barycentric-interpolated depth
				__m256 depth = zz[0];
				depth = _mm256_add_ps(depth, _mm256_mul_ps(_mm256_cvtepi32_ps(beta), zz[1]));
				depth = _mm256_add_ps(depth, _mm256_mul_ps(_mm256_cvtepi32_ps(gama), zz[2]));
				__m256i anyOut = _mm256_setzero_si256();

				for (int c = startXx; c < endXx; c += 4,
					index += 8,
					alpha = _mm256_add_epi32(alpha, aa0Inc),
					beta = _mm256_add_epi32(beta, aa1Inc),
					gama = _mm256_add_epi32(gama, aa2Inc),
					depth = _mm256_add_ps(depth, zx))
				{
					//Test Pixel inside triangle
					__m256i mask = _mm256_or_si256(_mm256_or_si256(alpha, beta), gama);

					__m256 previousDepthValue = _mm256_loadu_ps(&pDepthBuffer[index]);
					__m256 depthMask = _mm256_cmp_ps(depth, previousDepthValue, 0x1D);
					__m256i finalMask = _mm256_andnot_si256(mask, _mm256_castps_si256(depthMask));
					anyOut = _mm256_or_si256(anyOut, finalMask);
				}//for each column	

				if (!_mm256_testz_si256(anyOut, _mm256_set1_epi32(0x80000000)))
				{
					return true; //early exit
				}
			}// for each row
		}// for each triangle
	}// for each set of SIMD# triangles

	return false;
}