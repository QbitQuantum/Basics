/*++
* @name DxEngLockShareSem
* @implemented
*
* The function DxEngLockShareSem locks a struct of type ghsemShareDevLock that can be shared.
*
* @return
* This function returns TRUE for success and FALSE for failure.
* FALSE must mean the struct has already been locked.
*
* @remarks.
* It is being used in various ntuser* functions and ntgdi*
* ReactOS specific: It is not in use yet?
*SystemResourcesList
*--*/
BOOLEAN
APIENTRY
DxEngLockShareSem()
{
    DPRINT1("ReactX Calling : DxEngLockShareSem\n");
    if(!ghsemShareDevLock) ghsemShareDevLock = EngCreateSemaphore(); // Hax, should be in dllmain.c
    IntGdiAcquireSemaphore(ghsemShareDevLock);
    return TRUE;
}