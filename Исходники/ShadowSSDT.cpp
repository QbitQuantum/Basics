/* 获取当前SSDTShadow index、函数地址、当前所在模块 */
ULONG GetSSDTShadowFuncAddr( PSHADOW_INFO pShadowInfo, PULONG outputLen)
{
	PSYSTEM_SERVICE_TABLE_SHADOW KeServiceDescriptorTableShadow = NULL;
	ULONG		iCount = 0;
	ULONG		ulDrvNums=0;
	ULONG		iDrv=0;
	PDRVMOD_ITEM ptagDrvItem;
	ANSI_STRING				AnsiString;
	UNICODE_STRING			unico;

	if ( !pShadowInfo || !outputLen )
		return 0;

	KeServiceDescriptorTableShadow = (PSYSTEM_SERVICE_TABLE_SHADOW)GetSSDTShadowTable();
	if ( !KeServiceDescriptorTableShadow )
		return 0;

	//输出缓冲区尺寸 < 数量 * 尺寸，则返回 数量 * 尺寸
	if ( *outputLen < KeServiceDescriptorTableShadow->ServiceLimit * sizeof(SHADOW_INFO) )
	{
		*outputLen = (ULONG)KeServiceDescriptorTableShadow->ServiceLimit * sizeof(SHADOW_INFO);
		return 0;
	}

	//枚举驱动信息
	ptagDrvItem=GetKrnlModuleList(&ulDrvNums);

	/* 填充SSDTShadow的 index、当前函数地址 */
	for (iCount=0; iCount < KeServiceDescriptorTableShadow->ServiceLimit; iCount++)
	{
		pShadowInfo[iCount].currentAddr = (ULONG)KeServiceDescriptorTableShadow->ServiceTable[iCount];

//		KdPrint(("ShadowSSDT index:%d \t funcAddr:0x%08x\n", iCount, (ULONG)KeServiceDescriptorTableShadow->ServiceTable[iCount]));

		/* 查找Shadow函数当前所在的内核模块 */
		for ( iDrv = 0; iDrv < ulDrvNums; iDrv++ )
		{
			/* 查找ssdt函数当前所在的内核模块 */
			if ( CompareModule( (PVOID)pShadowInfo[iCount].currentAddr, &ptagDrvItem[iDrv]) )
			{
				RtlInitUnicodeString( &unico, ptagDrvItem[iDrv].pwszDrvPath );
				RtlUnicodeStringToAnsiString( &AnsiString, &unico, TRUE );

				/* 填充当前Shadow函数所在模块路径 */
				strcpy( pShadowInfo[iCount].imagePath, AnsiString.Buffer );
				RtlFreeAnsiString( &AnsiString );

//				KdPrint(("ssdt函数地址:0x%08X \t 模块路径:%s\n", pShadowInfo[iCount].currentAddr, pShadowInfo[iCount].imagePath));
				break;
			}
		}
	}

	//改写输出缓冲区尺寸、返回个数
	*outputLen = iCount * sizeof(SHADOW_INFO);
	return iCount;
}