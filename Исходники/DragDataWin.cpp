unsigned DragData::numberOfFiles() const
{
#if USE(CF)
    if (!m_platformDragData)
        return 0;

    STGMEDIUM medium;
    if (FAILED(m_platformDragData->GetData(cfHDropFormat(), &medium)))
        return 0;

    HDROP hdrop = static_cast<HDROP>(GlobalLock(medium.hGlobal));

    if (!hdrop)
        return 0;

    unsigned numFiles = DragQueryFileW(hdrop, 0xFFFFFFFF, 0, 0);

    DragFinish(hdrop);
    GlobalUnlock(medium.hGlobal);

    return numFiles;
#else
    return 0;
#endif
}