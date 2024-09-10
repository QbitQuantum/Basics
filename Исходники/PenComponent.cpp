void PenComponent::OnGUIRender(GUI::IGUIRenderer* renderer, const math::rectf& vp)
{
	MountableComponent::OnGUIRender(renderer, vp);
	video::IVideoDevice* device= Engine::getInstance().getDevice();
	if (m_points.points.size() > 1)
	{
		device->setLineWidth(m_points.width);
		std::vector<math::vector2d> pts;
		pts.resize(m_points.points.size());
		for (int i = 0; i < m_points.points.size(); ++i)
		{
			pts[i] = m_points.points[i] * vp.getSize();
		}
		device->draw2DLine(&pts[0], pts.size(), m_points.clr);
	}


	GUI::IFont* font = gFontResourceManager.getDefaultFont();
	GUI::FontAttributes attr;
	video::IVideoDevice* dev = Engine::getInstance().getDevice();
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
		r.ULPoint.y += 200;

		core::string msg = mT("Pos: ") + core::StringConverter::toString(m_currentProjPos);
		font->print(r, &attr, 0, msg, renderer);
		r.ULPoint.y += attr.fontSize + 5;
	}
}