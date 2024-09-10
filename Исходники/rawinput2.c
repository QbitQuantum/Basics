static LRESULT WINAPI window_message_handler(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
		case WM_INPUT:
		{
			if (wparam == RIM_INPUT)
			{
				HRAWINPUT raw_input_handle = (HRAWINPUT)(lparam);
				int raw_input_size;
				RAWINPUT *raw_input;
				int raw_input_device_name_size;
				char *raw_input_device_name;

				GetRawInputData(raw_input_handle, RID_INPUT, NULL, &raw_input_size, sizeof(RAWINPUTHEADER));
				raw_input = (RAWINPUT *)(malloc(raw_input_size));
				GetRawInputData(raw_input_handle, RID_INPUT, raw_input, &raw_input_size, sizeof(RAWINPUTHEADER));

				GetRawInputDeviceInfo(raw_input->header.hDevice, RIDI_DEVICENAME, NULL, &raw_input_device_name_size);
				raw_input_device_name = malloc(raw_input_device_name_size);
				GetRawInputDeviceInfo(raw_input->header.hDevice, RIDI_DEVICENAME, raw_input_device_name, &raw_input_device_name_size);

				if (raw_input->header.dwType == RIM_TYPEKEYBOARD)
				{
					edit_control_printf("dev = %s, scancode = %d, vkey = %d, message = %d\r\n", raw_input_device_name, raw_input->data.keyboard.MakeCode, raw_input->data.keyboard.VKey, raw_input->data.keyboard.Message);
				}

				free(raw_input_device_name);
				free(raw_input);
			}

			return DefWindowProc(window, message, wparam, lparam);
		}
		case WM_SETFOCUS:
		{
			SetFocus(edit_control);
			return 0;
		}
		case WM_SIZE:
		{
			MoveWindow(edit_control, 0, 0, LOWORD(lparam), HIWORD(lparam), TRUE);
			return 0;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
		default:
		{
			return DefWindowProc(window, message, wparam, lparam);
		}
	}
}