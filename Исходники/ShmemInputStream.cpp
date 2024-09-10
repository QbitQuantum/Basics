bool ShmemInputStreamImpl::Resize()
{
	++m_ResizeNum;

	ACE_Shared_Memory* pNewMap;

	//printf("input stream resize %d to %d\n",m_ResizeNum,m_pHeader->newsize);
	//fflush(stdout);

#ifdef ACE_LACKS_SYSV_SHMEM

	char file_path[1024];

	if (ACE::get_temp_dir(file_path,1024)==-1)
	{
		YARP_ERROR(Logger::get(),"ShmemHybridStream: no temp directory found.");
		return false;
	}

	char file_name[1024];
	sprintf(file_name,"%sSHMEM_FILE_%d_%d",file_path,m_Port,m_ResizeNum);

	pNewMap=new ACE_Shared_Memory_MM(file_name, //const ACE_TCHAR *filename,
		m_pHeader->newsize+sizeof(ShmemHeader_t), //int len = -1,
		O_RDWR, //int flags = O_RDWR | O_CREAT,
		ACE_DEFAULT_FILE_PERMS, //int mode = ACE_DEFAULT_FILE_PERMS,
		PROT_RDWR, //int prot = PROT_RDWR,
		ACE_MAP_SHARED); //int share = ACE_MAP_PRIVATE,

#else

	int shmemkey=(m_ResizeNum<<16)+m_Port;

	pNewMap=new ACE_Shared_Memory_SV(shmemkey,m_pHeader->size+sizeof(ShmemHeader_t));

#endif

	if (!pNewMap)
	{
		YARP_ERROR(Logger::get(),String("ShmemOutputStream can't create shared memory"));
		return false;
	}

	ShmemHeader_t *pNewHeader=(ShmemHeader_t*)pNewMap->malloc();
	char *pNewData=(char*)(pNewHeader+1);

	m_pMap->close();
	delete m_pMap;

	m_pMap=pNewMap;
	m_pHeader=pNewHeader;
	m_pData=pNewData;

	return true;
}