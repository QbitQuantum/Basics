bool TSShapeImport::import(const TSMesh* mesh,
	const TSMaterialList* materialList,ITRGeometry* geometry)
{
	const TSMeshAccess* pmesh = static_cast<const TSMeshAccess*>(mesh);
	const TSVertex* pVertices = pmesh->getVertices();
	const Point2F* pTextureCoords = pmesh->getTextureCoords();

	TPlaneF::DistancePrecision = distancePrecision;
	TPlaneF::NormalPrecision = normalPrecision;

	// Copy faces
	int nFaces = pmesh->getFaceCount();
	const TSMeshFace* pFaces = pmesh->getFaces();
	for (int i = 0; i < nFaces; i++) {
		const TSMeshFace& face = pFaces[i];
		ITRBitVector bv;

		// Build surface
		geometry->surfaceList.push_back(ITRGeometry::Surface());
		ITRGeometry::Surface& surface = geometry->surfaceList.last();
		surface.type = ITRGeometry::Surface::Material;
		surface.material = face.fMaterial;
		surface.textureOffset.x = 
			surface.textureOffset.y = 0;

		// Identify link surfaces
		const TSMaterial& material = (*materialList)[surface.material];
		if (material.fType == TSMaterial::MatRGB && 
			material.fRGB.fRed == .0f &&
			material.fRGB.fGreen == .0f &&
			material.fRGB.fBlue == .0f)
			surface.type = ITRGeometry::Surface::Link;
		else
			if (material.fType == TSMaterial::MatPalette && 
				material.fIndex == 0)
				surface.type = ITRGeometry::Surface::Link;

		// Build poly
		surface.polyCount = 1;
		surface.polyIndex = geometry->polyList.size();
		geometry->polyList.push_back(ITRGeometry::Poly());

		ITRGeometry::Poly& poly = geometry->polyList.last();
		poly.vertexCount = (face.fV[2] == face.fV[3])? 3: 4;
		poly.vertexIndex = geometry->vertexList.size();
		geometry->vertexList.setSize(geometry->vertexList.size() + poly.vertexCount);
		ITRGeometry::Vertex* vp = &geometry->vertexList[poly.vertexIndex];

		for (int i = 0; i < poly.vertexCount; i++) {
			Point3F sp = snap(pVertices[face.fV[i]].fPoint);
			vp[i].pointIndex = geometry->point3List.add(sp);
			vp[i].textureIndex = geometry->point2List.add
				(pTextureCoords[face.fT[i]]);
			bv.set(vp[i].pointIndex);
		}

		// Build plane
		// Make sure the three points of the poly are not on a line.
		TPlaneF plane;
		Point3F *p1 = &geometry->point3List[vp[0].pointIndex];
		Point3F *p2 = &geometry->point3List[vp[1].pointIndex];
		Point3F *p3 = &geometry->point3List[vp[2].pointIndex];
		if (poly.vertexCount > 3 && isLine(*p1,*p2,*p3)) {
			p1 = p2, p2 = p3;
			p3 = &geometry->point3List[vp[3].pointIndex];
		}
		if (isLine(*p1,*p2,*p3)) {
			printf("   Degenerate poly dropped\n");
			geometry->surfaceList.decrement();
			continue;
		}
		plane.set(*p1,*p2,*p3);

		// Add plane to list.
		ITRVector<TPlaneF>::iterator itr = 
			::find(geometry->planeList.begin(),geometry->planeList.end(),plane);
		if (itr == geometry->planeList.end()) {
			// Try too match inverted plane.
			plane.neg();
			itr = ::find(geometry->planeList.begin(),
				geometry->planeList.end(),plane);
			if (itr == geometry->planeList.end()) {
				// No inverted either, so add original plane
				// to the list.
				surface.planeIndex = geometry->planeList.size();
				surface.planeFront = true;
				plane.neg();
				geometry->planeList.push_back(plane);
			}
			else {
				surface.planeIndex = itr - geometry->planeList.begin();
				surface.planeFront = false;
			}
		}
		else {
			surface.planeIndex = itr - geometry->planeList.begin();
			surface.planeFront = true;
		}

		// Build bitvec of points used by the surface
		surface.pointIndex = geometry->bitList.size();
		surface.pointCount = bv.compress(&geometry->bitList);
	}
	//setBoundingBox(*geometry);
	return true;
}