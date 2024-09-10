	Color3 eval_reflect(const Vec3 &omega_out, const Vec3 &omega_in, float &pdf) const
	{
		// pdf is implicitly 0 (no indirect sampling)
		float cosNO = m_N.dot(omega_out);
		float cosNI = m_N.dot(omega_in);
		if (cosNO > 0 && cosNI > 0) {
			float sinNO2 = 1 - cosNO * cosNO;
			pdf = cosNI * float(M_1_PI);
			float westin = sinNO2 > 0 ? powf(sinNO2, 0.5f * m_edginess) * pdf : 0;
			return Color3(westin, westin, westin);
		}
		return Color3(0, 0, 0);
	}