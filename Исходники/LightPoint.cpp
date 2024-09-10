	void LightPoint::update_radius() {
		XMVECTOR v = colorv();
		float r = XMVectorGetX(v);
		float g = XMVectorGetY(v);
		float b = XMVectorGetZ(v);
		float max = std::fmaxf(std::fmaxf(r, g), b);
		m_radius = (-m_linear +
					std::sqrtf(m_linear * m_linear -
							   4 * m_quadratic * (m_constant - 256.0f * intensity() * max)))
			/ (2 * m_quadratic);
	}