/*****************************************************************************
                    snap by mode 1
 how to snap:
 1)only creat one snap group
 2)bind to a vichn to snap and then unbind
 3)repeat 2) to snap all vichn in turn

 features:
 1)save memory, because only one snap group and snap channel
 2)efficiency lower than mode 2, pictures snapped will not more than 8.
*****************************************************************************/
HI_VOID* thread_StartSnapByMode1(HI_VOID *p)
{
    HI_S32 s32Ret;
    VENC_GRP VeGroup = 0;
    VENC_CHN SnapChn = 0;
    VI_DEV ViDev = 0;
    VI_CHN ViChn = 0;
    FILE *pFile = NULL;
    HI_S32 s32SnapCnt = 0;
    HI_S32 s32SnapTotal;
    SNAP_MULTI_CHN_S *pstSnapMultiChn = NULL;
    HI_S32 s32ViChnTotal;

    pstSnapMultiChn = (SNAP_MULTI_CHN_S*)p;
    VeGroup = pstSnapMultiChn->SnapGroup;
    SnapChn = pstSnapMultiChn->SnapChn;
    ViDev = pstSnapMultiChn->ViDev;
    s32ViChnTotal = pstSnapMultiChn->s32ViChnCnt;
    s32SnapTotal = pstSnapMultiChn->s32SnapTotal;

    /* snap all vi channels in sequence.
      * step 1: bind vi
      * step 2: register snap channel to group.
      * step 3: start snap channel to receiver picture.
      * step 4: get one-picture stream and save as jpeg file.
      * step 5: undo step 3, step 2, step 1.
      * step 6: chose next vi to snap, then go to step 1
      */
    ViChn = 0;
    while (HI_TRUE == pstSnapMultiChn->bThreadStart)
    {
        s32Ret = HI_MPI_VENC_BindInput(VeGroup, ViDev, ViChn);
        if (s32Ret != HI_SUCCESS)
        {
            printf("HI_MPI_VENC_BindInput err 0x%x\n", s32Ret);
            return NULL;
        }

        s32Ret = HI_MPI_VENC_RegisterChn(VeGroup, SnapChn);
        if (s32Ret != HI_SUCCESS)
        {
            printf("HI_MPI_VENC_RegisterChn err 0x%x\n", s32Ret);
            return NULL;
        }

        s32Ret = HI_MPI_VENC_StartRecvPic(SnapChn);
        if (s32Ret != HI_SUCCESS)
        {
            printf("HI_MPI_VENC_StartRecvPic err 0x%x\n", s32Ret);
            return NULL;
        }

        {
            /*save jpeg picture*/
            char acFile[128]  = {0};
            //struct timeval timenow;
            //gettimeofday(&timenow, NULL);
            sprintf(acFile, "Vichn%d_num%d.jpg", ViChn, s32SnapCnt);
            pFile = fopen(acFile, "wb");
            if (pFile == NULL)
            {
                printf("open file err\n");
                return NULL;
            }

            s32Ret = SAMPLE_GetSnapPic(SnapChn, pFile);
            if (s32Ret != HI_SUCCESS)
            {
                printf("SAMPLE_GetSnapPic err 0x%x\n", s32Ret);
                fclose(pFile);
                return NULL;
            }

            fclose(pFile);
        }

        s32Ret = HI_MPI_VENC_StopRecvPic(SnapChn);
        if (s32Ret != HI_SUCCESS)
        {
            printf("HI_MPI_VENC_StopRecvPic err 0x%x\n", s32Ret);
            return NULL;
        }

        s32Ret = HI_MPI_VENC_UnRegisterChn(SnapChn);
        if (s32Ret != HI_SUCCESS)
        {
            printf("HI_MPI_VENC_UnRegisterChn err 0x%x\n", s32Ret);
            return NULL;
        }

        s32Ret = HI_MPI_VENC_UnbindInput(VeGroup);
        if (s32Ret != HI_SUCCESS)
        {
            printf("HI_MPI_VENC_UnbindInput err 0x%x\n", s32Ret);
            return NULL;
        }

        /* continue to snap next vi channel */
        ViChn++;
        if(ViChn >= s32ViChnTotal)
        {
            ViChn = 0;
            s32SnapCnt++;
        }
    }

    return NULL;
}