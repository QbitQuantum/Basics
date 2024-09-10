		BC_PLATFORMIMP_DLL
		bc_platform_script_error<core_platform::g_api_win32>::bc_platform_script_error(bc_script_context& p_context, const core::bc_wstring& p_message)
		{
			bc_chakra_call l_call(p_context);
			JsValueRef l_error_value;

			l_call = JsPointerToString(p_message.c_str(), p_message.length(), &l_error_value);
			l_call = JsCreateError(l_error_value, &m_pack.m_js_error);
		}