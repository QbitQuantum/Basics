/////////////////////////////////////////////////////////////
//
// CAdditionalVertexStreamManager::UpdateAdditionalStreamContent
//
// Generate data in the additional stream
//
/////////////////////////////////////////////////////////////
bool CAdditionalVertexStreamManager::UpdateAdditionalStreamContent ( SCurrentStateInfo& state, SAdditionalStreamInfo* pAdditionalInfo, uint ReadOffsetStart, uint ReadSize, uint WriteOffsetStart, uint WriteSize )
{
    //HRESULT hr;
    IDirect3DVertexBuffer9* pStreamDataPT = state.stream1.pStreamData;
    IDirect3DVertexBuffer9* pStreamDataN = pAdditionalInfo->pStreamData;
    uint StridePT = 20;
    uint StrideN = 12;
    uint NumVerts = ReadSize / StridePT;
    assert ( NumVerts == WriteSize / StrideN );

    // Get the source vertex bytes
    std::vector < uchar > sourceArray;
    sourceArray.resize ( ReadSize );
    uchar* pSourceArrayBytes = &sourceArray[0];
    {
        void* pVertexBytesPT = NULL;
        if ( FAILED( pStreamDataPT->Lock ( ReadOffsetStart, ReadSize, &pVertexBytesPT, D3DLOCK_NOSYSLOCK | D3DLOCK_READONLY ) ) )
            return false;
        memcpy ( pSourceArrayBytes, pVertexBytesPT, ReadSize );
        pStreamDataPT->Unlock ();
    }

    // Create dest byte buffer
    std::vector < uchar > destArray;
    destArray.resize ( WriteSize );
    uchar* pDestArrayBytes = &destArray[0];

    // Compute dest bytes
    {
        // Get index buffer
        if ( FAILED( m_pDevice->GetIndices( &state.pIndexData ) ) )
            return false;

        // Get index buffer desc
        D3DINDEXBUFFER_DESC IndexBufferDesc;
        state.pIndexData->GetDesc ( &IndexBufferDesc );

        uint numIndices = state.args.primCount + 2;
        uint step = 1;
        if ( state.args.PrimitiveType == D3DPT_TRIANGLELIST )
        {
            numIndices = state.args.primCount * 3;
            step = 3;
        }
        assert ( IndexBufferDesc.Size >= ( numIndices + state.args.startIndex ) * 2 );

        // Get index buffer data
        std::vector < uchar > indexArray;
        indexArray.resize ( ReadSize );
        uchar* pIndexArrayBytes = &indexArray[0];
        {
            void* pIndexBytes = NULL;
            if ( FAILED( state.pIndexData->Lock ( state.args.startIndex*2, numIndices*2, &pIndexBytes, D3DLOCK_NOSYSLOCK | D3DLOCK_READONLY ) ) )
                return false;
            memcpy ( pIndexArrayBytes, pIndexBytes, numIndices*2 );
            state.pIndexData->Unlock ();
        }

        // Calc normals
        std::vector < CVector > NormalList;
        NormalList.insert ( NormalList.end (), NumVerts, CVector () );

        std::map < long long, CVector > doneTrisMap;

        // For each triangle
        for ( uint i = 0 ; i < numIndices - 2 ; i += step )
        {
            // Get triangle vertex indici
            WORD v0 = ((WORD*)pIndexArrayBytes)[ i ];
            WORD v1 = ((WORD*)pIndexArrayBytes)[ i + 1 ];
            WORD v2 = ((WORD*)pIndexArrayBytes)[ i + 2 ];

            if ( v0 >= NumVerts || v1 >= NumVerts || v2 >= NumVerts )
                continue;   // vert index out of range

            if ( v0 == v1 || v0 == v2 || v1 == v2 )
                continue;   // degenerate tri

            // Get vertex positions from original stream
            CVector* pPos0 = (CVector*)( pSourceArrayBytes + v0 * 20 );
            CVector* pPos1 = (CVector*)( pSourceArrayBytes + v1 * 20 );
            CVector* pPos2 = (CVector*)( pSourceArrayBytes + v2 * 20 );

            // Calculate the normal
            CVector Dir1 = *pPos2 - *pPos1;
            CVector Dir2 = *pPos0 - *pPos1;

            CVector Normal = Dir1;
            Normal.CrossProduct ( &Dir2 );
            Normal.Normalize ();

            // Flip normal if triangle was flipped
            if ( state.args.PrimitiveType == D3DPT_TRIANGLESTRIP && ( i & 1 ) )
                Normal = -Normal;

            // Try to improve results by ignoring duplicated triangles
            long long key = getTriKey ( v0, v1, v2 );
            if ( CVector* pDoneTriPrevNormal = MapFind ( doneTrisMap, key ) )
            {
                // Already done this tri - Keep prev tri if it has a better 'up' rating
                if ( pDoneTriPrevNormal->fZ > Normal.fZ )
                    continue;

                // Remove effect of prev tri
                NormalList[ v0 ] -= *pDoneTriPrevNormal;
                NormalList[ v1 ] -= *pDoneTriPrevNormal;
                NormalList[ v2 ] -= *pDoneTriPrevNormal;
            }
            MapSet ( doneTrisMap, key, Normal );

            // Add normal weight to used vertices
            NormalList[ v0 ] += Normal;
            NormalList[ v1 ] += Normal;
            NormalList[ v2 ] += Normal;
        }

        // Validate normals and set dest data
        for ( uint i = 0 ; i < NumVerts ; i++ )
        {
            // Validate
            CVector& Normal = NormalList[i];
            if ( Normal.Normalize () < FLOAT_EPSILON )
                Normal = CVector ( 0, 0, 1 );

            // Set
            CVector* pNormal = (CVector*)( pDestArrayBytes + i * 12 );
            *pNormal = Normal;
        }
    }

    // Set the dest bytes
    {
        void* pVertexBytesN = NULL;
        if ( FAILED( pStreamDataN->Lock ( WriteOffsetStart, WriteSize, &pVertexBytesN, D3DLOCK_NOSYSLOCK ) ) )
            return false;
        memcpy ( pVertexBytesN, pDestArrayBytes, WriteSize );
        pStreamDataN->Unlock ();
    }

    return true;
}