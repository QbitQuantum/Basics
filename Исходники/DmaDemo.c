void DmaScanModeDemo(void)
{
    UINT8 ch_no;    //Dma channel number
    UINT32 len = 1023;
    UINT32 tmp_src[1023], tmp_dst[1023];
    UINT8 ret;

    printf("Dma Scan Mode Demo.\r\n");
    /* enable Dma Clk */
    ScuDmaClkEn();
    for(ch_no = 0; ch_no < 8; ch_no++)
    {
        /* initial source data */
        GetTrueRand8((UINT8 *)tmp_src, len << 2);
        /* lock dma channel */
        ret = DmaChLock(ch_no);
        /* setting dma trans parameter */
        ret |= SetupMode(ch_no, MEM_MEM, DISCRIC, NO_PER, NO_PER, ENINC, ENINC, W_32BIT, len, H_PRI);
        /* setting dma trans address */
        ret |= SetTransAddress(ch_no, (UINT32)tmp_src, (UINT32)tmp_dst);
        /* start dma trans */
        ret |= DmaTrans(ch_no);
        if(ret != DMA_RET_SUCESS)
        {
            printf("dma channel %d trans error, error code %d\r\n", ch_no, ret);
            return;
        }

        /* dma trans finish */
        if(Memcmp(tmp_src, tmp_dst, len) != 0)
        {
            printf("dma channel %d trans error, data error\r\n", ch_no);
            return;
        }
        else
        {
            printf("dma channel %d trans sucess\r\n", ch_no);
        }
        DmaChUnlock(ch_no);
    }
    ScuDmaClkDis();
}