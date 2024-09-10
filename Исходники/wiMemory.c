// ================================================================================================
// FUNCTION  : wiMemory_Check()
// ------------------------------------------------------------------------------------------------
// ================================================================================================
wiStatus wiMemory_Check(char *Filename, int Line)
{
    STATUS( wiProcess_WaitForMutex(&TraceMemoryMutex) );
    {
        wiMemory_traceMem_t *item = traceMemList;
        unsigned long total = 0;

        wiUtil_WriteLogFile("wiMemory_Check() called from %s line %d in thread %d\n",
            Filename, Line, wiProcess_ThreadIndex() );

        if (traceMemList)
        {
            while (item)
            {
                XSTATUS( wiMemory_CheckTraceBlock(item) )
                total += item->size;
                item = item->next;
            }
            wiUtil_WriteLogFile("    Total Allocated Memory: %d bytes\n",total);
        }
        #ifdef WIN32
        {
            int heapstatus = _heapchk();
            switch (heapstatus)
            {
                case _HEAPOK      : wiUtil_WriteLogFile("    HEAP CHECK: OK - heap is okay\n"); break;
                case _HEAPEMPTY   : wiUtil_WriteLogFile("    HEAP CHECK: OK - heap is empty\n"); break;
                case _HEAPBADBEGIN: wiUtil_WriteLogFile("    HEAP CHECK: ERROR - bad start of heap\n"); break;
                case _HEAPBADNODE : wiUtil_WriteLogFile("    HEAP CHECK: ERROR - bad node in heap\n"); break;
                default           : wiUtil_WriteLogFile("    HEAP CHECK: UNKNOWN STATUS %d\n",heapstatus);
            }
        }
        #endif
    }
    STATUS( wiProcess_ReleaseMutex(&TraceMemoryMutex) );
    return WI_SUCCESS;
}