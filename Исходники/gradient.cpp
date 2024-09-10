void Gradient::Draw()
{
	Graphics::Renderer *r = GetContext()->GetRenderer();
	if (!m_quad) {
		const Point &offset = GetActiveOffset();
		const Point &area = GetActiveArea();

		const float x = offset.x;
		const float y = offset.y;
		const float sx = area.x;
		const float sy = area.y;

		Graphics::VertexArray va(Graphics::ATTRIB_POSITION | Graphics::ATTRIB_DIFFUSE);
		va.Add(vector3f(x, y, 0.0f), m_beginColor);
		va.Add(vector3f(x, y + sy, 0.0f), m_direction == HORIZONTAL ? m_beginColor : m_endColor);
		va.Add(vector3f(x + sx, y, 0.0f), m_direction == HORIZONTAL ? m_endColor : m_beginColor);
		va.Add(vector3f(x + sx, y + sy, 0.0f), m_endColor);

		auto renderState = GetContext()->GetSkin().GetAlphaBlendState();
		m_quad.reset(new Graphics::Drawables::TexturedQuad(r, m_material, va, renderState));
	}
	m_quad->Draw(r, Color(Color::WHITE.r, Color::WHITE.g, Color::WHITE.b, GetContext()->GetOpacity()*Color::WHITE.a));

	Container::Draw();
}