    void
    verify_MultimapIters()  ///< @see IterTools_test#verify_filterRepetitions
    {
        MAP testMap;
        for (uint i=0; i<NUM_ELMS; ++i)
        {
            uint n = 1 + rand() % 100;
            do testMap.insert (make_pair (i,n));
            while (--n);
        }
        CHECK (NUM_ELMS < testMap.size(), "no repetition in test data??");

        IntIter keys = eachDistinctKey (testMap);

        cout << "distinct_keys";
        CHECK (keys);
        pullOut (keys);
        CHECK (!keys);

        cout << "values_4_key";
        IntIter vals = eachValForKey (testMap, NUM_ELMS); // non-existent key
        CHECK (!vals);

        vals = eachValForKey (testMap, 0);
        CHECK (vals);
        pullOut (vals); // should produce anything between 1 and 100 entries
        CHECK (!vals);
    }