void NURBS::Refine(vector<Reference<Shape> > &refined) const {
	// Compute NURBS dicing rates
	int diceu = 30, dicev = 30;
	float *ueval = new float[diceu];
	float *veval = new float[dicev];
	Point *evalPs = new Point[diceu*dicev];
	Normal *evalNs = new Normal[diceu*dicev];
	int i;
	for (i = 0; i < diceu; ++i)
		ueval[i] = Lerp((float)i / (float)(diceu-1), umin, umax);
	for (i = 0; i < dicev; ++i)
		veval[i] = Lerp((float)i / (float)(dicev-1), vmin, vmax);
	// Evaluate NURBS over grid of points
	memset(evalPs, 0, diceu*dicev*sizeof(Point));
	memset(evalNs, 0, diceu*dicev*sizeof(Point));
	float *uvs = new float[2*diceu*dicev];
	// Turn NURBS into triangles
	Homogeneous3 *Pw = (Homogeneous3 *)P;
	if (!isHomogeneous) {
		Pw = (Homogeneous3 *)alloca(nu*nv*sizeof(Homogeneous3));
		for (int i = 0; i < nu*nv; ++i) {
			Pw[i].x = P[3*i];
			Pw[i].y = P[3*i+1];
			Pw[i].z = P[3*i+2];
			Pw[i].w = 1.;
		}
	}
	for (int v = 0; v < dicev; ++v) {
		for (int u = 0; u < diceu; ++u) {
			uvs[2*(v*diceu+u)]   = ueval[u];
			uvs[2*(v*diceu+u)+1] = veval[v];
	
			Vector dPdu, dPdv;
			Point pt = NURBSEvaluateSurface(uorder, uknot, nu, ueval[u],
				vorder, vknot, nv, veval[v], Pw, &dPdu, &dPdv);
			evalPs[v*diceu + u].x = pt.x;
			evalPs[v*diceu + u].y = pt.y;
			evalPs[v*diceu + u].z = pt.z;
			evalNs[v*diceu + u] = Normal(Normalize(Cross(dPdu, dPdv)));
		}
	}
	// Generate points-polygons mesh
	int nTris = 2*(diceu-1)*(dicev-1);
	int *vertices = new int[3 * nTris];
	int *vertp = vertices;
	// Compute the vertex offset numbers for the triangles
	for (int v = 0; v < dicev-1; ++v) {
		for (int u = 0; u < diceu-1; ++u) {
	#define VN(u,v) ((v)*diceu+(u))
			*vertp++ = VN(u,   v);
			*vertp++ = VN(u+1, v);
			*vertp++ = VN(u+1, v+1);
	
			*vertp++ = VN(u,   v);
			*vertp++ = VN(u+1, v+1);
			*vertp++ = VN(u,   v+1);
	#undef VN
		}
	}
	int nVerts = diceu*dicev;
	ParamSet paramSet;
	paramSet.AddInt("indices", vertices, 3*nTris);
	paramSet.AddPoint("P", evalPs, nVerts);
	paramSet.AddFloat("uv", uvs, 2 * nVerts);
	paramSet.AddNormal("N", evalNs, nVerts);
	refined.push_back(MakeShape("trianglemesh", ObjectToWorld,
			reverseOrientation, paramSet));
	// Cleanup from NURBS refinement
	delete[] uvs;
	delete[] ueval;
	delete[] veval;
	delete[] evalPs;
	delete[] evalNs;
	delete[] vertices;
}