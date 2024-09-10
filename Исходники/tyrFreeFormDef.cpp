void tyrFreeFormDef::reParamVertices(vector<RectCoord> &param, Vector3 &S,Vector3 &T, Vector3 &U){
	printf("  - Reparameterizing vertices\n");

	int nVtx = _ply.GetNumVertices();
	point3D_t *vtx = _ply.GetVertices();

	Vector3 min = _ply.GetMin();
	Vector3 p0 = min;
	Vector3 max = _ply.GetMax();

	S = Vector3(max.x - min.x,0.0,0.0);
	T = Vector3(0.0,max.y - min.y,0.0);
	U = Vector3(0.0,0.0,max.z - min.z);


	Vector3 TcU = T.Cross(U);
	Vector3 ScU = S.Cross(U);
	Vector3 ScT = S.Cross(T);

	double TcUdS = TcU.Dot(S);
	double ScUdT = ScU.Dot(T);
	double ScTdU = ScT.Dot(U);

	for(int v = 0; v < nVtx; v++){
		Vector3 diff = vtx[v].ToVector3() - p0;

		RectCoord tmp;
		tmp.s = TcU.Dot(diff/TcUdS);
		tmp.t = ScU.Dot(diff/ScUdT);
		tmp.u = ScT.Dot(diff/ScTdU);
		tmp.p = p0 + (tmp.s * S) + (tmp.t * T) + (tmp.u * U);
		tmp.p0 = p0;
		
		{	///Pre-calculate bernstein polynomial expansion.  It only needs to be done once per parameterization
			for(int i = 0; i <= 5; i++){
				for(int j = 0; j <= 5; j++){
					
					for(int k = 0; k <= 5; k++){
						tmp.bernPolyPack[n][k][2] = bern_poly(n,k,tmp.u);
					}
					tmp.bernPolyPack[m][j][1] = bern_poly(m,j,tmp.t);
				}
				tmp.bernPolyPack[l][i][0] = bern_poly(l,i,tmp.s);
			}
		}
		param.push_back(tmp);
		if(tmp.p.Dist(vtx[v].ToVector3()) > Math::EPSILON){
			printf("     - Warning, vtx[%d] does not match it's parameterization.\n",v);
		}
	}
	for(int i = 0; i <= 5; i++){
		for(int j = 0; j <= 5; j++){
			Vector3 tK(0.0f,0.0f,0.0f);
			for(int k = 0; k <= 5; k++){
				controlPoints[i][j][k] = createControlPoint(min,i,j,k,S,T,U);
				
			}
		}
	}
}