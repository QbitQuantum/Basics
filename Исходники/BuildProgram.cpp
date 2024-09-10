BOOL CBuildProgram::UpdatedDbCheckSumInfo(PSNODEINFO psInfo)
{
    ICluster* pCluster = nullptr;
    m_pGlobalObj->m_ouClusterConfig->GetDBService(m_eBus, 0, 0, &pCluster);
    if (nullptr != pCluster)
    {
        std::string strChecksum;
        pCluster->GetDBFileChecksum(strChecksum);
        psInfo->m_ouLastDBChecksum = _strtoui64(strChecksum.c_str(), nullptr, 16);
    }

    return TRUE;
}