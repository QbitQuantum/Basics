  main(CkArgMsg *)
  {
    #if CMK_USE_STL_MSGQ
    CkPrintf("Charm has CMK_USE_STL_MSGQ enabled\n");
    #if CMK_HAS_STD_UNORDERED_MAP
    CkPrintf("... and its using a msg q implemented with a std::unordered_map\n");
    #else
    CkPrintf("... and its using a msg q implemented with a std::map\n");
    #endif
    #endif
    int tests = 0, success = 0, fail = 0;
    char message[100];

    RUN_TEST(test_empty);
    RUN_TEST(test_one);
    RUN_TEST(test_two);
    RUN_TEST(test_fifo);
    RUN_TEST(test_lifo);
    RUN_TEST(test_enqueue_mixed);
    RUN_TEST(test_enumerate);
    RUN_TEST(test_general_fifo);
    RUN_TEST(test_general_ififo);
    RUN_TEST(perftest_general_ififo);

    if (fail) {
      sprintf(message, "%d/%d tests failed\n", fail, tests);
      CkAbort(message);
    }
    else {
      CkPrintf("All %d tests passed\n", tests);
      CkExit();
    }
  }