IMPL_LUA_FUNC(LuaWindowExport, ArrangeIconicWindows)
{
    try
    {
        CLuaWindow* self;
        self = static_cast<CLuaWindow*>(LuaStatic::CheckUserData(l, 1));
        lua_pushnumber(l,self->ArrangeIconicWindows());
        return 1;
    }
    catch(...)
    {
        DuiException(_T("LuaWindowExport::ArrangeIconicWindows"));
        return 0;
    }
}