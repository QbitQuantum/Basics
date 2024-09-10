	Color3 eval_reflect(const Vec3 &omega_out, const Vec3 &omega_in, float& pdf) const
	{
		if (Refractive == 1) return Color3(0, 0, 0);
		float cosNO = m_N.dot(omega_out);
		float cosNI = m_N.dot(omega_in);
		if (cosNI > 0 && cosNO > 0) {
			// get half vector
			Vec3 Hr = omega_in + omega_out;
			Hr.normalize();
			// eq. 20: (F*G*D)/(4*in*on)
			// eq. 33: first we calculate D(m) with m=Hr:
			float alpha2 = m_ag * m_ag;
			float cosThetaM = m_N.dot(Hr);
			float cosThetaM2 = cosThetaM * cosThetaM;
			float tanThetaM2 = (1 - cosThetaM2) / cosThetaM2;
			float cosThetaM4 = cosThetaM2 * cosThetaM2;
			float D = alpha2 / ((float) M_PI * cosThetaM4 * (alpha2 + tanThetaM2) * (alpha2 + tanThetaM2));
			// eq. 34: now calculate G1(i,m) and G1(o,m)
			float G1o = 2 / (1 + sqrtf(1 + alpha2 * (1 - cosNO * cosNO) / (cosNO * cosNO)));
			float G1i = 2 / (1 + sqrtf(1 + alpha2 * (1 - cosNI * cosNI) / (cosNI * cosNI)));
			float G = G1o * G1i;
			float out = (G * D) * 0.25f / cosNO;
			// eq. 24
			float pm = D * cosThetaM;
			// convert into pdf of the sampled direction
			// eq. 38 - but see also:
			// eq. 17 in http://www.graphics.cornell.edu/~bjw/wardnotes.pdf
			pdf = pm * 0.25f / Hr.dot(omega_out);
			return Color3(out, out, out);
		}
		return Color3(0, 0, 0);
	}