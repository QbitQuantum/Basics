// returns whether the shape was drawn
eBool eLSystem::drawShapes(eMesh& destMesh, tDrawState& state, const tTurtleState& turtle0, const tTurtleState& turtle1, eF32 shapeLen, eF32 stexY0, eF32 stexY1, eBool forceDraw, eU32 numParts) {
    eF32 partLen = eLerp(this->m_sizePar * (eF32)numParts, 0.0001f, detail);
//	eF32 partLen = eLerp(eF32_MAX, 0.0001f, detail);
	if(partLen <= 0.0f)
		partLen = eALMOST_ZERO;
	eF32 numToDrawF = (eF32)shapeLen / partLen;
	if(!forceDraw) {
		if(numToDrawF <= 1.0f)
			return false;
	}
	eU32 numDraw = eCeil(eClamp(1.0f, numToDrawF, (eF32)m_gen_rings)); 


	eU32		numFaces = numDraw * m_gen_edges * 2;
	eU32		faceNr = 0;

    ePROFILER_ZONE("L-System - Draw Shapes");

    __declspec(align(16)) const eVector3  control0 = turtle0.position;
	__declspec(align(16)) const eVector3  control1 = control0   + turtle0.rotation.getVector(2) * 0.333333f * shapeLen;
    __declspec(align(16)) const eVector3  control3 = turtle1.position;
	__declspec(align(16)) const eVector3  control2 = control3   - turtle1.rotation.getVector(2) * 0.333333f * shapeLen;

    eF32 rscale0 = turtle0.size * turtle0.width;
	eF32 rscale1 = turtle1.size * turtle1.width;
	for(eU32 d = 0; d < numDraw; d++) {
		eF32 t0 = ((eF32)d / (eF32)numDraw);
		eF32 t1 = ((eF32)(d + 1) / (eF32)numDraw);
		for(eU32 r = 0; r <= 1; r++) {
			eF32 tt = (r == 0) ? t0 : t1;
			eF32 rscale = eLerp(rscale0, rscale1, tt);
			if((r != 0) || (state.lastVertices->size() == 0)) {
                // create ring vertices
                __declspec(align(16)) eVector3 position;
                __declspec(align(16)) eVector3 normal;

                // calculate bezier curve position
                __m128 mt = _mm_set1_ps(tt);
                __m128 mtinv = _mm_set1_ps(1.0f - tt);
                __m128 mcp0 = _mm_load_ps(&control0.x);
                __m128 mcp1 = _mm_load_ps(&control1.x);
                __m128 m0 = _mm_add_ps(_mm_mul_ps(mcp0, mtinv), _mm_mul_ps(mcp1, mt));
                __m128 mcp2 = _mm_load_ps(&control2.x);
                __m128 m1 = _mm_add_ps(_mm_mul_ps(mcp1, mtinv), _mm_mul_ps(mcp2, mt));
                __m128 mm0 = _mm_add_ps(_mm_mul_ps(m0, mtinv), _mm_mul_ps(m1, mt));
                __m128 mcp3 = _mm_load_ps(&control3.x);
                __m128 m2 = _mm_add_ps(_mm_mul_ps(mcp2, mtinv), _mm_mul_ps(mcp3, mt));
                __m128 mm1 = _mm_add_ps(_mm_mul_ps(m1, mtinv), _mm_mul_ps(m2, mt));
                __m128 bezCurvePosition = _mm_add_ps(_mm_mul_ps(mm0, mtinv), _mm_mul_ps(mm1, mt));

                // calculate bezier tangent
                __m128 vec3mask = _mm_set_ps(0x0,0xFFFFFFFF,0xFFFFFFFF, 0xFFFFFFFF);
                __m128 mrestangent = _mm_and_ps(_mm_sub_ps(mm1, mm0), vec3mask);

                __m128 mdot = _mm_mul_ps(mrestangent, mrestangent);
                __m128 mdotagg = _mm_hadd_ps(mdot, mdot);
                __m128 recipsqrt = _mm_rsqrt_ss( _mm_hadd_ps(mdotagg, mdotagg) );
                __m128 tangentnorm = _mm_mul_ps(mrestangent, _mm_shuffle_ps(recipsqrt, recipsqrt, _MM_SHUFFLE(0,0,0,0)));


                // get look vector on axis 2 (ringRot.getVector(2))
                eQuat       ringRot = turtle0.rotation.slerp(tt, turtle1.rotation);
                __m128 mRingRot = _mm_loadu_ps((eF32*)&ringRot);
                __m128 rrmulparts = _mm_mul_ps(mRingRot, _mm_shuffle_ps(mRingRot, mRingRot, _MM_SHUFFLE(0,1,3,2)));

                __m128 ringRotSqr = _mm_mul_ps(mRingRot, mRingRot);
                __m128 mrdotagg = _mm_hadd_ps(rrmulparts, ringRotSqr);
                __m128 mrdotaggshuf = _mm_shuffle_ps(mrdotagg, mrdotagg, _MM_SHUFFLE(0,2,0,2));
                __m128 mrrotz = _mm_hsub_ps(rrmulparts, mrdotaggshuf);
                __m128 rrecipsqrt = _mm_rsqrt_ss( _mm_hadd_ps(mrdotagg, mrdotagg) );

                __m128 maxisparts = _mm_shuffle_ps(mrrotz,mrdotagg, _MM_SHUFFLE(0,2,0,2)); // -Y-X
                __m128 maxisparts2 = _mm_add_ps(maxisparts, maxisparts); // -Y*2-X*2
                __m128 maxispartsfinal = _mm_shuffle_ps(mrrotz,maxisparts2,_MM_SHUFFLE(0,0,2,0)); //ZZY*2X*2
                __m128 mlook = _mm_and_ps(_mm_mul_ps(maxispartsfinal, _mm_shuffle_ps(rrecipsqrt, rrecipsqrt, _MM_SHUFFLE(0,0,0,0))), vec3mask);

                // calculate side vector (look ^ tangent)
                __m128 mside = _mm_sub_ps(
                    _mm_mul_ps(_mm_shuffle_ps(mlook, mlook, _MM_SHUFFLE(3, 0, 2, 1)), _mm_shuffle_ps(tangentnorm, tangentnorm, _MM_SHUFFLE(3, 1, 0, 2))),
                    _mm_mul_ps(_mm_shuffle_ps(mlook, mlook, _MM_SHUFFLE(3, 1, 0, 2)), _mm_shuffle_ps(tangentnorm, tangentnorm, _MM_SHUFFLE(3, 0, 2, 1)))
                  );

                // normalize side vector
                mdot = _mm_mul_ps(mside, mside);
                mdotagg = _mm_hadd_ps(mdot, mdot);
                __m128 dotsum = _mm_hadd_ps(mdotagg, mdotagg);
                const eF32 sideLenSqr = dotsum.m128_f32[0];
                if(sideLenSqr > eALMOST_ZERO) {
                    recipsqrt = _mm_rsqrt_ss( dotsum );
                    __m128 sidenorm = _mm_mul_ps(mside, _mm_shuffle_ps(recipsqrt, recipsqrt, _MM_SHUFFLE(0,0,0,0)));

                    // calc dot product (look * tangent)
                    __m128 dotprod = _mm_mul_ps(mlook, sidenorm);
                    __m128 dph0 = _mm_hadd_ps(dotprod, dotprod);
                    __m128 dph1 = _mm_hadd_ps(dph0, dph0);
                    const eF32 dot = eClamp(-1.0f, dph1.m128_f32[0], 1.0f);
		            eF32 alpha = eACos(dot) * (1.0f / (2.0f * ePI));

                    eQuat rotation(sidenorm, alpha);
		            ringRot = rotation * ringRot;
	            }


				eMatrix4x4 curveMat(ringRot);
                __declspec(align(16)) eVector3 ringX = curveMat.getVector(0);
                __declspec(align(16)) eVector3 ringY = curveMat.getVector(1);

				eF32 texY = eLerp(stexY0, stexY1, tt);
                const eF32 texXStep = 1.0f / m_gen_edges;
                eVector2 texPos(0, texY);
                
                __m128 mRingX = _mm_load_ps(&ringX.x);
                __m128 mRingY = _mm_load_ps(&ringY.x);
                __m128 mScale = _mm_set1_ps(rscale);

				for(eU32 e = 0; e <= m_gen_edges * 2; e += 2) {
                    __m128 msin = _mm_set1_ps(m_gen_edge_sinCosTable[e]);
                    __m128 mcos = _mm_set1_ps(m_gen_edge_sinCosTable[e+1]);
                    __m128 mnormal = _mm_add_ps(_mm_mul_ps(mRingX, msin), _mm_mul_ps(mRingY, mcos));
                    _mm_store_ps(&normal.x, mnormal);
                    __m128 mposition = _mm_add_ps(bezCurvePosition, _mm_mul_ps(mnormal, mScale));
                    _mm_store_ps(&position.x, mposition);

                    state.curVertices->append(destMesh.addVertex(position, normal, texPos));
                    texPos.x += texXStep;
                }

				// connect triangles
				if(r != 0) {
					eF32 texY0 = eLerp(stexY0, stexY1, t0);
					eF32 texY1 = eLerp(stexY0, stexY1, t1);
					for(eU32 e = 0; e < m_gen_edges; e++) {
						destMesh.addTriangleFast((*state.curVertices)[e], 
							                 (*state.curVertices)[e + 1], 
											 (*state.lastVertices)[e + 1],
											 m_gen_materials_dsIdx[turtle0.polyMatIdx]);
						destMesh.addTriangleFast((*state.curVertices)[e], 
							                 (*state.lastVertices)[e + 1], 
											 (*state.lastVertices)[e],
											 m_gen_materials_dsIdx[turtle0.polyMatIdx]);
					}
				}

				state.lastVertices = state.curVertices;
				eSwap(state.curVertices, state.curTempVertices);
				state.curVertices->clear();
			}
		}
	}
	return true;
}