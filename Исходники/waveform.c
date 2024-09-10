float poly_triangle(float amplitude, float freq, float phase)
{
	// Triangle wave implemented as absolute value of sawtooth wave:
	// (signal amplitude) * (peak amplitude) * (2 * abs(sawtooth(t, phase)) - 1)
	return amplitude * POLY_MAX_AMP * (2 * fabsf(2 * (freq * (((float)poly_time)/(poly_format->rate) + phase*(1.0/freq)) - floorf(0.5 + (((float)poly_time)/(poly_format->rate) + phase*(1.0/freq)) * freq))) - 1);
}