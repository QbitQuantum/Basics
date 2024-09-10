void TextureWave::BuildParamaters()
{
    m_constBufferPerObj.Create(m_d3dDevice, VertexShaer, 0);
    m_constMaterial.Create(m_d3dDevice, PixelShader, 0);
    m_constBufferPerFrame.Create(m_d3dDevice, PixelShader, 1);
    m_constPixelParam.Create(m_d3dDevice, PixelShader, 2);

    m_landMat.Ambient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
    m_landMat.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    m_landMat.Specular = XMFLOAT4(0.2f, 0.2f, 0.2f, 16.0f);

    m_waveMat.Ambient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
    m_waveMat.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 0.5f);
    m_waveMat.Specular = XMFLOAT4(0.8f, 0.8f, 0.8f, 32.0f);

    m_boxMat.Ambient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
    m_boxMat.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    m_boxMat.Specular = XMFLOAT4(0.4f, 0.4f, 0.4f, 16.0f);

    for (UINT i = 0; i < 4; ++i)
    {
        m_blendFactor[i] = 0.0f;
    }

    m_waveSpeed = 0.0002f;

    m_grassTextureMatrix = XMMatrixScaling(5.0f, 5.0f, 1.0f);

    texCoords[0] = { 0.0f, 0.0f };
    texCoords[1] = { 1.0f, 0.0f };
    texCoords[2] = { 0.0f, 1.0f };
    texCoords[3] = { 1.0f, 1.0f };

    m_constBufferPerFrameReflect.GlobalLight[0].Ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
    m_constBufferPerFrameReflect.GlobalLight[0].Diffuse = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
    m_constBufferPerFrameReflect.GlobalLight[0].Specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
    m_constBufferPerFrameReflect.GlobalLight[0].Direction = XMFLOAT3(0.57735f, -0.57735f, 0.57735f);

    m_constBufferPerFrameReflect.GlobalLight[1].Ambient = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
    m_constBufferPerFrameReflect.GlobalLight[1].Diffuse = XMFLOAT4(0.20f, 0.20f, 0.20f, 1.0f);
    m_constBufferPerFrameReflect.GlobalLight[1].Specular = XMFLOAT4(0.25f, 0.25f, 0.25f, 1.0f);
    m_constBufferPerFrameReflect.GlobalLight[1].Direction = XMFLOAT3(-0.57735f, -0.57735f, 0.57735f);

    m_constBufferPerFrameReflect.GlobalLight[2].Ambient = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
    m_constBufferPerFrameReflect.GlobalLight[2].Diffuse = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
    m_constBufferPerFrameReflect.GlobalLight[2].Specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
    m_constBufferPerFrameReflect.GlobalLight[2].Direction = XMFLOAT3(0.0f, -0.707f, -0.707f);

    m_boxWorldMatrix = XMMatrixScaling(5.0f, 5.0f, 5.0f);
}