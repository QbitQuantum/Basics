static LRESULT CALLBACK cliprdr_proc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	static cliprdrContext *cliprdr = NULL;

	switch (Msg)
	{
		case WM_CREATE:
			cliprdr = (cliprdrContext *)((CREATESTRUCT *)lParam)->lpCreateParams;
			cliprdr->hwndNextViewer = SetClipboardViewer(hWnd);

			if (cliprdr->hwndNextViewer == NULL && GetLastError() != 0)
			{
				DEBUG_CLIPRDR("error: SetClipboardViewer failed with 0x%0x.", GetLastError());
			}
			cliprdr->hwndClipboard = hWnd;
			break;

		case WM_CLOSE:
			ChangeClipboardChain(hWnd, cliprdr->hwndNextViewer);
			break;

		case WM_CHANGECBCHAIN:
			if (cliprdr->hwndNextViewer == (HWND)wParam)
			{
				cliprdr->hwndNextViewer = (HWND)lParam;
			}
			else if (cliprdr->hwndNextViewer != NULL)
			{
				SendMessage(cliprdr->hwndNextViewer, Msg, wParam, lParam);
			}
			break;

		case WM_DRAWCLIPBOARD:
			if (cliprdr->channel_initialized)
			{
				if ((GetClipboardOwner() != cliprdr->hwndClipboard) && (S_FALSE == OleIsCurrentClipboard(cliprdr->data_obj)))
				{
						if (!cliprdr->hmem)
						{
							cliprdr->hmem = GlobalFree(cliprdr->hmem);
						}
						cliprdr_send_format_list(cliprdr);
				}
			}
			if (cliprdr->hwndNextViewer != NULL && cliprdr->hwndNextViewer != hWnd)
				SendMessage(cliprdr->hwndNextViewer, Msg, wParam, lParam);
			break;

		case WM_RENDERALLFORMATS:
			/* discard all contexts in clipboard */
			if (!OpenClipboard(cliprdr->hwndClipboard))
			{
				DEBUG_CLIPRDR("OpenClipboard failed with 0x%x", GetLastError());
				break;
			}
			EmptyClipboard();
			CloseClipboard();
			break;

		case WM_RENDERFORMAT:
			if (cliprdr_send_data_request(cliprdr, (UINT32)wParam) != 0)
			{
				DEBUG_CLIPRDR("error: cliprdr_send_data_request failed.");
				break;
			}

			if (SetClipboardData((UINT) wParam, cliprdr->hmem) == NULL)
			{
				DEBUG_CLIPRDR("SetClipboardData failed with 0x%x", GetLastError());
				cliprdr->hmem = GlobalFree(cliprdr->hmem);
			}
			/* Note: GlobalFree() is not needed when success */
			break;

		case WM_CLIPRDR_MESSAGE:
			switch (wParam)
			{
				case OLE_SETCLIPBOARD:
					if (wf_create_file_obj(cliprdr, &cliprdr->data_obj))
						if (OleSetClipboard(cliprdr->data_obj) != S_OK)
							wf_destroy_file_obj(cliprdr->data_obj);
					break;

				default:
					break;
			}
			break;

		case WM_CLIPBOARDUPDATE:
		case WM_DESTROYCLIPBOARD:
		case WM_ASKCBFORMATNAME:
		case WM_HSCROLLCLIPBOARD:
		case WM_PAINTCLIPBOARD:
		case WM_SIZECLIPBOARD:
		case WM_VSCROLLCLIPBOARD:
		default:
			return DefWindowProc(hWnd, Msg, wParam, lParam);
	}

	return 0;
}