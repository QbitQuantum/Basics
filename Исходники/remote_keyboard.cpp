LRESULT RemoteKeyboard::OnUpdateStatus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandle)
{
	static bool _last_enabled = true;
	bool _enable = (wParam != 0);
	unsigned int _check_value = (unsigned int)(lParam);
	TCHAR name[32];

	if (_last_enabled != _enable) {
		_last_enabled = _enable;
		for (int i = 1;; ++i) {
			_stprintf_s(name, sizeof(name) / sizeof(TCHAR), _T("rkbc_%02d"), i);
			if (!EnableControl(name, _last_enabled))
				break;
		}
	}

	if (_last_enabled) {
		unsigned int _recode_status = _check_value & 0x3;
		unsigned int _ch_status = (_check_value >> 2) & 0xf;
		unsigned int _director_status = (_check_value >> 6) & 0x3;

		for (int i = 1; i < 14; ++i) {
			_stprintf_s(name, sizeof(name) / sizeof(TCHAR), _T("rkbc_%02d"), i);

			if (i < 4) {
				EnableControl(name, _recode_status != i);
			} else if (i < 12) {
				EnableControl(name, _ch_status != i - 3);
			} else {
				EnableControl(name, _director_status != i - 11);
			}
		}
	}

	auto _GetExtendInfoWrap = [this](byte* &pBuf, long &nSize) -> boolean {
		boolean ret = false;

		RpcTryExcept
			ret = rkbc_GetExtendInfo(m_hwBinding, kExtendType_LessionInfo, __int64(m_lession_info_checksum), &pBuf, &nSize);
		RpcExcept(1)
			ret = false;
		RpcEndExcept

			return ret;
	};

	/* 如果同步排课界面不处于显示状态，则不刷新 */
	if (!m_PaintManager.FindControl(_T("sync_panel"))->IsVisible())	 
		return 0;
	byte *pBuf = 0;
	long nSize = 0;
	if (_enable && _GetExtendInfoWrap(pBuf, nSize) && pBuf) {
		auto const &items = g_LessionMappingTable;

		pugi::xml_document doc;
		if (doc.load(LPCTSTR(pBuf))) {
			pugi::xml_node elem = doc.child(_T("lesson"));
			if (elem) {
				for (int i = 0; i < _countof(items); ++i) {
					DuiLib::CControlUI *ctrl;
					if (ctrl = m_PaintManager.FindControl(items[i].name))
						ctrl->SetText(elem.attribute(items[i].attr).as_string());
				}

				m_lession_info = LPCTSTR(pBuf);
				boost::crc_32_type result;
				result.process_bytes(reinterpret_cast<const byte *>(m_lession_info.data()), (m_lession_info.size() + 1) * sizeof(wchar_t));
				m_lession_info_checksum = result.checksum();
			}
		}
		midl_user_free(pBuf);
	}

	return LRESULT();
}