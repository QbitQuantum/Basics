HRESULT CeeFileGenWriter::setLibraryGuid(LPWSTR libraryGuid)
{
    return IIDFromString(libraryGuid, &m_libraryGuid);
} // HRESULT CeeFileGenWriter::setLibraryGuid()