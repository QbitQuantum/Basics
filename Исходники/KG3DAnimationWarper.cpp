HRESULT KG3DAnimationWarper::Helper_LoadBipExtraInfo(IFile *pFile)
{
    HRESULT hr = E_FAIL;
    unsigned long uSize = 0;
    KG3DSkeleton::SerializeData Data;
    m_BoneMatchTable.clear();

    KG_PROCESS_ERROR(pFile);

    uSize = pFile->Read(&Data, sizeof(KG3DSkeleton::SerializeData));
    KGLOG_PROCESS_ERROR(uSize == sizeof(KG3DSkeleton::SerializeData));

    KG_PROCESS_ERROR(Data.dwMask == KG3DSkeleton::SerializeData::cdwMask);
    KG_PROCESS_ERROR(Data.dwNumBones == static_cast<DWORD>(m_Skeleton.GetNumBones()));

    m_BoneMatchTable.resize(Data.dwNumBones);
    for (size_t i = 0; i < m_BoneMatchTable.size(); i++)
    {
        TCHAR strBoneName[MAX_BONE_NAME_LENGTH];

        uSize = pFile->Read(strBoneName, sizeof(TCHAR) * MAX_BONE_NAME_LENGTH);
        KGLOG_PROCESS_ERROR(uSize == sizeof(TCHAR) * MAX_BONE_NAME_LENGTH);
		_strlwr_s(strBoneName, MAX_BONE_NAME_LENGTH);
        int nIndex = m_Skeleton.FindBone(strBoneName);
        m_BoneMatchTable[i] = nIndex;
    }
    hr = S_OK;
Exit0:
    return hr;
}