/**
 * Find IO port range for the parallel port and return the lower address.
 *
 * @returns parallel port IO address.
 * @param   DevInst    Device Instance for parallel port.
 */
static uint32_t drvHostWinFindIORangeResource(const DEVINST DevInst)
{
    uint8_t  *pBuf  = NULL;
    short     wHeaderSize;
    uint32_t  u32Size;
    CONFIGRET cmRet;
    LOG_CONF  firstLogConf;
    LOG_CONF  nextLogConf;
    RES_DES   rdPrevResDes;
    uint32_t  u32ParportAddr = 0;

    wHeaderSize = sizeof(IO_DES);
    cmRet = CM_Get_First_Log_Conf(&firstLogConf, DevInst, ALLOC_LOG_CONF);
    if (cmRet != CR_SUCCESS)
    {
        cmRet = CM_Get_First_Log_Conf(&firstLogConf, DevInst, BOOT_LOG_CONF);
        if (cmRet != CR_SUCCESS)
            return 0;
    }
    cmRet = CM_Get_Next_Res_Des(&nextLogConf, firstLogConf, 2, 0L, 0L);
    if (cmRet != CR_SUCCESS)
    {
        CM_Free_Res_Des_Handle(firstLogConf);
        return 0;
    }
    /* This loop is based on the fact that only one resourece is assigned to
     * the LPT port. If multiple resources (address range) are assigned to
     * to LPT port, it will pick and return the last one
     */
    for (;;)
    {
        u32Size = 0;
        cmRet = CM_Get_Res_Des_Data_Size((PULONG)(&u32Size), nextLogConf, 0L);
        if (cmRet != CR_SUCCESS)
        {
            LogFlowFunc(("Failed to get Size \n"));
            CM_Free_Res_Des_Handle(nextLogConf);
            break;
        }

        pBuf = (uint8_t *)RTMemAlloc(u32Size + 1);
        if (!pBuf)
        {
            LogFlowFunc(("Failed to get Buf %d\n", u32Size));
            CM_Free_Res_Des_Handle(nextLogConf);
            break;
        }
        cmRet = CM_Get_Res_Des_Data(nextLogConf, pBuf, u32Size, 0L);
        if (cmRet != CR_SUCCESS)
        {
            LogFlowFunc(("Failed to get Des Data \n"));
            CM_Free_Res_Des_Handle(nextLogConf);
            if (pBuf)
                RTMemFree(pBuf);
            break;
        }

        LogFlowFunc(("call GetIOResource\n"));
        if (pBuf)
            u32ParportAddr = ((IO_DES *)pBuf)->IOD_Alloc_Base;
        LogFlowFunc(("called GetIOResource, ret=%#x\n", u32ParportAddr));
        rdPrevResDes = 0;
        cmRet = CM_Get_Next_Res_Des(&rdPrevResDes,
                                    nextLogConf,
                                    2,
                                    0L,
                                    0L);
        if (pBuf)
            RTMemFree(pBuf);
        if (cmRet != CR_SUCCESS)
           break;

        CM_Free_Res_Des_Handle(nextLogConf);
        nextLogConf = rdPrevResDes;
    }
    CM_Free_Res_Des_Handle(nextLogConf);
    LogFlowFunc(("return u32ParportAddr=%#x", u32ParportAddr));
    return u32ParportAddr;
}