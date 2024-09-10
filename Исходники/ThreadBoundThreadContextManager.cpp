void ThreadBoundThreadContextManager::DestroyAllContexts()
{
#if ENABLE_BACKGROUND_JOB_PROCESSOR
    JsUtil::BackgroundJobProcessor * jobProcessor = NULL;
#endif
    
    {
        AutoCriticalSection lock(ThreadContext::GetCriticalSection());

        ThreadContextTLSEntry * currentEntry = ThreadContextTLSEntry::GetEntryForCurrentThread();

        if (currentEntry == NULL)
        {
            // We need a current thread entry so that we can use it to release any thread contexts
            // we find below.
            try
            {
                AUTO_NESTED_HANDLED_EXCEPTION_TYPE(ExceptionType_OutOfMemory);
                currentEntry = ThreadContextTLSEntry::CreateEntryForCurrentThread();
                entries.Prepend(currentEntry);
            }
            catch (Js::OutOfMemoryException)
            {
                return;
            }
        }
        else
        {
            // We need to clear out the current thread entry so that we can use it to release any
            // thread contexts we find below.
            ThreadContext * threadContext = static_cast<ThreadContext *>(currentEntry->GetThreadContext());

            if (threadContext != NULL)
            {
                if (threadContext->IsThreadBound())
                {
                    ShutdownThreadContext(threadContext);
                    ThreadContextTLSEntry::ClearThreadContext(currentEntry, false);
                }
                else
                {
                    ThreadContextTLSEntry::ClearThreadContext(currentEntry, true);
                }
            }
        }

        EntryList::Iterator iter(&entries);

        while (iter.Next())
        {
            ThreadContextTLSEntry * entry = iter.Data();
            ThreadContext * threadContext =  static_cast<ThreadContext *>(entry->GetThreadContext());

            if (threadContext != nullptr)
            {
                // Found a thread context. Remove it from the containing entry.
                ThreadContextTLSEntry::ClearThreadContext(entry, true);
                // Now set it to our thread's entry.
                ThreadContextTLSEntry::SetThreadContext(currentEntry, threadContext);
                // Clear it out.
                ShutdownThreadContext(threadContext);
                // Now clear it out of our entry.
                ThreadContextTLSEntry::ClearThreadContext(currentEntry, false);
            }
        }

        // We can only clean up our own TLS entry, so we're going to go ahead and do that here.
        entries.Remove(currentEntry);
        ThreadContextTLSEntry::CleanupThread();

#if ENABLE_BACKGROUND_JOB_PROCESSOR
        if (s_sharedJobProcessor != NULL)
        {
            jobProcessor = s_sharedJobProcessor;
            s_sharedJobProcessor = NULL;

            jobProcessor->Close();
        }
#endif
    }

#if ENABLE_BACKGROUND_JOB_PROCESSOR
    if (jobProcessor != NULL)
    {
        HeapDelete(jobProcessor);
    }
#endif
}