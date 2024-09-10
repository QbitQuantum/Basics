void LLManip::renderTickValue(const LLVector3& pos, F32 value, const std::string& suffix, const LLColor4 &color)
{
	LLLocale locale(LLLocale::USER_LOCALE);

	const LLFontGL* big_fontp = LLResMgr::getInstance()->getRes( LLFONT_SANSSERIF );
	const LLFontGL* small_fontp = LLResMgr::getInstance()->getRes( LLFONT_SANSSERIF_SMALL );

	std::string val_string;
	std::string fraction_string;
	F32 val_to_print = llround(value, 0.001f);
	S32 fractional_portion = llround(fmodf(llabs(val_to_print), 1.f) * 100.f);
	if (val_to_print < 0.f)
	{
		if (fractional_portion == 0)
		{
			val_string = llformat("-%d%s", lltrunc(llabs(val_to_print)), suffix.c_str());
		}
		else
		{
			val_string = llformat("-%d", lltrunc(llabs(val_to_print)));
		}
	}
	else
	{
		if (fractional_portion == 0)
		{
			val_string = llformat("%d%s", lltrunc(llabs(val_to_print)), suffix.c_str());
		}
		else
		{
			val_string = llformat("%d", lltrunc(val_to_print));
		}
	}

	BOOL hud_selection = mObjectSelection->getSelectType() == SELECT_TYPE_HUD;
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	LLVector3 render_pos = pos;
	if (hud_selection)
	{
		F32 zoom_amt = gAgent.mHUDCurZoom;
		F32 inv_zoom_amt = 1.f / zoom_amt;
		// scale text back up to counter-act zoom level
		render_pos = pos * zoom_amt;
		glScalef(inv_zoom_amt, inv_zoom_amt, inv_zoom_amt);
	}

	LLColor4 shadow_color = LLColor4::black;
	shadow_color.mV[VALPHA] = color.mV[VALPHA] * 0.5f;

	if (fractional_portion != 0)
	{
		fraction_string = llformat("%c%02d%s", LLResMgr::getInstance()->getDecimalPoint(), fractional_portion, suffix.c_str());

		gViewerWindow->setupViewport(1, -1);
		hud_render_utf8text(val_string, render_pos, *big_fontp, LLFontGL::NORMAL, -1.f * big_fontp->getWidthF32(val_string), 3.f, shadow_color, hud_selection);
		hud_render_utf8text(fraction_string, render_pos, *small_fontp, LLFontGL::NORMAL, 1.f, 3.f, shadow_color, hud_selection);

		gViewerWindow->setupViewport();
		hud_render_utf8text(val_string, render_pos, *big_fontp, LLFontGL::NORMAL, -1.f * big_fontp->getWidthF32(val_string), 3.f, color, hud_selection);
		hud_render_utf8text(fraction_string, render_pos, *small_fontp, LLFontGL::NORMAL, 1.f, 3.f, color, hud_selection);
	}
	else
	{
		gViewerWindow->setupViewport(1, -1);
		hud_render_utf8text(val_string, render_pos, *big_fontp, LLFontGL::NORMAL, -0.5f * big_fontp->getWidthF32(val_string), 3.f, shadow_color, hud_selection);
		gViewerWindow->setupViewport();
		hud_render_utf8text(val_string, render_pos, *big_fontp, LLFontGL::NORMAL, -0.5f * big_fontp->getWidthF32(val_string), 3.f, color, hud_selection);
	}
	glPopMatrix();
}