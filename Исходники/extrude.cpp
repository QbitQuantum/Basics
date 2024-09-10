static void MakeMeshCapTexture(Mesh &mesh, Matrix3 &itm, int fstart, int fend, BOOL usePhysUVs) {
	if(fstart == fend)
		return;
	// Find out which verts are used by the cap
	BitArray capVerts(mesh.numVerts);
	capVerts.ClearAll();
	for(int i = fstart; i < fend; ++i) {
		Face &f = mesh.faces[i];
		capVerts.Set(f.v[0]);
		capVerts.Set(f.v[1]);
		capVerts.Set(f.v[2]);
		}
	// Minmax the verts involved in X/Y axis and total them
	Box3 bounds;
	int numCapVerts = 0;
	int numCapFaces = fend - fstart;
	IntTab capIndexes;
	capIndexes.SetCount(mesh.numVerts);
	int baseTVert = mesh.getNumTVerts();
	for(int i = 0; i < mesh.numVerts; ++i) {
		if(capVerts[i]) {
			capIndexes[i] = baseTVert + numCapVerts++;
			bounds += mesh.verts[i] * itm;
			}
		}
	mesh.setNumTVerts(baseTVert + numCapVerts, TRUE);
	Point3 s;
    if (usePhysUVs)
        s = Point3(1.0f, 1.0f, 0.0f);
    else
        s = Point3(1.0f / bounds.Width().x, 1.0f / bounds.Width().y, 0.0f);

	Point3 t(-bounds.Min().x, -bounds.Min().y, 0.0f);
	// Do the TVerts
	for(int i = 0; i < mesh.numVerts; ++i) {
		if(capVerts[i])
			mesh.setTVert(baseTVert++, ((mesh.verts[i] * itm) + t) * s);
		}
	// Do the TVFaces
	for(int i = fstart; i < fend; ++i) {
		Face &f = mesh.faces[i];
		mesh.tvFace[i] = TVFace(capIndexes[f.v[0]], capIndexes[f.v[1]], capIndexes[f.v[2]]);
		}
	}