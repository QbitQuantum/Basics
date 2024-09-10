/*******************************************************************************
*
*   函 数 名 : GetOSBit
*  功能描述 : 取得操作系统位数
*  参数列表 : 无
*   说      明 : 
*  返回结果 :  如果成功，返回操作系统位数, 否则返回0
*
*******************************************************************************/
ULONG   GetOSBit(VOID)
{
        SYSTEM_INFO si = {0} ;
        GetNativeSystemInfo(&si) ;
        if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 ||
                si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64 )
        {
                return 64;
        }
        return 32;
}