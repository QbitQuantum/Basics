//-------------------------------------------------------------------------------------------------
HRESULT ImageShader2D::Start()
{
    ALVR_RESULT res = ALVR_OK;

    if (m_bShaderReady)
    {
        // read shader in memory
        FILE *file = NULL;
        _wfopen_s(&file, m_pFileNameBin, L"rb");
        if (file == NULL)
        {
            return E_FAIL;
        }
        fseek(file, 0, SEEK_END);
        int fileSize = ftell(file);
        fseek(file, 0, SEEK_SET);
        unsigned char * pShader = new unsigned char[fileSize];
        fread(pShader, 1, fileSize, file);
        fclose(file);

        res = m_pComputeContext->CreateComputeTask(ALVR_SHADER_MODEL_D3D11, 0, pShader, fileSize, &m_pShader);

        delete[] pShader;

        if (m_pFence != NULL)
        {
            m_pFence->Release();
            m_pFence = NULL;
        }
        m_pApplicationContext->m_pLiquidVrDevice->CreateFence(&m_pFence);
    }
    else
    {
        m_bDelayedStart = true;
    }
    return S_OK;
}