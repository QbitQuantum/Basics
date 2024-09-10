HANDLE MicroMockCreateGlobalSemaphore(const char* name, unsigned int highWaterCount)
{
    WCHAR temp[MAX_PATH]; 
    if(MultiByteToWideChar(CP_ACP, 0, name, -1, temp,MAX_PATH)==0)
    {
        return NULL;
    }
    else
    {
        return CreateSemaphoreW(NULL, highWaterCount,highWaterCount, temp);
    }
}