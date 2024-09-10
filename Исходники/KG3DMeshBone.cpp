HRESULT KG3DMeshBone::AddSubMesh(D3DXVECTOR3 v1, D3DXVECTOR3 v2, TCHAR* szBoneName, DWORD dwType)
{
    HRESULT hResult  = E_FAIL;

    _SubMeshInfo subMeshInfo;
    D3DXVECTOR3  vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    D3DXVECTOR3  vDir = v2 - v1;
    D3DXVECTOR3  vVer;
    D3DXVECTOR3  vHor;
    D3DXMATRIX   matRotation;
    FLOAT        fAngel = 0;
    FLOAT        fLen   = 0;

    ASSERT(szBoneName);

    fLen = D3DXVec3Length(&vDir);
    D3DXVec3Normalize(&vDir, &vDir);
    fAngel = D3DXVec3Dot(&vUp, &vDir);

    if (abs(acosf(fAngel)) <= 0.05f)
    {
        vVer = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
        vHor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
    }
    else
    {
        D3DXMatrixRotationY(&matRotation, D3DX_PI /2);
        D3DXVec3TransformNormal(&vVer, &vDir, &matRotation);

        D3DXVec3Cross(&vHor, &vDir, &vVer);
        D3DXVec3Cross(&vVer, &vDir, &vHor);
    }

    D3DXVec3Normalize(&vVer, &vVer);
    D3DXVec3Normalize(&vHor, &vHor);

    switch (dwType)
    {
    case 1 :
        vVer *= fLen / 2;
        vHor *= fLen / 2;
        subMeshInfo.vPosition[0] = v2;
        subMeshInfo.vPosition[1] = v1 + (vDir * fLen) - vHor - vVer;
        subMeshInfo.vPosition[2] = v1 + (vDir * fLen) + vHor - vVer;
        subMeshInfo.vPosition[3] = v1 + (vDir * fLen) + vHor + vVer;
        subMeshInfo.vPosition[4] = v1 + (vDir * fLen) - vHor + vVer;
        subMeshInfo.vPosition[5] = v1;
        break;
    case 0 :
        vVer *= fLen / 15;
        vHor *= fLen / 15;
        subMeshInfo.vPosition[0] = v2;
        subMeshInfo.vPosition[1] = v1 + (vDir * fLen / 15) - vHor - vVer;
        subMeshInfo.vPosition[2] = v1 + (vDir * fLen / 15) + vHor - vVer;
        subMeshInfo.vPosition[3] = v1 + (vDir * fLen / 15) + vHor + vVer;
        subMeshInfo.vPosition[4] = v1 + (vDir * fLen / 15) - vHor + vVer;
        subMeshInfo.vPosition[5] = v1;
        break;
    case 2 :
        vVer *= fLen / 15;
        vHor *= fLen / 15;
        subMeshInfo.vPosition[0] = v2;
        subMeshInfo.vPosition[1] = v1 + (vDir * fLen / 2) - vHor - vVer;
        subMeshInfo.vPosition[2] = v1 + (vDir * fLen / 2) + vHor - vVer;
        subMeshInfo.vPosition[3] = v1 + (vDir * fLen / 2) + vHor + vVer;
        subMeshInfo.vPosition[4] = v1 + (vDir * fLen / 2) - vHor + vVer;
        subMeshInfo.vPosition[5] = v1;
        break;
    default :
        KG_PROCESS_ERROR(0);
        break;
    }

    subMeshInfo.dwIndex[0]   = 0;
    subMeshInfo.dwIndex[1]   = 3;
    subMeshInfo.dwIndex[2]   = 4;

    subMeshInfo.dwIndex[3]   = 0;
    subMeshInfo.dwIndex[4]   = 2;
    subMeshInfo.dwIndex[5]   = 3;

    subMeshInfo.dwIndex[6]   = 0;
    subMeshInfo.dwIndex[7]   = 1;
    subMeshInfo.dwIndex[8]   = 2;

    subMeshInfo.dwIndex[9]   = 0;
    subMeshInfo.dwIndex[10]  = 4;
    subMeshInfo.dwIndex[11]  = 1;

   /* subMeshInfo.dwIndex[12]  = 1;
    subMeshInfo.dwIndex[13]  = 4;
    subMeshInfo.dwIndex[14]  = 2;

    subMeshInfo.dwIndex[15]  = 2;
    subMeshInfo.dwIndex[16]  = 4;
    subMeshInfo.dwIndex[17]  = 3;*/

    subMeshInfo.dwIndex[12]   = 5;
    subMeshInfo.dwIndex[13]   = 4;
    subMeshInfo.dwIndex[14]   = 3;

    subMeshInfo.dwIndex[15]   = 5;
    subMeshInfo.dwIndex[16]   = 3;
    subMeshInfo.dwIndex[17]   = 2;

    subMeshInfo.dwIndex[18]   = 5;
    subMeshInfo.dwIndex[19]   = 2;
    subMeshInfo.dwIndex[20]   = 1;

    subMeshInfo.dwIndex[21]   = 5;
    subMeshInfo.dwIndex[22]   = 1;
    subMeshInfo.dwIndex[23]   = 4;

    subMeshInfo.dwType = dwType;
    strncpy(subMeshInfo.szBoneName, szBoneName, sizeof(subMeshInfo.szBoneName));
    m_vecSubMeshInfo.push_back(subMeshInfo);

    hResult = S_OK;
Exit0:
    return hResult;
}