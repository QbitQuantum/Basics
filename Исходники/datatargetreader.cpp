HRESULT DataTargetReader::Read(TargetObject* pTargetObject)
{
    ULONG32 previousAlign = m_currentStructureAlign;
    m_currentStructureAlign = 1;
    HRESULT hr = pTargetObject->ReadFrom(*this);
    if (SUCCEEDED(hr))
    {
        // increase the structure size to a multiple of the maximum alignment of any of its members
        Align(m_currentStructureAlign);
    }
    m_currentStructureAlign = MAX(previousAlign, m_currentStructureAlign);
    return hr;
}