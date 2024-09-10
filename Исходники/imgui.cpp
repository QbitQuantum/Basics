bool imguiSlider(const char* text, float* val, float vmin, float vmax, float vinc, bool enabled)
{
	g_state.widgetId++;
	unsigned int id = (g_state.areaId<<16) | g_state.widgetId;
	
	int x = g_state.widgetX;
	int y = g_state.widgetY - BUTTON_HEIGHT;
	int w = g_state.widgetW;
	int h = SLIDER_HEIGHT;
	g_state.widgetY -= SLIDER_HEIGHT + DEFAULT_SPACING;

	addGfxCmdRoundedRect((float)x, (float)y, (float)w, (float)h, 4.0f, imguiRGBA(0,0,0,128));

	const int range = w - SLIDER_MARKER_WIDTH;

	float u = (*val - vmin) / (vmax-vmin);
	if (u < 0) u = 0;
	if (u > 1) u = 1;
	int m = (int)(u * range);

	bool over = enabled && inRect(x+m, y, SLIDER_MARKER_WIDTH, SLIDER_HEIGHT);
	bool res = buttonLogic(id, over);
	bool valChanged = false;

	if (isActive(id))
	{
		if (g_state.wentActive)
		{
			g_state.dragX = g_state.mx;
			g_state.dragOrig = u;
		}
		if (g_state.dragX != g_state.mx)
		{
			u = g_state.dragOrig + (float)(g_state.mx - g_state.dragX) / (float)range;
			if (u < 0) u = 0;
			if (u > 1) u = 1;
			*val = vmin + u*(vmax-vmin);
			*val = floorf(*val / vinc)*vinc; // Snap to vinc
			m = (int)(u * range);
			valChanged = true;
		}
	}

	if (isActive(id))
		addGfxCmdRoundedRect((float)(x+m), (float)y, (float)SLIDER_MARKER_WIDTH, (float)SLIDER_HEIGHT, 4.0f, imguiRGBA(255,255,255,255));
	else
		addGfxCmdRoundedRect((float)(x+m), (float)y, (float)SLIDER_MARKER_WIDTH, (float)SLIDER_HEIGHT, 4.0f, isHot(id) ? imguiRGBA(255,196,0,128) : imguiRGBA(255,255,255,64));

	// TODO: fix this, take a look at 'nicenum'.
	int digits = (int)(ceilf(log10f(vinc)));
	char fmt[16];
	snprintf(fmt, 16, "%%.%df", digits >= 0 ? 0 : -digits);
	char msg[128];
	snprintf(msg, 128, fmt, *val);
	
	if (enabled)
	{
		addGfxCmdText(x+SLIDER_HEIGHT/2, y+SLIDER_HEIGHT/2-TEXT_HEIGHT/2, IMGUI_ALIGN_LEFT, text, isHot(id) ? imguiRGBA(255,196,0,255) : imguiRGBA(255,255,255,200));
		addGfxCmdText(x+w-SLIDER_HEIGHT/2, y+SLIDER_HEIGHT/2-TEXT_HEIGHT/2, IMGUI_ALIGN_RIGHT, msg, isHot(id) ? imguiRGBA(255,196,0,255) : imguiRGBA(255,255,255,200));
	}
	else
	{
		addGfxCmdText(x+SLIDER_HEIGHT/2, y+SLIDER_HEIGHT/2-TEXT_HEIGHT/2, IMGUI_ALIGN_LEFT, text, imguiRGBA(128,128,128,200));
		addGfxCmdText(x+w-SLIDER_HEIGHT/2, y+SLIDER_HEIGHT/2-TEXT_HEIGHT/2, IMGUI_ALIGN_RIGHT, msg, imguiRGBA(128,128,128,200));
	}

	return res || valChanged;
}