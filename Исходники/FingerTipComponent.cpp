void FingerTipComponent::OnGUIRender(GUI::IGUIRenderer* renderer, const math::rectf& vp)
{
	VT::MountableComponent::OnGUIRender(renderer,vp);
	math::vector2d p;
	p.x = vp.ULPoint.x+m_projPos.x*vp.getWidth();
	p.y = vp.ULPoint.y + m_projPos.y*vp.getHeight();
	renderer->AddQuad(0, math::rectf(p.x - 5, p.y - 5, p.x + 5, p.y + 5), math::rectf(0, 0, 1, 1), 1);

	GUI::IFont* font = gFontResourceManager.getDefaultFont();
	GUI::FontAttributes attr;
	video::IVideoDevice* dev = Engine::getInstance().getDevice();
	AppData* app = AppData::Instance();
	if (font)
	{
		attr.fontColor.Set(1, 0, 0, 1);
		attr.fontAligment = GUI::EFA_TopLeft;
		attr.fontSize = 18;
		attr.hasShadow = true;
		attr.shadowColor.Set(0, 0, 0, 1);
		attr.shadowOffset = math::vector2d(2);
		attr.spacing = 2;
		attr.wrap = 0;
		attr.RightToLeft = 0;

		math::rectf r = vp;
		r.ULPoint.y += 30*m_index;

		core::string msg = mT("Finger: ") + m_name + " - Proj=" + core::StringConverter::toString(m_depthSpace) + " - Force=" + core::StringConverter::toString(m_force);
		font->print(r, &attr, 0, msg, renderer);
		r.ULPoint.y += attr.fontSize + 5;
	}

}