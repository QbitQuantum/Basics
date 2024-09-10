 static void ThreadStateDestroy(ThreadState* self)
 {
   LinearAllocDestroy(&self->m_ScratchAlloc);
   HeapDestroy(&self->m_LocalHeap);
 }