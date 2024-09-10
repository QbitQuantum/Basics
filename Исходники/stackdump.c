/*-----------------------------------------------------------------------------
    Name        : llSystemsShutdown
    Description : Shut down systems required by the system
    Inputs      :
    Outputs     :
    Return      :
----------------------------------------------------------------------------*/
void llSystemsShutdown(void)
{
    //memory
    GlobalFree(utyMemoryHeap);
}