/*----------------------------------------------------------------------*
                            rtp_thread_kill
 *----------------------------------------------------------------------*/
int rtp_thread_kill (RTP_HANDLE         * newThread,
                      RTP_ENTRY_POINT_FN   entryPoint,
                      const char         * name,
                      int                  stackSizeIndex,
                      int                  priorityIndex,
                      void               * userData)
{
    int * index = (int *) userData;
    
    if ((rtp_strcmp(name, "ip interpret") == 0) && IPTaskInitialized[*index])
    {
        IPTaskInitialized[*index] = 0;

        IPTaskContinuation[*index].Abort();
    }
    
    else if ((rtp_strcmp(name, "timer comp") == 0) && TimerTaskCompInitialized)
    {
        TimerTaskCompInitialized = 0;
        
        TimerTaskCompletion.Abort();
    }       
    
    else if ((rtp_strcmp(name, "timer cont") == 0) && TimerTaskContInitialized)
    {      
        TimerTaskContInitialized = 0;

        TimerTaskContinuation.Abort();
    } 
    
    else if ((rtp_strcmp(name, "interrupt task") == 0) && InterruptTaskContInitialized[*index])
    {
        InterruptTaskContInitialized[*index] = 0;
        
        InterruptTaskContinuation[*index].Abort();
    }
    
    else if ((rtp_strcmp(name, "dhcp") == 0) && DHCPTaskInitialized)
    {
        DHCPTaskInitialized = 0;
        
        DHCPTaskContinuation.Abort();
    }
    
    return (0);    
}