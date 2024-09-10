static ULONG WINAPI IDsCaptureDriverNotifyImpl_Release(PIDSDRIVERNOTIFY iface)
{
    IDsCaptureDriverNotifyImpl *This = (IDsCaptureDriverNotifyImpl *)iface;
    ULONG refCount = InterlockedDecrement(&This->ref);

    TRACE("(%p) ref was %d\n", This, refCount + 1);

    if (!refCount) {
        This->buffer->notify = NULL;
        if (This->timerID)
        {
            timeKillEvent(This->timerID);
            timeEndPeriod(DS_TIME_RES);
        }
        HeapFree(GetProcessHeap(), 0, This->notifies);
        HeapFree(GetProcessHeap(), 0, This);
        TRACE("(%p) released\n", This);
    }
    return refCount;
}