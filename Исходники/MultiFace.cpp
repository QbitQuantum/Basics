void MultiFace::UninitInstance()
{
    // Clean up the memory allocated for Face Tracking and rendering.
    m_FTHelper.Stop();

    if (m_hAccelTable)
    {
        DestroyAcceleratorTable(m_hAccelTable);
        m_hAccelTable = NULL;
    }

    DestroyWindow(m_hWnd);
    m_hWnd = NULL;

    if (m_pImageBuffer)
    {
        for (UINT i=0; i<m_nbUsers; i++)
        {
            if (m_pImageBuffer[i])
            {
                m_pImageBuffer[i]->Release();
                m_pImageBuffer[i] = NULL;
            }
        }
        delete[] m_pImageBuffer;
    }

    if (m_pVideoBuffer)
    {
        m_pVideoBuffer->Release();
        m_pVideoBuffer = NULL;
    }

    if (m_eggavatar)
    {
        delete[] m_eggavatar;
    }
}