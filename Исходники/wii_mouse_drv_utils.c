BOOL WiiMouse_DrvUtil_GetInterfaceHandles(WiiMouse_HandleInfo_t *handleInfo)
{
    BOOL retval = FALSE;
    UCHAR interfaceIndex = 0;
    UCHAR pipeIndex = 0;
    USB_INTERFACE_DESCRIPTOR usbInterfaceDesc;
    WINUSB_PIPE_INFORMATION pipeInfo;

    while( WinUsb_QueryInterfaceSettings(handleInfo->winUsbHandle, interfaceIndex, &usbInterfaceDesc) )
    {
        if( _IsValidInterface(&usbInterfaceDesc) )
        {
            break;
        }

        interfaceIndex++;
    }

    if( GetLastError() == ERROR_INVALID_HANDLE )
    {
        WiiMouse_AddMsg(DERR,"Error, WinUsb_QueryInterfaceSettings invalid handle\n");
        return FALSE;
    }

    if( !WinUsb_GetAssociatedInterface(handleInfo->winUsbHandle, interfaceIndex, &handleInfo->interfaceHandle) )
    {
        DWORD err = GetLastError();

        if( err != ERROR_ALREADY_EXISTS )
        {
            WiiMouse_AddMsg(DERR,"Error, WinUsb_GetAssociatedInterface failed: %d\n", err);
            return FALSE;
        }
        else
        {
            handleInfo->interfaceHandle = handleInfo->winUsbHandle;
            handleInfo->interfaceId = 0;
        }
    }
    handleInfo->interfaceId = interfaceIndex;

    for( pipeIndex = 0; pipeIndex < usbInterfaceDesc.bNumEndpoints; pipeIndex++ )
    {
        if( !WinUsb_QueryPipe(handleInfo->winUsbHandle, interfaceIndex, pipeIndex, &pipeInfo) )
        {
            WiiMouse_AddMsg(DERR,"Error, WinUsb_QueryPipe failed: %d\n", GetLastError());
            retval = FALSE;
            break;
        }
        else
        {
            _SetEndpoint(handleInfo, &pipeInfo);
        }
    }

   /* if( !_ValidateEndpoints(handleInfo) )
    {
         WiiMouse_AddMsg(DERR,"Error, endpoint validation failed\n");
         retval = FALSE;
    }*/
    
    if( !retval )
    {
        WinUsb_Free(handleInfo->interfaceHandle);
    }


    return retval;
}