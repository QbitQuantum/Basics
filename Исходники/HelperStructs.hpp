 inline void CommandContext<T, N, L>::destroy() {
     CHECK_CALL(m_commandQueue->Signal(m_fence.Get(), UINT64_MAX),
                "Failed to insert a fence into the command queue.");
     syncThread(UINT64_MAX);
     if (!CloseHandle(m_syncEvent)) {
         printError("Failed to close the synchronization event handle."); 
         TERMINATE();
     }
     for (size_t i = 0; i < L; ++i) {
         // Command lists have to be released before the associated
         // root signatures and pipeline state objects.
         m_commandLists[i].Reset();
     }
 }