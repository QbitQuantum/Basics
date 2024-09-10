static void i51ManagedLaunchi51App(u32 param)
{
    CmnAppLaunchRspCbInfo_t tRspCb = {0};
    u32 *pSxmParam = MALLOC(sizeof(u32));
    MAE_WChar Url[128];
    int nLen = 128;
	u16 nClsId = CLSID_I51BASE;

    if (NULL != pSxmParam)
    {
        *pSxmParam = param;
        SWPRINTF(Url, nLen, L"Launch?APM_Mode=%d&ClsId=%d&VenData=%d&VenDataLen=%d&TransInId=%d&TransOutId=%d", APM_LAUNCH_NORMAL, nClsId, (u32)pSxmParam, sizeof(u32), 0, 0);
        tRspCb.pvUserData = (void *)pSxmParam;
        tRspCb.pfnLaunchListenerCb = i51ManagedAppLaunchVendorAppRspCB;
        if (MAE_RET_SUCCESS != LaunchApp(MAE_CLSID_2_SCHEMEID(nClsId), Url, &tRspCb))
        {
            FREEIF(pSxmParam);
        }
    }
}