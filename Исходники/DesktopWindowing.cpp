LRESULT DesktopWindowing::HandleRawInput(WPARAM wParam, LPARAM lParam) const
{
	unsigned int dataSize = 0;
	auto& input = Input::GetInstance();

	auto result = GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &dataSize, sizeof(RAWINPUTHEADER));
	auto buffer = unique_ptr<unsigned char[]>(new unsigned char[dataSize]);
	result = GetRawInputData((HRAWINPUT)lParam, RID_INPUT, buffer.get(), &dataSize, sizeof(RAWINPUTHEADER));

	RAWINPUT* raw = (RAWINPUT*)buffer.get();

	if (raw->header.dwType == RIM_TYPEKEYBOARD) 
	{
		if (raw->data.keyboard.Message == WM_KEYDOWN && wParam == 0)
		{
			input.KeyDown(raw->data.keyboard.VKey);
		}
		else if (raw->data.keyboard.Message == WM_KEYUP)
		{
			input.KeyUp(raw->data.keyboard.VKey);
		}
		return 0;
	}
	else if (raw->header.dwType == RIM_TYPEMOUSE && wParam == 0) 
	{
		switch (raw->data.mouse.usButtonFlags)
		{
		case RI_MOUSE_BUTTON_1_DOWN:
			input.MouseButtonDown(1);
			break;

		case RI_MOUSE_BUTTON_1_UP:
			input.MouseButtonUp(1);
			break;

		case RI_MOUSE_BUTTON_2_DOWN:
			input.MouseButtonDown(2);
			break;

		case RI_MOUSE_BUTTON_2_UP:
			input.MouseButtonUp(2);
			break;

		case RI_MOUSE_BUTTON_3_DOWN:
			input.MouseButtonDown(3);
			break;

		case RI_MOUSE_BUTTON_3_UP:
			input.MouseButtonUp(3);
			break;

		case RI_MOUSE_BUTTON_4_DOWN:
			input.MouseButtonDown(4);
			break;

		case RI_MOUSE_BUTTON_4_UP:
			input.MouseButtonUp(4);
			break;

		case RI_MOUSE_BUTTON_5_DOWN:
			input.MouseButtonDown(5);
			break;

		case RI_MOUSE_BUTTON_5_UP:
			input.MouseButtonUp(5);
			break;

		case RI_MOUSE_WHEEL:
			input.SetMouseWheelDisplacement(static_cast<long>(raw->data.mouse.usButtonData));
			break;
		}

		input.SetMouseDisplacement(raw->data.mouse.lLastX, raw->data.mouse.lLastY);
		return 0;
	}

	return DefRawInputProc(&raw, 1, sizeof(RAWINPUTHEADER));
}