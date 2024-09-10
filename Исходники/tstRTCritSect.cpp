DECLINLINE(int) RTCritSectDelete(PCRITICAL_SECTION pCritSect)
{
    DeleteCriticalSection(pCritSect);
    return VINF_SUCCESS;
}