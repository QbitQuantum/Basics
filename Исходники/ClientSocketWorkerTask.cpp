bool ClientSocketWorkerTask::run()
{
    CommonFunctions::SetThreadName("ClientSocketWorkerTask thread");

    //open file per thread - read only
    IOHandleGuard rIOHandleGuard(m_rDataFileHandle);
    m_rDataFileHandle = IO::fopen(m_rStorage.m_rDataPath.c_str(), IO::IO_READ_ONLY, IO::IO_DIRECT);
    if(m_rDataFileHandle == INVALID_HANDLE_VALUE)
    {
        Log.Error(__FUNCTION__, "Cannot open data file: %s", m_rStorage.m_rDataPath.c_str());
        return true;
    }
    
    try
    {
#ifdef WIN32
        _set_se_translator(trans_func);
#endif
        
        //main thread loop
        while(m_threadRunning)
        {
            ClientSocketTaskData rTaskData;
            //get task data from queue
            if(m_rTaskDataQueue.get(rTaskData, g_cfg.TaskQueueTimeout))
            {
                //process task
                if(rTaskData.m_opcode < OP_NUM && m_ClientSocketWorkerTaskHandlers[rTaskData.m_opcode] != NULL)
                {
                    Log.Debug(__FUNCTION__, "Processing packet opcode: (0x%.4X)", rTaskData.m_opcode);
                    (void)(this->*m_ClientSocketWorkerTaskHandlers[rTaskData.m_opcode])(rTaskData);
                }
                else
                {
                    Log.Warning(__FUNCTION__, "Unknown opcode (0x%.4X)", rTaskData.m_opcode);
                }
                
                //dealloc task data
                bbuff_destroy(rTaskData.m_pData);
            }
            
            //check memory
            m_rStorage.CheckMemory(*m_pLRUCache);
        }
    }
    catch(...)
    {
        Log.Error(__FUNCTION__, "Fatal error stopping server.");
        g_stopEvent = true;
    }

    return true;
}