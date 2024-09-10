void TextureCreate(CCallParams& p) //создание текстуры и загрузка картинки
{
	CBaseOglControl* ctrl = CBaseOglControl::controls[WindowFromDC(wglGetCurrentDC())];
	if (0 == ctrl || p.AsString(0) == "")return;
	ctrl->Collection().TextureList().Create(p.AsString(0));
	CBaseTexture* tex = GetTexture(p.AsString(0));
	if (tex != 0) tex->LoadTexture(p.AsString(1));
}