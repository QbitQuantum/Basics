void Worklist::finishCreation(unsigned numberOfThreads)
{
    RELEASE_ASSERT(numberOfThreads);
    for (unsigned i = numberOfThreads; i--;)
        m_threads.append(createThread(threadFunction, this, "JSC Compilation Thread"));
}