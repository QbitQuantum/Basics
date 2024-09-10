void cyg_user_start(void)
#endif
{
    char x[300];
    char y[300];
    int  ret;
    int ctr;
    int fail;

    CYG_TEST_INIT();

    CYG_TEST_INFO("Starting tests from testcase " __FILE__ " for C library "
                  "strxfrm() function");
    CYG_TEST_INFO("This testcase tests robustness, and may take some time");

    fail = 0;
    for (ctr = 0; ctr < NUM_ROBUSTNESS_RUNS; ctr++) {
        my_strcpy(x, "Green plastic watering can, ");
        my_strcpy(y, "for her fake Chineese rubber plant");
        ret = strxfrm(x, y, my_strlen(y)+1);
        if ( (my_strcmp(x, "for her fake Chineese rubber plant") != 0) ||
             (my_strlen(y) != ret) ) {
            fail = 1;
            break;
        }
    }
    CYG_TEST_PASS_FAIL( (fail == 0), "Robustness test" );


//    CYG_TEST_NA("Testing is not applicable to this configuration");

    CYG_TEST_FINISH("Finished tests from testcase " __FILE__ " for C library "
                    "strxfrm() function");
} // main()