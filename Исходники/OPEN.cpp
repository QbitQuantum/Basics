/** @brief
 * Basic open test which does the following:
 * - creates KV with default rw perms and writes some data to the value blob.
 * - closes the newly created KV.
 * - opens the KV with the default permissions (r-only)
 * - reads the KV data and checks its the same as the previously created data.
 * - closes the opened key
 *
 * @return on success returns CaseNext to continue to next test case, otherwise will assert on errors.
 */
control_t cfstore_open_test_01_end(const size_t call_count)
{
    char* read_buf;
    int32_t ret = ARM_DRIVER_ERROR;
    ARM_CFSTORE_SIZE len = 0;
    ARM_CFSTORE_DRIVER* drv = &cfstore_driver;
    ARM_CFSTORE_KEYDESC kdesc;
    ARM_CFSTORE_HANDLE_INIT(hkey);
    cfstore_kv_data_t *node;
    ARM_CFSTORE_FMODE flags;

    CFSTORE_DBGLOG("%s:entered\n", __func__);
    (void) call_count;
    node = cfstore_open_test_01_kv_data;
    memset(&kdesc, 0, sizeof(kdesc));
    memset(&flags, 0, sizeof(flags));

    kdesc.drl = ARM_RETENTION_WHILE_DEVICE_ACTIVE;
    CFSTORE_DBGLOG("%s:About to create new node (key_name=\"%s\", value=\"%s\")\n", __func__, node->key_name, node->value);
    ret = drv->Create(node->key_name, strlen(node->value), &kdesc, hkey);
    CFSTORE_TEST_UTEST_MESSAGE(cfstore_open_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Error: failed to create node (key_name=\"%s\", value=\"%s\")(ret=%d)\n", __func__, node->key_name, node->value, (int) ret);
    TEST_ASSERT_MESSAGE(ret >= ARM_DRIVER_OK, cfstore_open_utest_msg_g);

    CFSTORE_DBGLOG("%s:length of KV=%d (key_name=\"%s\", value=\"%s\")\n", __func__, (int) len, node->key_name, node->value);
    len = strlen(node->value);
    ret = drv->Write(hkey, (char*) node->value, &len);
    CFSTORE_TEST_UTEST_MESSAGE(cfstore_open_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Error: failed to write key (key_name=\"%s\", value=\"%s\")(ret=%d)\n", __func__, node->key_name, node->value, (int) ret);
    TEST_ASSERT_MESSAGE(ret >= ARM_DRIVER_OK, cfstore_open_utest_msg_g);

    CFSTORE_TEST_UTEST_MESSAGE(cfstore_open_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Error: failed to write full value data (key_name=\"%s\", value=\"%s\"), len=%d, (ret=%d)\n", __func__, node->key_name, node->value, (int) len, (int) ret);
    TEST_ASSERT_MESSAGE(len == strlen(node->value), cfstore_open_utest_msg_g);

    CFSTORE_DBGLOG("Created KV successfully (key_name=\"%s\", value=\"%s\")\n", node->key_name, node->value);
    ret = drv->Close(hkey);
    CFSTORE_TEST_UTEST_MESSAGE(cfstore_open_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Error: failed to close handle (ret=%d)\n", __func__, (int) ret);
    TEST_ASSERT_MESSAGE(ret >= ARM_DRIVER_OK, cfstore_open_utest_msg_g);

    /* now open the newly created key */
    ret = drv->Open(node->key_name, flags, hkey);
    CFSTORE_TEST_UTEST_MESSAGE(cfstore_open_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Error: failed to open node (key_name=\"%s\", value=\"%s\")(ret=%d)\n", __func__, node->key_name, node->value, (int) ret);
    TEST_ASSERT_MESSAGE(ret >= ARM_DRIVER_OK, cfstore_open_utest_msg_g);

    len = strlen(node->value) + 1;
    read_buf = (char*) malloc(len);
    CFSTORE_TEST_UTEST_MESSAGE(cfstore_open_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Error: failed to allocated read buffer \n", __func__);
    TEST_ASSERT_MESSAGE(read_buf != NULL, cfstore_open_utest_msg_g);

    CFSTORE_DBGLOG("Opened KV successfully (key_name=\"%s\", value=\"%s\")\n", node->key_name, node->value);
    memset(read_buf, 0, len);
    ret = drv->Read(hkey, read_buf, &len);
    CFSTORE_TEST_UTEST_MESSAGE(cfstore_open_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Error: failed to write key (key_name=\"%s\", value=\"%s\")\n", __func__, node->key_name, node->value);
    TEST_ASSERT_MESSAGE(ret >= ARM_DRIVER_OK, cfstore_open_utest_msg_g);

    /* check read data is as expected */
    CFSTORE_TEST_UTEST_MESSAGE(cfstore_open_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Error: read value data (%s) != KV value data (key_name=\"%s\", value=\"%s\")\n", __func__, read_buf, node->key_name, node->value);
    TEST_ASSERT_MESSAGE(strncmp(read_buf, node->value, strlen(node->value)) == 0, cfstore_open_utest_msg_g);

    if(read_buf){
        free(read_buf);
    }
    CFSTORE_TEST_UTEST_MESSAGE(cfstore_open_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Error: Close() call failed.\n", __func__);
    TEST_ASSERT_MESSAGE(drv->Close(hkey) >= ARM_DRIVER_OK, cfstore_open_utest_msg_g);

    ret = drv->Uninitialize();
    CFSTORE_TEST_UTEST_MESSAGE(cfstore_open_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Error: Uninitialize() call failed.\n", __func__);
    TEST_ASSERT_MESSAGE(ret >= ARM_DRIVER_OK, cfstore_open_utest_msg_g);
    return CaseNext;
}