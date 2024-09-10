void MemoryMapView_DoneBitmap()
{
    if (m_hMemoryMapBitmap != NULL)
    {
        DeleteObject(m_hMemoryMapBitmap);  m_hMemoryMapBitmap = NULL;
    }

    DrawDibClose( m_hMemoryMapDrawDib );
}