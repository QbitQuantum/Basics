//-------------------------------------------------------------------------------
// For each tile go through all the bins and process all the triangles in it.
// Rasterize each triangle to the CPU depth buffer. 
//-------------------------------------------------------------------------------
void DepthBufferRasterizerSSEST::RasterizeBinnedTrianglesToDepthBuffer(UINT tileId, UINT idx)
{
	// Set DAZ and FZ MXCSR bits to flush denormals to zero (i.e., make it faster)
	_mm_setcsr( _mm_getcsr() | 0x8040 );

	__m128i colOffset = _mm_setr_epi32(0, 1, 0, 1);
	__m128i rowOffset = _mm_setr_epi32(0, 0, 1, 1);

	__m128i fxptZero = _mm_setzero_si128();
	float* pDepthBuffer = (float*)mpRenderTargetPixels[idx]; 

	// Based on TaskId determine which tile to process
	UINT screenWidthInTiles = SCREENW/TILE_WIDTH_IN_PIXELS;
    UINT tileX = tileId % screenWidthInTiles;
    UINT tileY = tileId / screenWidthInTiles;

    int tileStartX = tileX * TILE_WIDTH_IN_PIXELS;
	int tileEndX   = tileStartX + TILE_WIDTH_IN_PIXELS - 1;
	
	int tileStartY = tileY * TILE_HEIGHT_IN_PIXELS;
	int tileEndY   = tileStartY + TILE_HEIGHT_IN_PIXELS - 1;

	ClearDepthTile(tileStartX, tileStartY, tileEndX+1, tileEndY+1, idx);

	UINT bin = 0;
	UINT binIndex = 0;
	UINT offset1 = YOFFSET1_ST * tileY + XOFFSET1_ST * tileX;
	UINT offset2 = YOFFSET2_ST * tileY + XOFFSET2_ST * tileX;
	UINT numTrisInBin = mpNumTrisInBin[idx][offset1 + bin];

	__m128 gatherBuf[4][3];
	bool done = false;
	bool allBinsEmpty = true;
	mNumRasterizedTris[idx][tileId] = numTrisInBin;
	while(!done)
	{
		// Loop through all the bins and process 4 binned traingles at a time
		UINT ii;
		int numSimdTris = 0;
		for(ii = 0; ii < SSE; ii++)
		{
			while(numTrisInBin <= 0)
			{
				 // This bin is empty.  Move to next bin.
				if(++bin >= 1)
				{
					break;
				}
				numTrisInBin = mpNumTrisInBin[idx][offset1 + bin];
				mNumRasterizedTris[idx][tileId] += numTrisInBin;
				binIndex = 0;
			}
			if(!numTrisInBin)
			{
				break; // No more tris in the bins
			}
			USHORT modelId = mpBinModel[idx][offset2 + bin * MAX_TRIS_IN_BIN_ST + binIndex];
			USHORT meshId = mpBinMesh[idx][offset2 + bin * MAX_TRIS_IN_BIN_ST + binIndex];
			UINT triIdx = mpBin[idx][offset2 + bin * MAX_TRIS_IN_BIN_ST + binIndex];
			mpTransformedModels1[modelId].Gather(gatherBuf[ii], meshId, triIdx, idx);
			allBinsEmpty = false;
			numSimdTris++; 

			++binIndex;
			--numTrisInBin;
		}
		done = bin >= NUM_XFORMVERTS_TASKS;
		
		if(allBinsEmpty)
		{
			return;
		}

		// use fixed-point only for X and Y.  Avoid work for Z and W.
        __m128i fxPtX[3], fxPtY[3];
		__m128 Z[3];
		for(int i = 0; i < 3; i++)
		{
			__m128 v0 = gatherBuf[0][i];
			__m128 v1 = gatherBuf[1][i];
			__m128 v2 = gatherBuf[2][i];
			__m128 v3 = gatherBuf[3][i];

  			// transpose into SoA layout
			_MM_TRANSPOSE4_PS(v0, v1, v2, v3);
			fxPtX[i] = _mm_cvtps_epi32(v0);
			fxPtY[i] = _mm_cvtps_epi32(v1);
			Z[i] = v2;
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
		__m128 oneOverTriArea = _mm_div_ps(_mm_set1_ps(1.0f), _mm_cvtepi32_ps(triArea));

		Z[1] = _mm_mul_ps(_mm_sub_ps(Z[1], Z[0]), oneOverTriArea);
		Z[2] = _mm_mul_ps(_mm_sub_ps(Z[2], Z[0]), oneOverTriArea);

		// Use bounding box traversal strategy to determine which pixels to rasterize 
		__m128i startX = _mm_and_si128(Max(Min(Min(fxPtX[0], fxPtX[1]), fxPtX[2]), _mm_set1_epi32(tileStartX)), _mm_set1_epi32(0xFFFFFFFE));
		__m128i endX   = Min(_mm_add_epi32(Max(Max(fxPtX[0], fxPtX[1]), fxPtX[2]), _mm_set1_epi32(1)), _mm_set1_epi32(tileEndX));

		__m128i startY = _mm_and_si128(Max(Min(Min(fxPtY[0], fxPtY[1]), fxPtY[2]), _mm_set1_epi32(tileStartY)), _mm_set1_epi32(0xFFFFFFFE));
		__m128i endY   = Min(_mm_add_epi32(Max(Max(fxPtY[0], fxPtY[1]), fxPtY[2]), _mm_set1_epi32(1)), _mm_set1_epi32(tileEndY));

		// Now we have 4 triangles set up.  Rasterize them each individually.
        for(int lane=0; lane < numSimdTris; lane++)
        {
			// Extract this triangle's properties from the SIMD versions
            __m128 zz[3];
			for(int vv = 0; vv < 3; vv++)
			{
				zz[vv] = _mm_set1_ps(Z[vv].m128_f32[lane]);
			}
									
			int startXx = startX.m128i_i32[lane];
			int endXx	= endX.m128i_i32[lane];
			int startYy = startY.m128i_i32[lane];
			int endYy	= endY.m128i_i32[lane];
		
			__m128i aa0 = _mm_set1_epi32(A0.m128i_i32[lane]);
			__m128i aa1 = _mm_set1_epi32(A1.m128i_i32[lane]);
			__m128i aa2 = _mm_set1_epi32(A2.m128i_i32[lane]);

			__m128i bb0 = _mm_set1_epi32(B0.m128i_i32[lane]);
			__m128i bb1 = _mm_set1_epi32(B1.m128i_i32[lane]);
			__m128i bb2 = _mm_set1_epi32(B2.m128i_i32[lane]);

			__m128i aa0Inc = _mm_slli_epi32(aa0, 1);
			__m128i aa1Inc = _mm_slli_epi32(aa1, 1);
			__m128i aa2Inc = _mm_slli_epi32(aa2, 1);

			__m128i row, col;

			// Tranverse pixels in 2x2 blocks and store 2x2 pixel quad depths contiguously in memory ==> 2*X
			// This method provides better perfromance
			int rowIdx = (startYy * SCREENW + 2 * startXx);

			col = _mm_add_epi32(colOffset, _mm_set1_epi32(startXx));
			__m128i aa0Col = _mm_mullo_epi32(aa0, col);
			__m128i aa1Col = _mm_mullo_epi32(aa1, col);
			__m128i aa2Col = _mm_mullo_epi32(aa2, col);

			row = _mm_add_epi32(rowOffset, _mm_set1_epi32(startYy));
			__m128i bb0Row = _mm_add_epi32(_mm_mullo_epi32(bb0, row), _mm_set1_epi32(C0.m128i_i32[lane]));
			__m128i bb1Row = _mm_add_epi32(_mm_mullo_epi32(bb1, row), _mm_set1_epi32(C1.m128i_i32[lane]));
			__m128i bb2Row = _mm_add_epi32(_mm_mullo_epi32(bb2, row), _mm_set1_epi32(C2.m128i_i32[lane]));

			__m128i sum0Row = _mm_add_epi32(aa0Col, bb0Row);
			__m128i sum1Row = _mm_add_epi32(aa1Col, bb1Row);
			__m128i sum2Row = _mm_add_epi32(aa2Col, bb2Row);

			__m128i bb0Inc = _mm_slli_epi32(bb0, 1);
			__m128i bb1Inc = _mm_slli_epi32(bb1, 1);
			__m128i bb2Inc = _mm_slli_epi32(bb2, 1);

			__m128 zx = _mm_mul_ps(_mm_cvtepi32_ps(aa1Inc), zz[1]);
			zx = _mm_add_ps(zx, _mm_mul_ps(_mm_cvtepi32_ps(aa2Inc), zz[2]));

			// Incrementally compute Fab(x, y) for all the pixels inside the bounding box formed by (startX, endX) and (startY, endY)
			for(int r = startYy; r < endYy; r += 2,
											rowIdx += 2 * SCREENW,
											sum0Row = _mm_add_epi32(sum0Row, bb0Inc),
											sum1Row = _mm_add_epi32(sum1Row, bb1Inc),
											sum2Row = _mm_add_epi32(sum2Row, bb2Inc))
			{
				// Compute barycentric coordinates 
				int index = rowIdx;
				__m128i alpha = sum0Row;
				__m128i beta = sum1Row;
				__m128i gama = sum2Row;

				//Compute barycentric-interpolated depth
				__m128 depth = zz[0];
				depth = _mm_add_ps(depth, _mm_mul_ps(_mm_cvtepi32_ps(beta), zz[1]));
				depth = _mm_add_ps(depth, _mm_mul_ps(_mm_cvtepi32_ps(gama), zz[2]));

				for(int c = startXx; c < endXx; c += 2,
												index += 4,
												alpha = _mm_add_epi32(alpha, aa0Inc),
												beta  = _mm_add_epi32(beta, aa1Inc),
												gama  = _mm_add_epi32(gama, aa2Inc),
												depth = _mm_add_ps(depth, zx))
				{
					//Test Pixel inside triangle
					__m128i mask = _mm_or_si128(_mm_or_si128(alpha, beta), gama);
					
					__m128 previousDepthValue = _mm_load_ps(&pDepthBuffer[index]);
					__m128 mergedDepth = _mm_max_ps(depth, previousDepthValue);
					__m128 finalDepth = _mm_blendv_ps(mergedDepth, previousDepthValue, _mm_castsi128_ps(mask));
					_mm_store_ps(&pDepthBuffer[index], finalDepth);
				}//for each column											
			}// for each row
		}// for each triangle
	}// for each set of SIMD# triangles
}