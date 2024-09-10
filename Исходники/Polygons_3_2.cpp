// ワールド行列の生成
XMMATRIX CreateWorldMatrix( void )
{
	float			fAngleY;							// y軸周り回転角
	static float	fAngleX = 0.0f;						// x軸周り回転角
	XMMATRIX		matRot_Y;							// y軸周り回転行列
	XMMATRIX		matRot_X;							// x軸周り回転行列

	// 強制回転
	fAngleY = 2.0f * PI * ( float )( timeGetTime() % 2000 ) / 2000.0f;

	// キー入力で回転
	if ( GetAsyncKeyState( VK_UP ) ) {
		fAngleX += ROT_SPEED;
	}
	if ( GetAsyncKeyState( VK_DOWN ) ) {
		fAngleX -= ROT_SPEED;
	}

	// 行列作成
	matRot_Y = XMMatrixRotationY( fAngleY );
	matRot_X = XMMatrixRotationX( fAngleX );

	return matRot_Y * matRot_X;						// 回転の合成
}