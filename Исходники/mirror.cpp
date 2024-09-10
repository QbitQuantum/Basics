	Spectrum sample(BSDFQueryRecord &bRec, Float &pdf, const Point2 &sample) const {
		if (!(bRec.typeMask & m_combinedType))
			return Spectrum(0.0f);
		reflect(bRec.wi, bRec.wo);
		bRec.sampledComponent = 0;
		bRec.sampledType = EDeltaReflection;
		pdf = std::abs(Frame::cosTheta(bRec.wo));
		return m_reflectance;
	}