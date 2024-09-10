void ConcurrentDictionaryTest::RunDictionaryTest_GetOrAdd(
    int cLevel,
    int initSize,
    int threads,
    int addsPerThread)
{
    UNREFERENCED_PARAMETER(cLevel);
    UNREFERENCED_PARAMETER(initSize);

    NTSTATUS status;

    KAllocator& allocator = GetAllocator();
    ConcurrentDictionary<int, int>::SPtr dict;
    status = ConcurrentDictionary<int, int>::Create(allocator, dict);
    KInvariant(NT_SUCCESS(status));

    KArray<KThreadPool::WorkItem*> itemArray(allocator);
    KFinally([&] {
        for (ULONG i = 0; i < itemArray.Count(); ++i)
        {
            _delete(itemArray[i]);
        }
    });

    volatile ULONG count = threads;
    KDelegate<int(int const &)> func(valueFactory);
    KEvent event;
    for (int i = 0; i < threads; ++i)
    {
        int ii = i;
        auto work = [&, ii] {
            for (int j = 0; j < addsPerThread; ++j)
            {
                if (j + ii % 2 == 0)
                {
                    dict->GetOrAdd(j, -j);
                }
                else
                {
                    dict->GetOrAdd(j, func);
                }
            }
            if (InterlockedDecrement(&count) == 0)
            {
                event.SetEvent();
            }
        };
        WorkItem<decltype(work)> *item = _new(CONCURRENTDICTIONARY_TAG, allocator) WorkItem<decltype(work)>(work);
        KInvariant(item);

        GetThreadPool().QueueWorkItem(*item);
        itemArray.Append(item);
    }
    event.WaitUntilSet();

    typename IEnumerator<KeyValuePair<int, int>>::SPtr enumerator = dict->GetEnumerator();
    while (enumerator->MoveNext())
    {
        KeyValuePair<int, int> entry = enumerator->Current();
        KInvariant(entry.Key == -entry.Value);
    }
}