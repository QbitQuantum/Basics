static HRESULT WINAPI ReferenceClock_AdvisePeriodic(IReferenceClock *iface,
                                                    REFERENCE_TIME rtStartTime,
                                                    REFERENCE_TIME rtPeriodTime,
                                                    HSEMAPHORE hSemaphore,
                                                    DWORD_PTR *pdwAdviseCookie)
{
    DSoundRenderImpl *This = impl_from_IReferenceClock(iface);
    struct dsoundrender_timer *t;

    TRACE("(%p/%p)->(%s, %s, %p, %p)\n", This, iface, wine_dbgstr_longlong(rtStartTime), wine_dbgstr_longlong(rtPeriodTime), (void*)hSemaphore, pdwAdviseCookie);

    if (rtStartTime <= 0 || rtPeriodTime <= 0)
        return E_INVALIDARG;

    if (!pdwAdviseCookie)
        return E_POINTER;

    EnterCriticalSection(&This->renderer.filter.csFilter);
    if (!This->threadid && This->dsbuffer) {
        This->thread_wait = CreateEventW(0, 0, 0, 0);
        This->advisethread = CreateThread(NULL, 0, DSoundAdviseThread, This, 0, &This->threadid);
        WaitForSingleObject(This->thread_wait, INFINITE);
        CloseHandle(This->thread_wait);
    }
    LeaveCriticalSection(&This->renderer.filter.csFilter);

    t = HeapAlloc(GetProcessHeap(), 0, sizeof(*t));
    t->next = NULL;
    t->start = rtStartTime;
    t->periodicity = rtPeriodTime;
    t->handle = (HANDLE)hSemaphore;
    t->cookie = InterlockedIncrement(&cookie_counter);
    PostThreadMessageW(This->threadid, WM_APP+1, (WPARAM)t, 0);
    *pdwAdviseCookie = t->cookie;

    return S_OK;
}