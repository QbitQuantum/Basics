/** @brief
 *
 * This test case does the following:
 * - creates a KV.
 * - deletes the KV.
 * - checks that the deleted KV can no longer be found in the store.
 *
 * @return on success returns CaseNext to continue to next test case, otherwise will assert on errors.
 */
control_t cfstore_add_del_test_01_end(const size_t call_count)
{
    bool bfound = false;
    int32_t ret = ARM_DRIVER_ERROR;
    ARM_CFSTORE_SIZE len = 0;
    ARM_CFSTORE_DRIVER* drv = &cfstore_driver;
    ARM_CFSTORE_KEYDESC kdesc;
    ARM_CFSTORE_HANDLE_INIT(hkey);
    ARM_CFSTORE_FMODE flags;

    CFSTORE_FENTRYLOG("%s:entered\n", __func__);
    (void) call_count;
    memset(&kdesc, 0, sizeof(kdesc));
    memset(&flags, 0, sizeof(flags));

    kdesc.drl = ARM_RETENTION_WHILE_DEVICE_ACTIVE;
    len = strlen(cfstore_add_del_test_07_data[0].value);

    ret = cfstore_test_create(cfstore_add_del_test_07_data[0].key_name, (char*) cfstore_add_del_test_07_data[0].value, &len, &kdesc);
    CFSTORE_TEST_UTEST_MESSAGE(cfstore_add_del_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Error: failed to create KV in store (ret=%d).\n", __func__, (int) ret);
    TEST_ASSERT_MESSAGE(ret >= ARM_DRIVER_OK, cfstore_add_del_utest_msg_g);

    /* now delete KV*/
    ret = drv->Open(cfstore_add_del_test_07_data[0].key_name, flags, hkey);
    CFSTORE_TEST_UTEST_MESSAGE(cfstore_add_del_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Error: failed to Open() (ret=%d).\n", __func__, (int) ret);
    TEST_ASSERT_MESSAGE(ret >= ARM_DRIVER_OK, cfstore_add_del_utest_msg_g);

    if(hkey != NULL){
        ret = drv->Delete(hkey);
        drv->Close(hkey);
        hkey = NULL;
    }
    /* check that the KV has been deleted */
    /* revert to CFSTORE_LOG if more trace required */
    CFSTORE_DBGLOG("LOG: WARNING: About to look for non-existent key (key_name=%s) (which will generate internal trace reporting errors if debug trace enabled).\n", cfstore_add_del_test_07_data[0].key_name);
    ret = cfstore_test_kv_is_found(cfstore_add_del_test_07_data[0].key_name, &bfound);
    CFSTORE_TEST_UTEST_MESSAGE(cfstore_add_del_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Error failed to delete a key (ret=%d).\n", __func__, (int) ret);
    TEST_ASSERT_MESSAGE(ret == ARM_CFSTORE_DRIVER_ERROR_KEY_NOT_FOUND, cfstore_add_del_utest_msg_g);

    CFSTORE_TEST_UTEST_MESSAGE(cfstore_add_del_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Test failed: found KV that was previously deleted (key_name=%s)\n", __func__, cfstore_add_del_test_07_data[0].key_name);
    TEST_ASSERT_MESSAGE(bfound == false, cfstore_add_del_utest_msg_g);

    ret = drv->Uninitialize();
    CFSTORE_TEST_UTEST_MESSAGE(cfstore_add_del_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Error: Uninitialize() call failed.\n", __func__);
    TEST_ASSERT_MESSAGE(ret >= ARM_DRIVER_OK, cfstore_add_del_utest_msg_g);
    return CaseNext;
}