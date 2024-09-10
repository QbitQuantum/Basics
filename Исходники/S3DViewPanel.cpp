void S3DViewPanel::UpdateCamera(wxMouseEvent& event)
{
	static wxPoint point;

	if( event.LeftDown() || event.RightDown() || event.MiddleDown() )
		point = event.GetPosition();

	if( event.LeftIsDown() || event.RightIsDown() || event.MiddleIsDown() )
	{
		long x = event.GetX();
		long y = event.GetY();

		CVector2 dPoint = CVector2( point.x - x, point.y - y);
		point.x = x;
		point.y = y;

		IEntity* pCamera = GLOBAL::ObserverCamera()->GetEntity();

		if( event.LeftIsDown() )
		{	
			if( GLOBAL::SelectionMgr()->List()->size() == 0 )
			{
				// FPS camera moving
				if( fabs(dPoint.x) > fabs(dPoint.y) )
					pCamera->RotateLocalAxis( CVector3(0, 0, 1), dPoint.x * 0.005f);
				else
					pCamera->RotateLocalAxis( pCamera->GetWorldTM().r[0], dPoint.y * 0.005f );
			}
			else
			{
				// rotate in entity coordinate system
				IEntity* pEntity = GLOBAL::SelectionMgr()->First();
				XMMATRIX entityTM = XMMatrixIdentity();
				entityTM.r[3] = pEntity->GetWorldPos().ToXMVEECTOR();
				XMMATRIX invEntityTM = XMMATRIX_UTIL::Inverse(NULL, entityTM );

				XMMATRIX tm = XMMatrixMultiply( pCamera->GetWorldTM() , invEntityTM );

				if( fabs(dPoint.x) > fabs(dPoint.y) )
				{
					XMMATRIX rotTM = XMMatrixRotationAxis( CVector3(0,0,1).ToXMVEECTOR(), dPoint.x * 0.005f );
					tm = XMMatrixMultiply( tm, rotTM );

				}
				else
				{
					XMMATRIX rotTM = XMMatrixRotationAxis( pCamera->GetWorldTM().r[0] ,dPoint.y * 0.005f);
					tm = XMMatrixMultiply( tm, rotTM );
				}

				tm = XMMatrixMultiply( tm, entityTM );
				pCamera->SetWorldTM( tm );
			}
		}
		else if( event.RightIsDown() )
		{
			pCamera->MoveOnLocalAxis( 0 , 0,  dPoint.y * m_CameraSpeed );
		}
		else if( event.MiddleIsDown() )
		{
			pCamera->MoveOnLocalAxis( -dPoint.x * m_CameraSpeed , dPoint.y * m_CameraSpeed, 0 );
		}
	}
}