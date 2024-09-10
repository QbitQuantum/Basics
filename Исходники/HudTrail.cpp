void HudTrail::Render(Graphics::Renderer *r)
{
	PROFILE_SCOPED();
	//render trail
	if (m_trailPoints.size() > 1) {
		const vector3d vpos = m_transform * m_body->GetInterpPosition();
		m_transform[12] = vpos.x;
		m_transform[13] = vpos.y;
		m_transform[14] = vpos.z;
		m_transform[15] = 1.0;

		static std::vector<vector3f> tvts;
		static std::vector<Color> colors;
		tvts.clear();
		colors.clear();
		const vector3d curpos = m_body->GetInterpPosition();
		tvts.reserve(MAX_POINTS);
		colors.reserve(MAX_POINTS);
		tvts.push_back(vector3f(0.f));
		colors.push_back(Color::BLANK);
		float alpha = 1.f;
		const float decrement = 1.f / m_trailPoints.size();
		const Color tcolor = m_color;
		for (size_t i = m_trailPoints.size()-1; i > 0; i--) {
			tvts.push_back(-vector3f(curpos - m_trailPoints[i]));
			alpha -= decrement;
			colors.push_back(tcolor);
			colors.back().a = Uint8(alpha * 255);
		}

		r->SetTransform(m_transform);
		m_lines.SetData(tvts.size(), &tvts[0], &colors[0]);
		m_lines.Draw(r, m_renderState, Graphics::LINE_STRIP);
	}
}