StringSearchPerformanceTest::~StringSearchPerformanceTest() {
    CollData *data  = bms->getData();
    UCollator *coll = data->getCollator();

    delete bms;
    delete targetString;
    CollData::close(data);
    ucol_close(coll);

    if (pttrn != NULL) {
        free(pttrn);
    }

#ifndef TEST_BOYER_MOORE_SEARCH
    if (srch != NULL) {
        usearch_close(srch);
    }
#endif
}