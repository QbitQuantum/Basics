/**
 * @brief   add ~50 KVs and store them in flash
 *
 * @return on success returns CaseNext to continue to next test case, otherwise will assert on errors.
 */
static control_t cfstore_flash_set_test_01_end(const size_t call_count)
{
    int32_t ret = ARM_DRIVER_ERROR;
    ARM_CFSTORE_FMODE flags;
    ARM_CFSTORE_DRIVER* drv = &cfstore_driver;
    ARM_CFSTORE_CAPABILITIES caps = cfstore_driver.GetCapabilities();

    CFSTORE_FENTRYLOG("%s:entered\n", __func__);
    (void) call_count;
    memset(&flags, 0, sizeof(flags));

    CFSTORE_LOG("caps.asynchronous_ops : %d\n", (int) caps.asynchronous_ops);
    ret = cfstore_test_init_1();
    if(ret < ARM_DRIVER_OK){
        CFSTORE_ERRLOG("%s:Error: failed to write data to falsh.", __func__);
    }
    ret = drv->Flush();
    if(ret < ARM_DRIVER_OK){
        CFSTORE_ERRLOG("%s:Flush() call failed (ret=%d).\r\n", __func__, (int) ret);
    }
#ifdef CFSTORE_DEBUG
    ret = cfstore_test_dump();
    if(ret < ARM_DRIVER_OK){
        CFSTORE_ERRLOG("Error: failed to dump CFSTORE contents%s", "\n");
    }
#endif /* CFSTORE_DEBUG */
    ret = drv->Uninitialize();
    if(ret < ARM_DRIVER_OK){
        CFSTORE_ERRLOG("Error: failed to Uninitialize() CFSTORE%s", "\n");
    }
    return CaseNext;
}