int m_exec(wchar_t* app, int param_count, wchar_t* param[]) 
{
	if (param_count <= 0) {
		return 0;
	} 

	bool valid = false;
	std::wstring action ;
	long x, y;
	std::wstring win_name;
	std::wstring btn_event;
	
	for (int i = 0; i < param_count; i++) {
		if (i == 1) {
			action = param[0];
		}
		else {
			if (action == L"m"
				|| action == L"to"
				) {
				wchar_t* end;
				x = std::wcstol(param[1], &end, 10);
				y = std::wcstol(param[2], &end, 10);
				if (param_count == 4) {
					btn_event = param[3];
				}
				break;
			}
			else if (action == L"w") {
				win_name = param[1];
				if (param_count == 3) {
					btn_event = param[2];
				}
				break;
			}
		}

	}

	if (action== L"m") {
		int ret = mouse_move(x, y);
		mouse_event(btn_event);
	} 
	else if (action == L"to") {
		int ret = mouse_move(x, y);
		mouse_event(btn_event);
	}
	else if (action == L"w") {
		int ret = mouse_to_window(win_name);
		mouse_event(btn_event);
	}
	else {
		print_usage(app);
	}

	
}