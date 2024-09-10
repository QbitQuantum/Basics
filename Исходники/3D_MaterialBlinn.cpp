void MtlBlinnSW3D::Transmit(ShadeContext3D &sc)
{
	BlinnBlock &block = (BlinnBlock &) sc.GetMaterialBlock(this);
	const Vector4f &vertexColor = IsSet(block.VertexColor) ? *block.VertexColor : WHITE4F;

	Color4f diffuseMtl;

	if (DiffuseMtl)
	{
		DiffuseMtl->Shade(sc);
		diffuseMtl = *block.Color;
	}
	else
		diffuseMtl = WHITE4F;

	Color4f Kd = Mul(PreDiffuse, Mul(diffuseMtl, vertexColor));

	if (fabs(Kd.A) < 0.0001f)
		Kd = Color4f(1.0f, 1.0f, 1.0f, 0.0f);
	else
	{
		Kd.R /= Kd.A;
		Kd.G /= Kd.A;
		Kd.B /= Kd.A;
	}

	float32 y = Kd.Luminance();
	Color4f satColor = Lerp(Color4f(y, y, y, 1.0f), Kd, Saturation);
	satColor.A = 1.0f;

	Color4f textureDetail = Lerp(Color4f(0.0f, 0.0f, 0.0f, 1.0f), satColor, ColorDetail);
	textureDetail.A = 1.0f;

	float32 alphaDetail = Lerp(0.0f, 1.0f - Kd.A, AlphaDetail);
	Color4f outTrans = (1.0f - alphaDetail) * textureDetail + Color4f(alphaDetail);			// compute 1 - (1 - ad) * (1 - td)

	outTrans = Color4f(1.0f) - Mul(Color4f(1.0f) - outTrans, Color4f(1.0f) - Transmittance);

	sc.Transmittance.R = max(min(outTrans.R, 1.0f), 0.0f);
	sc.Transmittance.G = max(min(outTrans.G, 1.0f), 0.0f);
	sc.Transmittance.B = max(min(outTrans.B, 1.0f), 0.0f);
	sc.Transmittance.A = outTrans.A;

	FuASSERT(sc.Transmittance.A >= 0.0f && sc.Transmittance.A <= 1.002f, (""));
}