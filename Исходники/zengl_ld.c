/*
	链接动态数组初始化
*/
ZL_VOID zengl_LDAddrListInit(ZL_VOID * VM_ARG)
{
	ZENGL_COMPILE_TYPE * compile = &((ZENGL_VM_TYPE *)VM_ARG)->compile;
	if(compile->LDAddrList.isInit)
		return;
	compile->LDAddrList.size = ZL_LD_ADDRLIST_SIZE;
	compile->LDAddrList.count = 0;
	compile->LDAddrList.addr = (ZENGL_LD_ADDR_TYPE *)compile->memAlloc(VM_ARG,compile->LDAddrList.size * sizeof(ZENGL_LD_ADDR_TYPE));
	if(compile->LDAddrList.addr == ZL_NULL)
		compile->exit(VM_ARG,ZL_ERR_CP_LD_ADDR_LIST_MALLOC_FAILED);
	ZENGL_SYS_MEM_SET(compile->LDAddrList.addr,0,compile->LDAddrList.size * sizeof(ZENGL_LD_ADDR_TYPE));
	compile->LDAddrList.isInit = ZL_TRUE;
}