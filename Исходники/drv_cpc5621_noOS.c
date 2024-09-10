/**
  Open the device.
  
  At the first time:
  - allocating internal memory for each new device
  - initialize the device
  - set up the interrupt
 
   \return
   0 - if no error,
   otherwise error code
*/
static int cpc5621_open (
    char    *path,      /**< pointer to the device path */
    INT     flags       /**< flag of the open */
)
{
    int result = 0;
    int devNum, chNum;
    CPC5621_DEV *pDev = NULL;
    
    if (Get_Dev_Num(path, &devNum, &chNum) == ERR)
        return -ENODEV;

    /* check the device number */
    if (chNum >= MAX_CHANNEL)
    {
        TRACE(CPC5621_DRV, DBG_LEVEL_HIGH, ("cpc5621_open: max. device number exceed\n"));
        result = -ENODEV;
        goto OPEN_ERROR;
    }
    
    Sem_Lock(CpcSemDrv);

    pDev = CPC5621_Devices[devNum][chNum];

    if (pDev == NULL)
    {
        pDev = (CPC5621_DEV*)Alloc_Mem(sizeof(CPC5621_DEV));
        if (!pDev)
        {
            TRACE(CPC5621_DRV, DBG_LEVEL_HIGH,("cpc5621_open: no memory for device structure.\n"));
            result = -ENOMEM;
            goto OPEN_ERROR;
        }

        memset((char*)pDev, 0, sizeof(CPC5621_DEV));

        /* The device number and channel number should be getted from upper layer */
        if (Drv_CPC5621_Init(pDev, devNum, chNum) == ERR)
        {
            TRACE(CPC5621_DRV, DBG_LEVEL_HIGH,("cpc5621_open: driver init failed!\n"));
            result = -ENOMEM;
            goto OPEN_ERROR;
        }
        
        CPC5621_Devices[devNum][chNum] = pDev;
    }

    if (pDev->bOpen == TRUE)
    {
        TRACE(CPC5621_DRV, DBG_LEVEL_HIGH,("cpc5621_open: already opened!\n"));
        return -EBUSY;
    }

    pDev->bOpen = TRUE;
    pDev->nInUse++;

    /* and use filp->private_data to point to the device data */
    filp->private_data = pDev;
    
    Sem_Unlock(CpcSemDrv);

    return (int)(pDev);

OPEN_ERROR:

    if (pDev != NULL)
    {
        Free_Mem(pDev);
        CPC5621_Devices[devNum][chNum] = NULL;
    }
    
    Sem_Unlock(CpcSemDrv);
    
    return result;
}