bool loadEIOSClient(EIOSClient *client, char *path)
{
    memset(client, 0, sizeof(EIOSClient));
    client->libHandle = loadModule(path);

    if (client->libHandle == NULL)
        return false;

    client->requestTarget = (requestTargetT)getModuleFunc(client->libHandle, "EIOS_RequestTarget");
    client->releaseTarget = (releaseTargetT)getModuleFunc(client->libHandle, "EIOS_ReleaseTarget");

    client->getTargetDimensions = (getTargetDimensionsT)getModuleFunc(client->libHandle, "EIOS_GetTargetDimensions");
    client->getTargetPosition = (getTargetPositionT)getModuleFunc(client->libHandle, "EIOS_GetTargetPosition");

    client->getImageBuffer = (getImageBufferT)getModuleFunc(client->libHandle, "EIOS_GetImageBuffer");
    client->updateImageBuffer = (updateImageBufferT)getModuleFunc(client->libHandle, "EIOS_UpdateImageBuffer");
    client->updateImageBufferBox = (updateImageBufferBoxT)getModuleFunc(client->libHandle, "EIOS_UpdateImageBufferBounds");

    client->getMousePosition = (getMousePositionT)(getMousePositionT)getModuleFunc(client->libHandle, "EIOS_GetMousePosition");
    client->moveMouse = (moveMouseT)(moveMouseT)getModuleFunc(client->libHandle, "EIOS_MoveMouse");
    client->scrollMouse = (scrollMouseT)getModuleFunc(client->libHandle, "EIOS_ScrollMouse");
    client->holdMouse = (holdMouseT)getModuleFunc(client->libHandle, "EIOS_HoldMouse");
    client->releaseMouse = (releaseMouseT)getModuleFunc(client->libHandle, "EIOS_ReleaseMouse");
    client->isMouseButtonHeld = (isMouseButtonHeldT)getModuleFunc(client->libHandle, "EIOS_IsMouseButtonHeld");

    client->sendString = (sendStringT)getModuleFunc(client->libHandle, "EIOS_SendString");
    client->holdKey = (holdKeyT)getModuleFunc(client->libHandle, "EIOS_HoldKey");
    client->releaseKey = (releaseKeyT)getModuleFunc(client->libHandle, "EIOS_ReleaseKey");
    client->isKeyHeld = (isKeyHeldT)getModuleFunc(client->libHandle, "EIOS_IsKeyHeld");
    client->getKeyCode = (getKeyCodeT)getModuleFunc(client->libHandle, "EIOS_GetKeyCode");

    return true;
}