		BC_COREPLATFORMIMP_DLL
		void bc_platform_path<g_api_win32>::combine(const bc_platform_path& p_other)
		{
			bcECHAR l_buffer[MAX_PATH] = { '\0' };
			_copy_current_path_to_buffer(m_pack.m_path, l_buffer, MAX_PATH);

			win_call(PathCchCombine(l_buffer, MAX_PATH, m_pack.m_path.c_str(), p_other.m_pack.m_path.c_str()));

			m_pack.m_path.assign(l_buffer);
		}