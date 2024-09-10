HRESULT CCImageList::GetImageInfo(int i, IMAGEINFO* pii)
{
    ImageList_GetImageInfo(m_hImageList, i, pii);
    return E_FAIL;
}