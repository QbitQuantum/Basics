bool ShmemOutputStreamImpl::Resize(int newsize)
{
    ++m_ResizeNum;

    //printf("output stream resize %d to %d\n", m_ResizeNum, newsize);
    //fflush(stdout);

    ACE_Shared_Memory* pNewMap;

    m_pHeader->resize = true;
    m_pHeader->newsize = newsize;

#ifdef ACE_LACKS_SYSV_SHMEM

    char file_path[1024];

    if (ACE::get_temp_dir(file_path, 1024) == -1) {
        yError("ShmemHybridStream: no temp directory found.");
        return false;
    }

    char file_name[1024];
    sprintf(file_name, "%sSHMEM_FILE_%d_%d", file_path, m_Port, m_ResizeNum);

    pNewMap = new ACE_Shared_Memory_MM(file_name, //const ACE_TCHAR *filename,
                                       newsize + sizeof(ShmemHeader_t), //int len = -1,
                                       O_RDWR | O_CREAT, //int flags = O_RDWR | O_CREAT,
                                       ACE_DEFAULT_FILE_PERMS, //int mode = ACE_DEFAULT_FILE_PERMS,
                                       PROT_RDWR, //int prot = PROT_RDWR,
                                       ACE_MAP_SHARED); //int share = ACE_MAP_PRIVATE,

#else

    int shmemkey = (m_ResizeNum << 16) + m_Port;

    pNewMap = new ACE_Shared_Memory_SV(shmemkey, newsize + sizeof(ShmemHeader_t), ACE_Shared_Memory_SV::ACE_CREATE);

#endif

    if (!pNewMap) {
        yError("ShmemOutputStream can't create shared memory");
        return false;
    }

    ShmemHeader_t* pNewHeader = (ShmemHeader_t*)pNewMap->malloc();
    char* pNewData = (char*)(pNewHeader + 1);

    pNewHeader->size = newsize;
    pNewHeader->resize = false;
    pNewHeader->close = m_pHeader->close;

    pNewHeader->tail = 0;
    pNewHeader->head = pNewHeader->avail = m_pHeader->avail;
    pNewHeader->waiting = m_pHeader->waiting;

    if (m_pHeader->avail) {
        // one or two blocks in circular queue?
        if (m_pHeader->tail < m_pHeader->head) {
            memcpy(pNewData, m_pData + m_pHeader->tail, m_pHeader->avail);
        } else {
            int firstchunk = m_pHeader->size - m_pHeader->tail;
            memcpy(pNewData, m_pData + m_pHeader->tail, firstchunk);
            memcpy(pNewData + firstchunk, m_pData, m_pHeader->head);
        }
    }

    m_pMap->close();
    delete m_pMap;
    m_pMap = pNewMap;

    m_pHeader = pNewHeader;
    m_pData = pNewData;

    return true;
}