static void FindVertexAngles(PatchMesh &pm, float *vang) {
	int i;
	for (i=0; i<pm.numVerts + pm.numVecs; i++) vang[i] = 0.0f;
	for (i=0; i<pm.numPatches; i++) {
		Patch &p = pm.patches[i];
		for (int j=0; j<p.type; j++) {
			Point3 d1 = pm.vecs[p.vec[j*2]].p - pm.verts[p.v[j]].p;
			Point3 d2 = pm.vecs[p.vec[((j+p.type-1)%p.type)*2+1]].p - pm.verts[p.v[j]].p;
			float len = LengthSquared(d1);
			if (len == 0) continue;
			d1 /= Sqrt(len);
			len = LengthSquared (d2);
			if (len==0) continue;
			d2 /= Sqrt(len);
			float cs = DotProd (d1, d2);
			if (cs>=1) continue;	// angle of 0
			if (cs<=-1) vang[p.v[j]] += PI;
			else vang[p.v[j]] += (float) acos (cs);
		}
	}
}