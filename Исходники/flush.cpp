/** @brief  basic Flush() test
 *
 * @return on success returns CaseNext to continue to next test case, otherwise will assert on errors.
 */
int32_t cfstore_flush_test_01_x86_sync(void)
{
    int32_t ret = ARM_DRIVER_ERROR;
    ARM_CFSTORE_DRIVER* drv = &cfstore_driver;

    ret = drv->Initialize(NULL, NULL);
    if(ret != ARM_DRIVER_OK){
        CFSTORE_ERRLOG("%s:Initialize() call failed (ret=%d).\r\n", __func__, (int) ret);
        goto out0;
    }
    ret = drv->Flush();
    if(ret != ARM_DRIVER_OK){
        CFSTORE_ERRLOG("%s:Flush() call failed (ret=%d).\r\n", __func__, (int) ret);
    }
    ret = drv->Uninitialize();
    if(ret != ARM_DRIVER_OK){
        CFSTORE_ERRLOG("%s:Initialize() call failed to Uninitialise(ret=%d).\r\n", __func__, (int) ret);
        goto out0;
    }
 out0:
    return ret;
}