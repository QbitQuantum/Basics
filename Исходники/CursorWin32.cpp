void Cursor::Show(bool _show)
{
	show = _show;
	LPDIRECT3DDEVICE9 device = RenderManager::Instance()->GetD3DDevice();
	device->ShowCursor(show);
}