static void testSize()
{
    start_test("Lock free FIFO - size");
    
    const int es = sizeof(int);
    const int c = 100;
    
    const int nCases = 5;
    int nPush[nCases] = {10, 20, 30, 5, 90};
    int nPop[nCases] = {5, 1, 60, 10, 90};
    
    for (int i = 0; i < nCases; i++)
    {
        drLockFreeFIFO f;
        drLockFreeFIFO_init(&f, c, es);
        
        for (int j = 0; j < nPush[i]; j++)
        {
            int success = drLockFreeFIFO_push(&f, &j);
        }
        
        for (int j = 0; j < nPop[i]; j++)
        {
            int val = 0;
            int success = drLockFreeFIFO_pop(&f, &val);
        }
        
        const int expectedSize = fmaxf(0.0f, nPush[i] - nPop[i]);
        const int size = drLockFreeFIFO_getNumElements(&f);
        fail_unless(expectedSize == size, "FIFO size should be the same after pushing and popping the same number of items");
        
        drLockFreeFIFO_deinit(&f);
    }
    
    
}