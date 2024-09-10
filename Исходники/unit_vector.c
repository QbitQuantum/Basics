void TestPopAndRemove()
{
    Vector* vector = VectorInit(DEFAULT_CAPACITY);
    vector->set_clean(vector, CleanElement);
    void* dummy;

    CU_ASSERT(vector->pop_back(vector) == false);

    unsigned i;
    for (i = 0 ; i < SIZE_MID_TEST ; ++i) {
        Tuple* tuple = (Tuple*)malloc(sizeof(Tuple));
        tuple->first = i;
        tuple->second = i;
        vector->push_back(vector, tuple);
    }

    /* Pop elements ranging from (SML * 3) to MID from the vector tail. */
    for (i = 0 ; i < SIZE_SML_TEST ; ++i)
        CU_ASSERT(vector->pop_back(vector) == true);
    CU_ASSERT(vector->get(vector, SIZE_SML_TEST * 3, &dummy) == false);
    CU_ASSERT(vector->get(vector, SIZE_MID_TEST, &dummy) == false);

    /* Remove elements ranging from (SML * 2) to (SML * 3) from the vector tail. */
    for (i = SIZE_SML_TEST * 3 - 1 ; i >= SIZE_SML_TEST << 1 ; --i)
        CU_ASSERT(vector->remove(vector, i) == true);
    CU_ASSERT(vector->get(vector, SIZE_SML_TEST << 1, &dummy) == false);
    CU_ASSERT(vector->remove(vector, SIZE_SML_TEST << 1) == false);
    CU_ASSERT(vector->remove(vector, SIZE_MID_TEST) == false);

    /* Remove elements ranging from 0 to SML from the vector head. */
    for (i = 0 ; i < SIZE_SML_TEST ; ++i)
        CU_ASSERT(vector->remove(vector, 0) == true);
    CU_ASSERT(vector->get(vector, SIZE_SML_TEST, &dummy) == false);

    unsigned num = SIZE_SML_TEST;
    for (i = 0 ; i < SIZE_SML_TEST ; ++i) {
        void* tuple;
        CU_ASSERT(vector->get(vector, i, &tuple) == true);
        CU_ASSERT_EQUAL(((Tuple*)tuple)->first, num);
        ++num;
    }

    CU_ASSERT_EQUAL(vector->size(vector), SIZE_SML_TEST);
    CU_ASSERT_EQUAL(vector->capacity(vector), SIZE_MID_TEST);

    VectorDeinit(vector);
}