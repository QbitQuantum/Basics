/********************************************************************
Function name:       MpuDSecDemo
Input parameters:
    NULL
Return:
    NULL
Function:
    MPU SRAM  Secmode  function.
********************************************************************/
void MpuDSecDemo(void)
{
	UINT32 desaddr,srcaddr,back;
	UINT16 i;
	UINT8 *p;
	UINT32 *addr1;
	desaddr = 0x2000F800;
	srcaddr = (UINT32)dma_src;

	MpuSetSecMode(MPUCR_SEC1_EN);
	addr1 = (UINT32 *)0x2000F800;
	back = *addr1;
	*addr1 = 0x12345678;
	if(*addr1 != 0x12345678)
	{
		//Todo: program fail;
		printf("MpuDSecDemo err \r\n");
	}
	else
	{
		*addr1 = back;
		printf("MpuDSecDemo OK\r\n");
	}

	Memset(dma_src, 0xFF, sizeof(dma_src));

	ScuDmaClkEn();
	DmaChLock(0);
	SetupMode(0, MEM_MEM, DISCRIC, 0, 0, 1, 1, W_8BIT, 10, 0);

	SetTransAddress(0, srcaddr, desaddr);
	SetTransLength(0, 10);


	if(DmaTrans(0) != DMA_RET_SUCESS)
	{
		//TODO:program fail; 
	}
	else
	{
		p = (UINT8*)0x2000F800;
		for(i = 0;i<10;i++,p++)
		{
			if(dma_src[i]!= *p)
			{
				//TODO: program fail
				printf("MpuDSecDemo DMA err \r\n");
				return;
			}				 
		}
	}
	printf("MpuDSecDemo DMA OK \r\n");
	DmaChUnlock(0);
	ScuDmaClkDis();
	MpuClrSecMode(MPUCR_SEC1_EN);
}