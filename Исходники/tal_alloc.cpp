void ALLOCEXPANDARRAY::SetAt (size_t iElement, PVOID pData)
{
   size_t iHeap = iElement / m_cElementsPerHeap;
   size_t iIndex = iElement % m_cElementsPerHeap;

   if (!REALLOC (m_aHeaps, m_cHeaps, 1+iHeap, cREALLOC_EXPANDARRAYHEAPS))
      return;

   if (!m_aHeaps[ iHeap ])
      {
      size_t cbHeap = sizeof(EXPANDARRAYHEAP) + (m_cElementsPerHeap * m_cbElement);
      if ((m_aHeaps[ iHeap ] = (LPEXPANDARRAYHEAP)GlobalAlloc (GMEM_FIXED, cbHeap)) == NULL)
         return;
      memset (m_aHeaps[ iHeap ], 0x00, cbHeap);
      m_aHeaps[ iHeap ]->aElements = ((PBYTE)m_aHeaps[ iHeap ]) + sizeof(EXPANDARRAYHEAP);
      }

   if (!pData)
      memset (&((PBYTE)m_aHeaps[ iHeap ]->aElements)[ iIndex * m_cbElement ], 0x00, m_cbElement);
   else
      memcpy (&((PBYTE)m_aHeaps[ iHeap ]->aElements)[ iIndex * m_cbElement ], pData, m_cbElement);
}