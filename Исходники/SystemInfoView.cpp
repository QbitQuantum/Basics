void SystemInfoView::BodyIcon::Draw()
{
	Gui::ImageRadioButton::Draw();
	if (!GetSelected()) return;
	float size[2];
	GetSize(size);
	Color green = Color(0.f, 1.f, 0.f, 1.f);
	const vector2f vts[] = {
		vector2f(0.f, 0.f),
		vector2f(size[0], 0.f),
		vector2f(size[0], size[1]),
		vector2f(0.f, size[1]),
	};
	m_renderer->DrawLines2D(4, vts, green, Graphics::LINE_LOOP);
}