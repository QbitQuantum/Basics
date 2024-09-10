void CreateFont(CCallParams& p)
{
	if (p.AsString(0) == "" || GetFont(p.AsString(0)) != 0)return;
	CBaseOglControl* ctrl = CBaseOglControl::controls[WindowFromDC(wglGetCurrentDC())];
	if (ctrl == 0)return;
	CBaseFont *f = ctrl->Collection().FontsList().Create(p.AsString(0));
	if (f == 0)return;
	f->SetSprite(ctrl->Collection().SpriteList().Get(p.AsString(1)));
}