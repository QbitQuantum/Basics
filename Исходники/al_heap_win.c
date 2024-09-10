bool AL_CALLTYPE alHeapWin32_SetLowFragmentation(void* _this, bool bEnableLowFragmantation)
{
	alHeapWin32i* _data = (alHeapWin32i*)_this;
	ULONG HeapFragValue = bEnableLowFragmantation ? 2 : 0;
	if (!_data->heap)
		return false;
	return !!HeapSetInformation(_data->heap, HeapCompatibilityInformation, &HeapFragValue, sizeof(HeapFragValue));
}