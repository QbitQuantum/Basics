XCODE_IPC_DESCR_T *xcode_ipc_open(unsigned int sz, key_t key) {
  XCODE_IPC_DESCR_T *pIpc = NULL;

  pIpc = avc_calloc(1, sizeof(XCODE_IPC_DESCR_T));
  pIpc->sz = sz;

  if((pIpc->hFile = OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, 
                                    XCODE_FILE_MAPPING_NAME)) == NULL) {

    LOG(X_ERROR("OpenFileMapping %s failed (error:%d)"),  
                XCODE_FILE_MAPPING_NAME, GetLastError());
    xcode_ipc_close(pIpc);
    return NULL;
  }

  if((pIpc->pmem = MapViewOfFile(pIpc->hFile, FILE_MAP_ALL_ACCESS, 0, 0, pIpc->sz)) == NULL) {
    LOG(X_ERROR("MapViewOfFile %s failed (error:%d)"),  
                XCODE_FILE_MAPPING_NAME, GetLastError());
    xcode_ipc_close(pIpc);
    return NULL;
  }

  if((pIpc->hSemSrv = OpenSemaphoreA(SYNCHRONIZE | SEMAPHORE_MODIFY_STATE, 
                                    FALSE, XCODE_SEM_SRV_NAME)) == NULL) {
    LOG(X_ERROR("OpenSemaphore %s failed (error:%d)"), XCODE_SEM_SRV_NAME, GetLastError());
    xcode_ipc_close(pIpc);
    return NULL;
  }

  if((pIpc->hSemCli = OpenSemaphoreA(SYNCHRONIZE | SEMAPHORE_MODIFY_STATE, 
                                    FALSE, XCODE_SEM_CLI_NAME)) == NULL) {
    LOG(X_ERROR("OpenSemaphore %s failed (error:%d)"), XCODE_SEM_CLI_NAME, GetLastError());
    xcode_ipc_close(pIpc);
    return NULL;
  }

  pIpc->pmem->hdr.cmd = XCODE_IPC_CMD_NONE;

  return pIpc;
}