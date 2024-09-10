//*****************************************************************************
// クラス設計
LRESULT CALLBACK WindowProcedure(
	HWND handle_window,
	UINT message,
	WPARAM w_paramater,
	LPARAM l_paramater)
{
	switch (message)
	{
		case WM_CREATE:
		{
			// windowを真ん中
			wow::WindowCenter(handle_window);
			// ドラッグドロップを有効にする
			DragAcceptFiles(handle_window, TRUE);

			break;
		}
		case WM_DESTROY:
		{
			// システムに終了を要求
			PostQuitMessage(0);
			break;
		}
		case WM_CLOSE:
		{
			// 指定されたウィンドウを破棄
			DestroyWindow(handle_window);
			break;
		}
		case WM_DROPFILES:
		{
			// ドラッグした位置を取得
			POINT mouse_position;
			GetCursorPos(&mouse_position);
			 ScreenToClient(
				 handle_window,		// ウィンドウのハンドル
				 &mouse_position);	// スクリーン座標

			 // ドラッグしたファイル名を取得
			 HDROP drop = (HDROP)w_paramater;
			 char file_name[256];
			 DragQueryFileA(drop, 0, file_name, 256);
			 DragFinish(drop);

			 break;
		}
		
		case WM_LBUTTONDOWN:
		{

			break;
		}
		case WM_KEYDOWN:
		{
			switch (w_paramater)
			{
				case VK_ESCAPE:
					DestroyWindow(handle_window);
				break;
			}
			break;
		}
	}

	// デフォルトの処理を返す
	return DefWindowProc(handle_window, message, w_paramater, l_paramater);
}