void _fastcall 
    CC_Put_globals_Hook(DWORD OutClass)
{
	CHAR szConfigPath[MAX_PATH];
	PathCombineA(szConfigPath, g_szDllPath, "YDTrigger.ini");

    CreateDefine(BlizzardJ, USE_BJ_ANTI_LEAK);
    CreateDefine(BlizzardJ, USE_BJ_OPTIMIZATION);
    CreateDefine(BlizzardJ, USE_BJ_OPTIMIZATION_PRO);
    CreateDefine(BlizzardJ, USE_BJ_INLINE);

    CC_PutString(OutClass, 0, "#include <YDTrigger/Import.h>", 1);
    CC_PutString(OutClass, 0, "#include <YDTrigger/YDTrigger.h>", 1);
    CC_PutString(OutClass, 0, "globals", 1);
    ((DWORD*)OutClass)[3]++;
}