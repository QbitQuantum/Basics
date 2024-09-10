Mesh*
TriObject::GetRenderMesh(TimeValue t, INode *inode, View &view, BOOL& needDelete)
{
	if (mDisableDisplacement || !(view.flags & RENDER_MESH_DISPLACEMENT_MAP)) {
		needDelete = FALSE;
		return &mesh;
	}
	// need to check the mesh and see if any face has a matId the requires displacment mapping
	BOOL needDisp = FALSE;

	// Get the material
	Mtl* pMtl = inode ? inode->GetMtl() : NULL;

	if (pMtl) {
		// does the mesh as a whole need it
		if (pMtl->Requirements(mesh.mtlIndex)&MTLREQ_DISPLACEMAP)
			needDisp = TRUE;

		if (!needDisp) {
			for (int f = 0; f < mesh.numFaces; f++) {
				if (pMtl->Requirements(mesh.getFaceMtlIndex(f))&MTLREQ_DISPLACEMAP) {
					needDisp = TRUE;
					break;
				}
			}
		}

		if (needDisp) {
            if (mesh.getNumFaces() == 0)
                return &mesh;

			Matrix3 otm;
			if (inode)
				otm = inode->GetObjectTM(t);
			else
				otm.IdentityMatrix();
			GetGTessFunction();
			if (mSubDivideDisplacement && psGTessFunc) {
				// if we have a material that does displacement mapping and if we can do it
				Mesh *pMesh = new Mesh();
				needDelete = TRUE;
				(*psGTessFunc)((void *)&mesh, MAX_MESH, &otm, pMesh, NULL,
								&mDispApprox, &view, pMtl, FALSE, mSplitMesh);
				needDelete = TRUE;
				return pMesh;
			} else {
				Mesh *pMesh = new Mesh(mesh);
				needDelete = TRUE;

                BOOL hasUVs = pMesh->tvFace != NULL;
				pMesh->buildRenderNormals();

				// now displace the verts
				BitArray vertsSet;
				vertsSet.SetSize(pMesh->numVerts);

				for (int f = 0; f < pMesh->numFaces; f++) {
					Face *pFace = &pMesh->faces[f];
					TVFace *pTVFace = &pMesh->tvFace[f];
					int matid = pFace->getMatID();
					for (int v = 0; v < 3; v++) {
						int vidx = pFace->v[v];
						if (vertsSet[vidx])
							continue; // displace only once
						Point3 norm = pMesh->getNormal(vidx);
						norm.Normalize();
						Point3& vert = pMesh->getVert(vidx);

						UVVert uvvert;
                        if (hasUVs)
                            uvvert = pMesh->getTVert(pTVFace->t[v]);
                        else {
                            uvvert.x = 0.0;
                            uvvert.y = 0.0;
                        }

						pMesh->buildBoundingBox();
						Box3 bbox = pMesh->getBoundingBox();
						float dispScale = Length(bbox.pmax - bbox.pmin)/10.0f;

						float disp = GetDisp(pMtl, pMesh, f, pFace->getMatID(), vert, uvvert.x, uvvert.y, otm) * dispScale;
						vert += (norm * disp);
						vertsSet.Set(vidx);
					}
				}
				return pMesh;
			}
		}
	}

	needDelete = FALSE;
	return &mesh;
}