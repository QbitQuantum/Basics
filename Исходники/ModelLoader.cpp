XMMATRIX ModelLoader::ConvertFBXtoDXMatrix( aiMatrix4x4 inMat ) {
	// aiMatrix is transposed
	XMMATRIX xmInMat = XMLoadFloat4x4( &XMFLOAT4X4(
		inMat.a1, inMat.b1, inMat.c1, inMat.d1,
		inMat.a2, inMat.b2, inMat.c2, inMat.d2,
		inMat.a3, inMat.b3, inMat.c3, inMat.d3,
		inMat.a4, inMat.b4, inMat.c4, inMat.d4 ) );
	XMVECTOR translate, scale, rotQuat;
	XMMatrixDecompose( &scale, &rotQuat, &translate, xmInMat );
	scale = scale*100;
	return nullptr;
}