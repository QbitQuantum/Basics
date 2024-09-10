	LUA_METHOD_IMPL(CLabelUI, SetTextColor)
	{
		try
		{
			CLabelUI* self;
			self = static_cast<CLabelUI*>(LuaStatic::CheckUserData(l, 1));

			DWORD dwBkCor = LuaStatic::ReadRGBAFromLua(l, 2);

			self->SetTextColor(dwBkCor);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCLabelUI::SetTextColor"));
			return 0;
		}
	}