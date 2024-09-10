static void __cdecl CrtDoForAllClientObjects_thunk(void *pData, void *pContext)
{
    _PHEAP_m pFunc = (_PHEAP_m) DecodePointer(__pfnHeapfunc);

    if (pFunc)
    {
        pFunc(pData, pContext);
    }
}