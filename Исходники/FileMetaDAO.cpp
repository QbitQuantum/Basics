ReturnStatus
FileMetaDAO::statDir(const std::string &path, FileMeta *pMeta)
{
    assert(pMeta);

    Channel* pDataChannel = ChannelManager::getInstance()->Mapping(m_BucketId);
	NameSpace *DataNS = pDataChannel->m_DataNS;

    int rt = 0;
    int error = 0;

	FileAttr st;
	rt = DataNS->Stat(path.c_str(), &st);

    if (-1 == rt) {
        error = errno;
        ERROR_LOG("path %s, stat() error, %s.", path.c_str(), strerror(error));

        if (ENOENT == error || ENOTDIR == error) {
            return checkPrefix(path);

        } else {
            return ReturnStatus(MU_FAILED, MU_UNKNOWN_ERROR);
        }
    }

    if (st.m_Type != MU_DIRECTORY) {
        ERROR_LOG("path %s, not directory", path.c_str());
        return ReturnStatus(MU_FAILED, NOT_DIRECTORY);
    }

    pMeta->m_Attr.m_Mode = st.m_Mode;
    pMeta->m_Attr.m_CTime = st.m_CTime;
    pMeta->m_Attr.m_MTime = st.m_MTime;
    pMeta->m_Attr.m_Size = st.m_Size;

    return ReturnStatus(MU_SUCCESS);
}