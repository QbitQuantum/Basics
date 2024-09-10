    void DXCamera2D::VSetOrthoRHOffCenter(OrthoRect rect, float zNear, float zFar)
    {
        m_rect = rect;

        XMMATRIX P = XMMatrixOrthographicOffCenterRH(rect.left, rect.right, rect.bottom, rect.top, zNear, zFar);
        XMStoreFloat4x4(&m_projection, XMMatrixTranspose(P));
    }