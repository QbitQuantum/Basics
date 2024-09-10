void rgbe_to_rgb(RGB& rgb, RGBE const rgbe, float const gamma)
{
	if (rgbe.e)
	{
		int const exponent = rgbe.e - 128;
		float const scale = (1.f/256.f) * ldexpf(1.f, exponent);
		rgb.r = powf(scale * rgbe.r, gamma);
		rgb.g = powf(scale * rgbe.g, gamma);
		rgb.b = powf(scale * rgbe.b, gamma);
	}
	else
	{
		rgb = RGB();
	}
}