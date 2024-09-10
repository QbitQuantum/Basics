static HRESULT drawThemedCheckbox(struct drawState *s, HTHEME theme, int checked, int enabled)
{
	RECT r;
	SIZE size;
	int state;
	HRESULT hr;

	hr = GetThemePartSize(theme, s->dc,
		BP_CHECKBOX, CBS_UNCHECKEDNORMAL,
		NULL, TS_DRAW, &size);
	if (hr != S_OK) {
		logHRESULT(L"GetThemePartSize()", hr);
		return hr;			// TODO fall back?
	}
	r = s->m->subitemIcon;
	r.right = r.left + size.cx;
	r.bottom = r.top + size.cy;

	centerImageRect(&r, &(s->m->subitemIcon));
	if (!checked && enabled)
		state = CBS_UNCHECKEDNORMAL;
	else if (checked && enabled)
		state = CBS_CHECKEDNORMAL;
	else if (!checked && !enabled)
		state = CBS_UNCHECKEDDISABLED;
	else
		state = CBS_CHECKEDDISABLED;
	hr = DrawThemeBackground(theme, s->dc,
		BP_CHECKBOX, state,
		&r, NULL);
	if (hr != S_OK) {
		logHRESULT(L"DrawThemeBackground()", hr);
		return hr;
	}
	return S_OK;
}