VOID DebugDraw::DrawFrustum( const Frustum& frustum, D3DCOLOR Color )
{
    // compute corner points

    XMVECTOR Origin = XMVectorSet( frustum.Origin.x, frustum.Origin.y, frustum.Origin.z, 0 );
    FLOAT Near = frustum.Near;
    FLOAT Far = frustum.Far;
    FLOAT RightSlope = frustum.RightSlope;
    FLOAT LeftSlope = frustum.LeftSlope;
    FLOAT TopSlope = frustum.TopSlope;
    FLOAT BottomSlope = frustum.BottomSlope;

    XMFLOAT3 CornerPoints[8];
    CornerPoints[0] = XMFLOAT3( RightSlope * Near, TopSlope * Near, Near );
    CornerPoints[1] = XMFLOAT3( LeftSlope * Near, TopSlope * Near, Near );
    CornerPoints[2] = XMFLOAT3( LeftSlope * Near, BottomSlope * Near, Near );
    CornerPoints[3] = XMFLOAT3( RightSlope * Near, BottomSlope * Near, Near );

    CornerPoints[4] = XMFLOAT3( RightSlope * Far, TopSlope * Far, Far );
    CornerPoints[5] = XMFLOAT3( LeftSlope * Far, TopSlope * Far, Far );
    CornerPoints[6] = XMFLOAT3( LeftSlope * Far, BottomSlope * Far, Far );
    CornerPoints[7] = XMFLOAT3( RightSlope * Far, BottomSlope * Far, Far );

    XMVECTOR Orientation = XMLoadFloat4( &frustum.Orientation );
    XMMATRIX Mat = XMMatrixRotationQuaternion( Orientation );
    for( UINT i = 0; i < 8; i++ )
    {
        XMVECTOR Result = XMVector3Transform( XMLoadFloat3( &CornerPoints[i] ), Mat );
        Result = XMVectorAdd( Result, Origin );
        XMStoreFloat3( &CornerPoints[i], Result );
    }

    XMFLOAT3 Lines[12 * 2];

    Lines[0] = CornerPoints[0];
    Lines[1] = CornerPoints[1];
    Lines[2] = CornerPoints[1];
    Lines[3] = CornerPoints[2];
    Lines[4] = CornerPoints[2];
    Lines[5] = CornerPoints[3];
    Lines[6] = CornerPoints[3];
    Lines[7] = CornerPoints[0];

    Lines[8] = CornerPoints[0];
    Lines[9] = CornerPoints[4];
    Lines[10] = CornerPoints[1];
    Lines[11] = CornerPoints[5];
    Lines[12] = CornerPoints[2];
    Lines[13] = CornerPoints[6];
    Lines[14] = CornerPoints[3];
    Lines[15] = CornerPoints[7];

    Lines[16] = CornerPoints[4];
    Lines[17] = CornerPoints[5];
    Lines[18] = CornerPoints[5];
    Lines[19] = CornerPoints[6];
    Lines[20] = CornerPoints[6];
    Lines[21] = CornerPoints[7];
    Lines[22] = CornerPoints[7];
    Lines[23] = CornerPoints[4];

    // draw frustum

    SimpleShaders::SetDeclPos();
    SimpleShaders::BeginShader_Transformed_ConstantColor( g_matViewProjection, Color );
    g_pd3dDevice->DrawPrimitiveUP( D3DPT_LINELIST, 12, Lines, sizeof( XMFLOAT3 ) );
    SimpleShaders::EndShader();
}