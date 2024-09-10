TEST(MallocTests, HeapInformation) {
    HANDLE heap = GetProcessHeap();
    ASSERT_NE(heap, (HANDLE)NULL);
    ULONG heap_type;
    SIZE_T got;
    BOOL res = HeapQueryInformation(heap, HeapCompatibilityInformation, &heap_type,
                                    sizeof(heap_type), &got);
    ASSERT_EQ(res, TRUE);
    ASSERT_EQ(got, sizeof(heap_type));
    ASSERT_LT(heap_type, 3); /* 0, 1, 2 are the only valid values */

    heap_type = 2;
    res = HeapSetInformation(heap, HeapCompatibilityInformation, &heap_type,
                             sizeof(heap_type));
    ASSERT_EQ(res, TRUE);
    heap_type = 2;

    res = HeapSetInformation(heap, HeapEnableTerminationOnCorruption, NULL, 0);
    ASSERT_EQ(res, TRUE);
}