void CWE122_Heap_Based_Buffer_Overflow__c_CWE805_wchar_t_memcpy_17_bad()
{
    int i;
    wchar_t * data;
    data = NULL;
    for(i = 0; i < 1; i++)
    {
        /* FLAW: Allocate and point data to a small buffer that is smaller than the large buffer used in the sinks */
        data = (wchar_t *)malloc(50*sizeof(wchar_t));
        data[0] = L'\0'; /* null terminate */
    }
    {
        wchar_t source[100];
        wmemset(source, L'C', 100-1); /* fill with L'C's */
        source[100-1] = L'\0'; /* null terminate */
        /* POTENTIAL FLAW: Possible buffer overflow if source is larger than data */
        memcpy(data, source, 100*sizeof(wchar_t));
        data[100-1] = L'\0'; /* Ensure the destination buffer is null terminated */
        printWLine(data);
        free(data);
    }
}