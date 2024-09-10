//--------------------------------------------------------------------------------------
// Name: ComputeMeshBoundingBox()
// Desc: Calculate the bounding box of the transformed mesh.
//--------------------------------------------------------------------------------------
VOID Mesh::ComputeMeshBoundingBox( MESH_DATA* pMesh, const XMMATRIX mat,
                                   XMVECTOR& vMin, XMVECTOR& vMax )
{
    // Initialize bounds to be reset on the first point
    vMin.x = vMin.y = vMin.z = +FLT_MAX;
    vMax.x = vMax.y = vMax.z = -FLT_MAX;

    DWORD dwNumVertices = pMesh->m_dwNumVertices;
    DWORD dwVertexSize = pMesh->m_dwVertexSize;

    BYTE* pVertexData;
    pMesh->m_VB.Lock( 0, 0, ( VOID** )&pVertexData, D3DLOCK_READONLY );

    while( dwNumVertices-- )
    {
        XMFLOAT3* pVertex = ( XMFLOAT3* )pVertexData;
        XMVECTOR vPos = XMVectorSet( pVertex->x, pVertex->y, pVertex->z, 0 );
        vPos = XMVector3TransformCoord( vPos, mat );

        UnionBox( vMin, vMax, vPos, vPos );  // Expand the bounding box to include the point
        pVertexData += dwVertexSize;
    }
    pMesh->m_VB.Unlock();
}