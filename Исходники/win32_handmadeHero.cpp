LRESULT CALLBACK MainWindowCallback(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam) {
	LRESULT result = NULL;
	switch (message) {
	case WM_SIZE: {
	}	break;
	case WM_DESTROY: {
	}	break;
	case WM_CLOSE: {
	}	break;
	case WM_ACTIVATEAPP: {
	}	break;
	case WM_PAINT: {
		PAINTSTRUCT paint;
		HDC deviceContext = BeginPaint(windowHandle, &paint);
		int height = paint.rcPaint.bottom - paint.rcPaint.top;
		int width = paint.rcPaint.right - paint.rcPaint.left;
		PatBlt(deviceContext, paint.rcPaint.left, paint.rcPaint.top, width, height, WHITENESS);
		EndPaint(windowHandle, &paint);
	}	break;
	default: {
		result = DefWindowProc(windowHandle, message, wParam, lParam);
	}	break;
	}
	return result;
}