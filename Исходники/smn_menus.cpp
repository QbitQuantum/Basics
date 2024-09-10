static cell_t CreateMenu(IPluginContext *pContext, const cell_t *params)
{
    IMenuStyle *style = g_Menus.GetDefaultStyle();
    IPluginFunction *pFunction;

    if ((pFunction=pContext->GetFunctionById(params[1])) == NULL)
    {
        return pContext->ThrowNativeError("Function id %x is invalid", params[1]);
    }

    CMenuHandler *handler = g_MenuHelpers.GetMenuHandler(pFunction, params[2]);
    IBaseMenu *menu = style->CreateMenu(handler, pContext->GetIdentity());

    Handle_t hndl = menu->GetHandle();
    if (!hndl)
    {
        menu->Destroy();
        return BAD_HANDLE;
    }

    return hndl;
}