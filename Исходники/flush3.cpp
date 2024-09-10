/* @brief   simple flush test */
static control_t cfstore_flush3_test_02(const size_t call_count)
{
    int32_t cfsStatus = ARM_DRIVER_ERROR;
    ARM_CFSTORE_KEYDESC kdesc;
    ARM_CFSTORE_FMODE flags;
    ARM_CFSTORE_SIZE len = strlen("key0");
    ARM_CFSTORE_HANDLE_INIT(hkey);
    ARM_CFSTORE_DRIVER* drv = &cfstore_driver;

    (void) call_count;
    memset(&kdesc, 0, sizeof(kdesc));
    memset(&flags, 0, sizeof(flags));

    CFSTORE_DBGLOG("%s:Initialize()\n", __func__);
    cfsStatus = drv->Initialize(NULL, NULL);
    CFSTORE_TEST_UTEST_MESSAGE(cfstore_flush3_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Error:%d:cfsStatus=%d", __func__, __LINE__, (int) cfsStatus);
    TEST_ASSERT_MESSAGE(cfsStatus >= ARM_DRIVER_OK, cfstore_flush3_utest_msg_g);

    CFSTORE_DBGLOG("%s:Create()\n", __func__);
    cfsStatus = drv->Create("key0", len, &kdesc, hkey);
    CFSTORE_TEST_UTEST_MESSAGE(cfstore_flush3_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Error:%d:cfsStatus=%d", __func__, __LINE__, (int) cfsStatus);
    TEST_ASSERT_MESSAGE(cfsStatus >= ARM_DRIVER_OK, cfstore_flush3_utest_msg_g);

    len = strlen("some-value");
    CFSTORE_DBGLOG("%s:Write()\n", __func__);
    cfsStatus = drv->Write(hkey, "some-value", &len);
    CFSTORE_TEST_UTEST_MESSAGE(cfstore_flush3_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Error:%d:cfsStatus=%d", __func__, __LINE__, (int) cfsStatus);
    TEST_ASSERT_MESSAGE(cfsStatus >= ARM_DRIVER_OK, cfstore_flush3_utest_msg_g);

    CFSTORE_DBGLOG("%s:Close()\n", __func__);
    cfsStatus = drv->Close(hkey);
    CFSTORE_TEST_UTEST_MESSAGE(cfstore_flush3_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Error:%d:cfsStatus=%d", __func__, __LINE__, (int) cfsStatus);
    TEST_ASSERT_MESSAGE(cfsStatus >= ARM_DRIVER_OK, cfstore_flush3_utest_msg_g);

    CFSTORE_DBGLOG("%s:Flush()\n", __func__);
    cfsStatus = drv->Flush();
    CFSTORE_TEST_UTEST_MESSAGE(cfstore_flush3_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Error:%d:cfsStatus=%d", __func__, __LINE__, (int) cfsStatus);
    TEST_ASSERT_MESSAGE(cfsStatus >= ARM_DRIVER_OK, cfstore_flush3_utest_msg_g);

    CFSTORE_DBGLOG("%s:Open()\n", __func__);
    cfsStatus = drv->Open("key0", flags, hkey);
    CFSTORE_TEST_UTEST_MESSAGE(cfstore_flush3_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Error:%d:cfsStatus=%d", __func__, __LINE__, (int) cfsStatus);
    TEST_ASSERT_MESSAGE(cfsStatus >= ARM_DRIVER_OK, cfstore_flush3_utest_msg_g);

    CFSTORE_DBGLOG("%s:Delete()\n", __func__);
    cfsStatus = drv->Delete(hkey);
    CFSTORE_TEST_UTEST_MESSAGE(cfstore_flush3_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Error:%d:cfsStatus=%d", __func__, __LINE__, (int) cfsStatus);
    TEST_ASSERT_MESSAGE(cfsStatus >= ARM_DRIVER_OK, cfstore_flush3_utest_msg_g);

    CFSTORE_DBGLOG("%s:Close()\n", __func__);
    cfsStatus = drv->Close(hkey);       ///////  <--- cfsStatus = ARM_CFSTORE_DRIVER_ERROR_PREEXISTING_KEY
    CFSTORE_TEST_UTEST_MESSAGE(cfstore_flush3_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Error:%d:cfsStatus=%d", __func__, __LINE__, (int) cfsStatus);
    TEST_ASSERT_MESSAGE(cfsStatus >= ARM_DRIVER_OK, cfstore_flush3_utest_msg_g);

    CFSTORE_DBGLOG("%s:got status = %d\n", __func__, (int) cfsStatus);

    CFSTORE_DBGLOG("%s:Uninitialize()\n", __func__);
    cfsStatus = drv->Uninitialize();
    CFSTORE_TEST_UTEST_MESSAGE(cfstore_flush3_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Error:%d:cfsStatus=%d", __func__, __LINE__, (int) cfsStatus);
    TEST_ASSERT_MESSAGE(cfsStatus >= ARM_DRIVER_OK, cfstore_flush3_utest_msg_g);

    return CaseNext;
}