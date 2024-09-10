MINLINE void ushort_to_byte_dither_v4(uchar b[4], const unsigned short us[4], DitherContext *di, float s, float t)
{
#define USHORTTOFLOAT(val) ((float)val / 65535.0f)
	float dither_value = dither_random_value(s, t) * 0.005f * di->dither;

	b[0] = ftochar(dither_value + USHORTTOFLOAT(us[0]));
	b[1] = ftochar(dither_value + USHORTTOFLOAT(us[1]));
	b[2] = ftochar(dither_value + USHORTTOFLOAT(us[2]));
	b[3] = USHORTTOUCHAR(us[3]);

#undef USHORTTOFLOAT
}