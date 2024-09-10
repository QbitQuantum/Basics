void TMesh::Render(PPC * ppc, FrameBuffer *fb, PointLight *pl, bool wireframe, Envmap *env){
	if(trisN == 0 && vertsN != 0){
		RenderPoints(ppc,fb,3);
		return;
	}else if(trisN == 0 && vertsN == 0){
		return;
	}
	
	Vector3D *projVerts = new Vector3D[vertsN];

	for(int i = 0; i < vertsN; i++){
		projVerts[i] = Vector3D(FLT_MAX, FLT_MAX, FLT_MAX);
		ppc->Project(verts[i], projVerts[i]);
	}

	for(int i = 0; i < trisN; i++){
		int currTri = i;

		unsigned int vinds[3];
		vinds[0] = tris[3*i+0];
		vinds[1] = tris[3*i+1];
		vinds[2] = tris[3*i+2];

		if(wireframe){
			for(int j = 0; j < 3; j++){
				fb->DrawSegment(projVerts[vinds[j]], projVerts[vinds[(j+1)%3]], cols[vinds[j]], cols[vinds[(j+1)%3]]);
			}

			continue;
		}

		//Setup Rasterization

		//Create AABB
		AABB aabb = AABB(projVerts[vinds[0]]);
		aabb.AddPoint(projVerts[vinds[1]]);
		aabb.AddPoint(projVerts[vinds[2]]);

		if(!aabb.Clip(fb->w, fb->h)){
			continue;
		}

		int top = (int) (0.5f + aabb.corners[0][1]);
		int left = (int) (0.5f + aabb.corners[0][0]);
		int bottom = (int) (-0.5f + aabb.corners[1][1]);
		int right = (int) (-0.5f + aabb.corners[1][0]);

		//Edge equations
		Vector3D eeqs[3];

		for(int i = 0; i < 3; i++){
			int _i = (i+1)%3;

			eeqs[i][0] = projVerts[vinds[_i]][1] - projVerts[vinds[i]][1];
			eeqs[i][1] = projVerts[vinds[i]][0] - projVerts[vinds[_i]][0];
			eeqs[i][2] = projVerts[vinds[i]][1] * (-eeqs[i][1]) - projVerts[vinds[i]][0] * eeqs[i][0];

			int _i2 = (i+2)%3;

			Vector3D v3 = Vector3D(projVerts[vinds[_i2]][0], projVerts[vinds[_i2]][1], 1.0f);

			if(v3*eeqs[i] < 0){
				eeqs[i] = -1.0f * eeqs[i];
			}
		}

		//Screen Space Interpolation
		Matrix3x3 ssii = Matrix3x3();
		ssii[0] = projVerts[vinds[0]]; ssii[0][2] = 1.0f;
		ssii[1] = projVerts[vinds[1]]; ssii[1][2] = 1.0f;
		ssii[2] = projVerts[vinds[2]]; ssii[2][2] = 1.0f;
		ssii = ssii.inverse();

		//Color interpolation
		Matrix3x3 tcols = Matrix3x3();
		tcols[0] = cols[vinds[0]];
		tcols[1] = cols[vinds[1]];
		tcols[2] = cols[vinds[2]];

		if(gouraud){ //Apply lighting before creating interpolation matrix
			Vector3D toPL;
			Vector3D norm;

			Vector3D eyeV;
			Vector3D reflectedToPL;

			for(int i = 0; i < 3; i++){
				toPL = (pl->pos - verts[vinds[i]]).normalize();
				norm = (normals[vinds[i]]).normalize();

				eyeV = (ppc->C - verts[vinds[i]]).normalize();
				reflectedToPL = (2.0f * norm * (norm * toPL) - toPL).normalize();

				kdiff = toPL * norm;
				if(kdiff < 0.0f){
					kdiff = 0.0f;
				}

				float temp = reflectedToPL * eyeV;

				if(temp < 0){
					temp = 0;
				}

				kspec = pow(temp, phongExp);

				if(norm * toPL < 0){
					kspec = 0;
				}

				tcols[i] = tcols[i] * (kamb + (1.0f - kamb) * kdiff + kspec);
			}
		}

		Matrix3x3 colABCs = ssii*tcols;
		colABCs = colABCs.transpose();

		//Z buffer interpolation
		Vector3D tzs = Vector3D(projVerts[vinds[0]][2], projVerts[vinds[1]][2], projVerts[vinds[2]][2]);
		Vector3D zABC = ssii * tzs;

		//Normal interpolation
		
		Matrix3x3 tnormals = Matrix3x3();
		Matrix3x3 normalABCs = Matrix3x3();
		if(normals != NULL){
			tnormals[0] = normals[vinds[0]];
			tnormals[1] = normals[vinds[1]];
			tnormals[2] = normals[vinds[2]];
			normalABCs = ssii*tnormals;
			normalABCs = normalABCs.transpose();
		}

		//Model Space Interpolation
		Matrix3x3 camM;
		camM.setColumn(0,ppc->a);
		camM.setColumn(1,ppc->b);
		camM.setColumn(2,ppc->c);
		Matrix3x3 triM;
		triM.setColumn(0, verts[vinds[0]] - ppc->C);
		triM.setColumn(1, verts[vinds[1]] - ppc->C);
		triM.setColumn(2, verts[vinds[2]] - ppc->C);
		Matrix3x3 Q = triM.inverse() * camM;
		Vector3D DEF = Q[0] + Q[1] + Q[2];
		Vector3D ABCr = Vector3D(
			tcols.getColumn(0) * Q.getColumn(0), 
			tcols.getColumn(0) * Q.getColumn(1), 
			tcols.getColumn(0) * Q.getColumn(2));
		Vector3D ABCg = Vector3D(
			tcols.getColumn(1) * Q.getColumn(0), 
			tcols.getColumn(1) * Q.getColumn(1), 
			tcols.getColumn(1) * Q.getColumn(2)); 
		Vector3D ABCb = Vector3D(
			tcols.getColumn(2) * Q.getColumn(0), 
			tcols.getColumn(2) * Q.getColumn(1), 
			tcols.getColumn(2) * Q.getColumn(2));
		Vector3D ABCk = Vector3D(Q[1]);
		Vector3D ABCl = Vector3D(Q[2]);

		Matrix3x3 tst = Matrix3x3();
		Vector3D ABCs, ABCt;

		if(textured){
			tst[0] = st[vinds[0]];
			tst[1] = st[vinds[1]];
			tst[2] = st[vinds[2]];
			ABCs = Vector3D(
				tst.getColumn(0) * Q.getColumn(0), 
				tst.getColumn(0) * Q.getColumn(1), 
				tst.getColumn(0) * Q.getColumn(2));
			ABCt = Vector3D(
				tst.getColumn(1) * Q.getColumn(0), 
				tst.getColumn(1) * Q.getColumn(1), 
				tst.getColumn(1) * Q.getColumn(2));
		}


		//Rasterization
		for(int v = top; v <= bottom; v++){
			for(int u = left; u <= right; u++){
				Vector3D pixv = Vector3D(0.5f + (float)u, 0.5f + (float)v, 1.0f);
				if(pixv * eeqs[0] < 0.0f || pixv * eeqs[1] < 0.0f || pixv * eeqs[2] < 0.0f){
					continue;
				}
				if(((normalABCs*pixv).normalize() * ppc->GetVD())>=0){
					continue;
				}

				float currZ = zABC * pixv;
				Vector3D currP = Vector3D(pixv[0], pixv[1], currZ);
				if(!fb->CloserThenSet(currP)){
					continue;
				}

				Vector3D currC;
				
				//currC = colABCs * pixv; //SS Interpolation
				
				currC[0] = (ABCr*pixv) / (DEF*pixv); //MS Interpolation
				currC[1] = (ABCg*pixv) / (DEF*pixv);
				currC[2] = (ABCb*pixv) / (DEF*pixv);

				if(textured){
					Vector3D texel = Vector3D();

					texel[0] = (ABCs*pixv)/(DEF*pixv);
					texel[1] = (ABCt*pixv)/(DEF*pixv);


					FrameBuffer * currTexture = texs[triToTexMap[currTri]];

					if(texRepetition){
						texel[0] = (int)(texel[0]*currTexture->w) % currTexture->w;
						texel[1] = (int)(texel[1]*currTexture->h) % currTexture->h;
					}else if(texMirror){
						if((int)((texel[0]*currTexture->w) / currTexture->w) % 2 == 0){
							texel[0] = (int)(texel[0]*currTexture->w) % currTexture->w;
						}else{
							texel[0] = currTexture->w - 1 - ((int)(texel[0]*currTexture->w) % currTexture->w);
						}

						if((int)((texel[1]*currTexture->h) / currTexture->h) % 2 == 0){
							texel[1] = (int)(texel[1]*currTexture->h) % currTexture->h;
						}else{
							texel[1] = currTexture->h - 1 - ((int)(texel[1]*currTexture->h) % currTexture->h);
						}
					}

					currC = currTexture->GetV(texel[0],texel[1]);
				}else if(projTextured){
					int uv = (fb->h-1-v)*fb->w+u;
					Vector3D projP(0.5f + float(u), 0.5f + (float)v, currZ);
					Vector3D P = ppc->GetPoint(projP);  //Unprojecting point
					Vector3D refProjP;  //Projected point onto reference framebuffer

					if(!projPPC->Project(P,refProjP)){
						currC = Vector3D(1.0f, 0.0f, 1.0f);
					}else{
						int u0 = (int) refProjP[0];
						int v0 = (int) refProjP[1];

						if (u0 < 0 || u0 > projTM->w-1 || v0 < 0 || v0 > projTM->h-1){
							//currC = Vector3D(0.0f, 0.0f, 0.0f);
						}else{
							int uv0 = (projTM->h-1-v0)*projTM->w+u0;
							float eps = 0.01f;
							if(projTM->zb[uv0] > eps+refProjP[2]){  //If not in foreground on reference framebuffer
								currC = Vector3D(0.0f, 0.0f, 0.0f);
							}
							else{
								currC = projTM->GetV(u0, v0);
							}
						}
					}
				}

				if(phong){ //Interpolate normal, calculate lighting at individual point
					Vector3D currNorm = normalABCs * pixv;
					Vector3D toPL;
					Vector3D norm;

					Vector3D eyeV;
					Vector3D reflectedToPL;

					toPL = (pl->pos - ppc->GetPoint(currP)).normalize(); //Need to unproject currP
					norm = (currNorm).normalize(); //Using interpolated normal

					eyeV = (ppc->C - ppc->GetPoint(currP)).normalize(); //Need to unproject currP
					reflectedToPL = (2.0f * norm * (norm * toPL) - toPL).normalize();

					kdiff = toPL * norm;
					if(kdiff < 0.0f){
						kdiff = 0.0f;
					}

					float temp = reflectedToPL * eyeV;

					if(temp < 0){
						temp = 0;
					}

					kspec = pow(temp, phongExp);

					if(norm * toPL < 0){
						kspec = 0;
					}

					currC = currC * (kamb + (1.0f - kamb) * kdiff + kspec); //Applying lighting equation to the interpolated color
				}

				if(envmapReflection){
					/*Vector3D currNorm = normalABCs * pixv;
					Vector3D toPL;
					Vector3D norm;

					//Vector3D eyeV;
					Vector3D reflectedToPL;

					toPL = (ppc->C - ppc->GetPoint(currP)).normalize(); //Need to unproject currP
					norm = (currNorm).normalize(); //Using interpolated normal

					//eyeV = (ppc->C - ppc->GetPoint(currP)).normalize(); //Need to unproject currP
					reflectedToPL = (2.0f * norm * (norm * toPL) - toPL).normalize();

					unsigned int col = env->getColor(reflectedToPL);
					currC.SetFromColor(col);*/

					Vector3D norm = (normalABCs*pixv).normalize();
					Vector3D toEye = Vector3D();
					Vector3D reflected = Vector3D();

					toEye = (ppc->C - ppc->GetPoint(currP));

					reflected = (2.0f * (norm*toEye) * norm - toEye).normalize();

					unsigned int col = env->getColor(reflected);
					currC.SetFromColor(col);
				}
				
				fb->Set(u,v,currC.GetColor());
			}
		}
	}

	delete[] projVerts;
}