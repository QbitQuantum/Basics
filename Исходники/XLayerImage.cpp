// lx, ly는 0,0기준 로컬좌표
DWORD XLayerImage::GetPixel( float cx, float cy, float mx, float my, const D3DXMATRIX &m, BYTE *pa, BYTE *pr, BYTE *pg, BYTE *pb ) const
{
	XSprite *pSpr = m_pSpriteCurr;
	if( pSpr )
	{
		XE::VEC2 vLocal = GetcnPos().m_vPos;
//		float lx = GetcnPos().x;
//		float ly = GetcnPos().y;
		pSpr->SetAdjustAxis( GetvAdjustAxis() );		// 회전축을 보정함
		pSpr->SetRotateZ( GetcnRot().fAngle );
		pSpr->SetScale( GetcnScale().vScale );
		pSpr->SetFlipHoriz( (GetcnEffect().dwDrawFlag & EFF_FLIP_HORIZ) ? TRUE : FALSE );
		pSpr->SetFlipVert( (GetcnEffect().dwDrawFlag & EFF_FLIP_VERT) ? TRUE : FALSE );
//		DWORD pixel = pSpr->GetPixel( lx, ly, m, pa, pr, pg, pb );
		D3DXMATRIX mWorld;
		pSpr->GetMatrix( &mWorld, vLocal.x, vLocal.y );		
//		mWorld *= m;			// 부모의행렬과 스프라이트의 로컬행렬을곱함
		D3DXMATRIX mInv;
//		D3DXMatrixInverse( &mInv, nullptr, &mWorld );		// 이제까지 반영된 모든 매트릭스를 역행렬로 만든다
		D3DXMatrixInverse( &mInv, nullptr, &m );		// 이제까지 반영된 모든 매트릭스를 역행렬로 만든다
		D3DXVECTOR2 v = D3DXVECTOR2( mx, my );		// 마우스 클릭한 좌표
		D3DXVECTOR4 vInv;
		D3DXVec2Transform( &vInv, &v, &mInv );			// 최종 매트릭스 기준 좌표가 나온다.
		DWORD pixel = pSpr->GetPixel( vInv.x, vInv.y, pa, pr, pg, pb );
		pSpr->SetScale( 1.0f, 1.0f );
		pSpr->SetRotate( 0, 0, 0 );
		return pixel;
	}
	return 0;
}