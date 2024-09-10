//--------------------------------------------------------------------------------------
//
// SuballocateFromUploadHeap
//
//--------------------------------------------------------------------------------------
UINT8* UploadHeapDX12::Suballocate(SIZE_T uSize, UINT64 uAlign)
{
    m_pDataCur = reinterpret_cast<UINT8*>(Align(reinterpret_cast<SIZE_T>(m_pDataCur), uAlign));

    // flush operations if we ran out of space in the heap

    if (m_pDataCur >= m_pDataEnd || m_pDataCur + uSize >= m_pDataEnd)
    {
        FlushAndFinish();
    }

    UINT8* pRet = m_pDataCur;
    m_pDataCur += uSize;
    return pRet;
}