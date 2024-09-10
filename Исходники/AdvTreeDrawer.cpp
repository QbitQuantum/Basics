void CAdvTreeDrawer::DrawShadowPass()
{
	const float treeDistance = oldTreeDistance;
	const int activeFarTex = (camera->forward.z < 0.0f)? treeGen->farTex[0] : treeGen->farTex[1];
	const bool drawDetailed = (treeDistance >= 4.0f);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, activeFarTex);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_ALPHA_TEST);
	glDisable(GL_CULL_FACE);

	glPolygonOffset(1, 1);
	glEnable(GL_POLYGON_OFFSET_FILL);

	CAdvTreeSquareDrawer_SP drawer;
	const int cx = drawer.cx = (int)(camera->pos.x / (SQUARE_SIZE * TREE_SQUARE_SIZE));
	const int cy = drawer.cy = (int)(camera->pos.z / (SQUARE_SIZE * TREE_SQUARE_SIZE));

	drawer.drawDetailed = drawDetailed;
	drawer.td = this;
	drawer.treeDistance = treeDistance * SQUARE_SIZE * TREE_SQUARE_SIZE;

	Shader::IProgramObject* po = NULL;

	GML_STDMUTEX_LOCK(tree); // DrawShadowPass

	// draw with extraSize=1
	readmap->GridVisibility(camera, TREE_SQUARE_SIZE, drawer.treeDistance * 2.0f, &drawer, 1);

	if (drawDetailed) {
		const int xstart = std::max(                              0, cx - 2);
		const int xend   = std::min(gs->mapx / TREE_SQUARE_SIZE - 1, cx + 2);
		const int ystart = std::max(                              0, cy - 2);
		const int yend   = std::min(gs->mapy / TREE_SQUARE_SIZE - 1, cy + 2);

		glBindTexture(GL_TEXTURE_2D, treeGen->barkTex);
		glEnable(GL_TEXTURE_2D);

		po = shadowHandler->GetShadowGenProg(CShadowHandler::SHADOWGEN_PROGRAM_TREE_NEAR);
		po->Enable();

		if (globalRendering->haveGLSL) {
			po->SetUniform3fv(1, &camera->right[0]);
			po->SetUniform3fv(2, &camera->up[0]);
		} else {
			po->SetUniformTarget(GL_VERTEX_PROGRAM_ARB);
			po->SetUniform4f(13, camera->right.x, camera->right.y, camera->right.z, 0.0f);
			po->SetUniform4f(9,  camera->up.x,    camera->up.y,    camera->up.z,    0.0f);
			po->SetUniform4f(11, 1.0f, 1.0f, 1.0f, 0.85f                           );
			po->SetUniform4f(12, 0.0f, 0.0f, 0.0f, 0.20f * (1.0f / MAX_TREE_HEIGHT));   // w = alpha/height modifier
		}

		glAlphaFunc(GL_GREATER, 0.5f);
		glEnable(GL_ALPHA_TEST);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		CVertexArray* va = GetVertexArray();
		va->Initialize();

		static FadeTree fadeTrees[3000];
		FadeTree* pFT = fadeTrees;

		for (TreeSquareStruct* pTSS = trees + (ystart * treesX); pTSS <= trees + (yend * treesX); pTSS += treesX) {
			for (TreeSquareStruct* tss = pTSS + xstart; tss <= pTSS + xend; ++tss) {
				tss->lastSeen = gs->frameNum;
				va->EnlargeArrays(12 * tss->trees.size(), 0, VA_SIZE_T); //!alloc room for all tree vertexes

				for (std::map<int, TreeStruct>::iterator ti = tss->trees.begin(); ti != tss->trees.end(); ++ti) {
					const TreeStruct* ts = &ti->second;
					const float3 pos(ts->pos);

					if (!camera->InView(pos + float3(0, MAX_TREE_HEIGHT / 2, 0), MAX_TREE_HEIGHT / 2 + 150)) {
						continue;
					}

					const float camDist = (pos - camera->pos).SqLength();
					int type = ts->type;
					float dy = 0.0f;
					unsigned int dispList;

					if (type < 8) {
						dy = 0.5f;
						dispList = treeGen->pineDL + type;
					} else {
						type -= 8;
						dy = 0;
						dispList = treeGen->leafDL + type;
					}

					if (camDist < SQUARE_SIZE * SQUARE_SIZE * 110 * 110) {
						po->SetUniform3f((globalRendering->haveGLSL? 3: 10), pos.x, pos.y, pos.z);
						glCallList(dispList);
					} else if (camDist < SQUARE_SIZE * SQUARE_SIZE * 125 * 125) {
						const float relDist = (pos.distance(camera->pos) - SQUARE_SIZE * 110) / (SQUARE_SIZE * 15);

						glAlphaFunc(GL_GREATER, 0.8f + relDist * 0.2f);
						po->SetUniform3f((globalRendering->haveGLSL? 3: 10), pos.x, pos.y, pos.z);
						glCallList(dispList);
						glAlphaFunc(GL_GREATER, 0.5f);

						pFT->pos = pos;
						pFT->deltaY = dy;
						pFT->type = type;
						pFT->relDist = relDist;
						++pFT;
					} else {
						CAdvTreeDrawer::DrawTreeVertex(va, pos, type * 0.125f, dy, false);
					}
				}
			}
		}


		po->SetUniform3f((globalRendering->haveGLSL? 3: 10), 0.0f, 0.0f, 0.0f);

		for (std::list<FallingTree>::iterator fti = fallingTrees.begin(); fti != fallingTrees.end(); ++fti) {
			const float3 pos = fti->pos - UpVector * (fti->fallPos * 20);

			if (camera->InView(pos + float3(0, MAX_TREE_HEIGHT / 2, 0), MAX_TREE_HEIGHT / 2)) {
				const float ang = fti->fallPos * PI;

				const float3 yvec(fti->dir.x * sin(ang), cos(ang), fti->dir.z * sin(ang));
				const float3 zvec((yvec.cross(float3(1.0f, 0.0f, 0.0f))).ANormalize());
				const float3 xvec(zvec.cross(yvec));

				CMatrix44f transMatrix(pos, xvec, yvec, zvec);

				glPushMatrix();
				glMultMatrixf(&transMatrix[0]);

				int type = fti->type;
				int dispList;

				if (type < 8) {
					dispList = treeGen->pineDL + type;
				} else {
					type -= 8;
					dispList = treeGen->leafDL + type;
				}

				glCallList(dispList);
				glPopMatrix();
			}
		}

		po->Disable();
		po = shadowHandler->GetShadowGenProg(CShadowHandler::SHADOWGEN_PROGRAM_TREE_FAR);
		po->Enable();

		glBindTexture(GL_TEXTURE_2D, activeFarTex);
		va->DrawArrayT(GL_QUADS);

		for (FadeTree* pFTree = fadeTrees; pFTree < pFT; ++pFTree) {
			// faded close trees
			va = GetVertexArray();
			va->Initialize();
			va->CheckInitSize(12 * VA_SIZE_T);

			CAdvTreeDrawer::DrawTreeVertex(va, pFTree->pos, pFTree->type * 0.125f, pFTree->deltaY, false);

			glAlphaFunc(GL_GREATER, 1.0f - (pFTree->relDist * 0.5f));
			va->DrawArrayT(GL_QUADS);
		}

		po->Disable();
	}

	glEnable(GL_CULL_FACE);
	glDisable(GL_POLYGON_OFFSET_FILL);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_ALPHA_TEST);
}