void D3DDrawText(wchar_t *str)
{
	if (*str == L'\0') return;

	RECT rect;
	//SetRect(&rct, rect.left, rect.top, rect.right, rect.bottom);
	GetClientRect(hwnd, &rect);
	uint width = rect.right - rect.left;
	wstring wstr = addenter(str, width / 30);

	//pDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);
	pDevice->BeginScene();

	g_pTextSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);


	//描边
	rect.left += 2;
	g_pFont->DrawTextW(g_pTextSprite, wstr.c_str(), -1, &rect, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

	rect.left -= 2;
	rect.top += 2;
	g_pFont->DrawTextW(g_pTextSprite, wstr.c_str(), -1, &rect, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

	rect.left += 4;
	g_pFont->DrawTextW(g_pTextSprite, wstr.c_str(), -1, &rect, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

	rect.left -= 2;
	rect.top += 2;
	g_pFont->DrawTextW(g_pTextSprite, wstr.c_str(), -1, &rect, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

	//实体
	rect.top -= 2;
	g_pFont->DrawTextW(g_pTextSprite, wstr.c_str(), -1, &rect, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));
	g_pTextSprite->End();

	pDevice->EndScene();
	//pDevice->Present(&rect, &rect, 0, 0);
}