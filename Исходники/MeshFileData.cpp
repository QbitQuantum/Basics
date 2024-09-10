void CalcTangentAndBinormal(
	SimpleVertexNormal& p0,
	SimpleVertexNormal& p1,
	SimpleVertexNormal& p2
	) {
	// 5次元→3次元頂点に
	XMVECTOR CP0[3] = {
		XMVectorSet(p0.Pos.x, p0.Tex.x, p0.Tex.y,1),
		XMVectorSet(p0.Pos.y, p0.Tex.x, p0.Tex.y,1),
		XMVectorSet(p0.Pos.z, p0.Tex.x, p0.Tex.y,1),
	};
	XMVECTOR CP1[3] = {
		XMVectorSet(p1.Pos.x, p1.Tex.x, p1.Tex.y, 1),
		XMVectorSet(p1.Pos.y, p1.Tex.x, p1.Tex.y, 1),
		XMVectorSet(p1.Pos.z, p1.Tex.x, p1.Tex.y, 1),
	};
	XMVECTOR CP2[3] = {
		XMVectorSet(p2.Pos.x, p2.Tex.x, p2.Tex.y, 1),
		XMVectorSet(p2.Pos.y, p2.Tex.x, p2.Tex.y, 1),
		XMVectorSet(p2.Pos.z, p2.Tex.x, p2.Tex.y, 1),
	};

	// 平面パラメータからUV軸座標算出
	float U[3], V[3];
	for (int i = 0; i < 3; ++i) {
		XMVECTOR V1 = CP1[i] - CP0[i];
		XMVECTOR V2 = CP2[i] - CP1[i];
		XMVECTOR ABC;
		ABC = XMVector3Cross(V1, V2);

		if (ABC.x == 0.0f) {
			// やばいす！
			// ポリゴンかUV上のポリゴンが縮退してます！
			//_ASSERT(0);
			//memset(outTangent, 0, sizeof(D3DXVECTOR3));
			//memset(outBinormal, 0, sizeof(D3DXVECTOR3));
			p0.Binormal = XMFLOAT3(1, 0, 0);
			p1.Binormal = XMFLOAT3(1, 0, 0);
			p2.Binormal = XMFLOAT3(1, 0, 0);
			p0.Tangent = XMFLOAT3(0,1,0);
			p1.Tangent = XMFLOAT3(0,1,0);
			p2.Tangent = XMFLOAT3(0,1,0);
			return;
		}
		U[i] = -ABC.y / ABC.x;
		V[i] = -ABC.z / ABC.x;
	}


	XMVECTOR tan = XMVectorSet(U[0], U[1], U[2], 1);
	XMVECTOR bin = -XMVectorSet(V[0], V[1], V[2], 1);

	// 正規化します
	tan = XMVector3Normalize(tan);
	bin = XMVector3Normalize(bin);

	p0.Binormal = XMFLOAT3(bin.x, bin.y, bin.z);
	p1.Binormal = XMFLOAT3(bin.x, bin.y, bin.z);
	p2.Binormal = XMFLOAT3(bin.x, bin.y, bin.z);
	p0.Tangent = XMFLOAT3(tan.x, tan.y, tan.z);
	p1.Tangent = XMFLOAT3(tan.x, tan.y, tan.z);
	p2.Tangent = XMFLOAT3(tan.x, tan.y, tan.z);
}