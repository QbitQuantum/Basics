XMMATRIX CreateWorldMatrix( float x, float y, float z, float fSize )	// ワールド行列の生成
{
	float			fAngleY;							// y軸周り回転角
	static float	fAngleX = 0.0f;						// x軸周り回転角
	XMMATRIX		matRot_Y;							// y軸周り回転行列
	XMMATRIX		matRot_X;							// x軸周り回転行列
	XMMATRIX		matScaleTrans;						// 拡大縮小平行移動行列

	// 強制回転
	fAngleY = 2.0f * PI * ( float )( timeGetTime() % 3000 ) / 3000.0f;

	// 行列作成
	matRot_Y = XMMatrixRotationY( fAngleY );
	matRot_X = XMMatrixRotationX( fAngleX );

	matScaleTrans= XMMatrixIdentity();
	matScaleTrans._11 = fSize;
	matScaleTrans._22 = fSize;
	matScaleTrans._33 = fSize;
	matScaleTrans._41 = x;
	matScaleTrans._42 = y;
	matScaleTrans._43 = z;

	return matRot_Y * matRot_X * matScaleTrans;		// 変換の合成
}