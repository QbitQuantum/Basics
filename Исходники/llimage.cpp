void LLImageRaw::copyLineScaled( U8* in, U8* out, S32 in_pixel_len, S32 out_pixel_len, S32 in_pixel_step, S32 out_pixel_step )
{
	const S32 components = getComponents();
	llassert( components >= 1 && components <= 4 );

	const F32 ratio = F32(in_pixel_len) / out_pixel_len; // ratio of old to new
	const F32 norm_factor = 1.f / ratio;

	S32 goff = components >= 2 ? 1 : 0;
	S32 boff = components >= 3 ? 2 : 0;
	for( S32 x = 0; x < out_pixel_len; x++ )
	{
		// Sample input pixels in range from sample0 to sample1.
		// Avoid floating point accumulation error... don't just add ratio each time.  JC
		const F32 sample0 = x * ratio;
		const F32 sample1 = (x+1) * ratio;
		const S32 index0 = llfloor(sample0);			// left integer (floor)
		const S32 index1 = llfloor(sample1);			// right integer (floor)
		const F32 fract0 = 1.f - (sample0 - F32(index0));	// spill over on left
		const F32 fract1 = sample1 - F32(index1);			// spill-over on right

		if( index0 == index1 )
		{
			// Interval is embedded in one input pixel
			S32 t0 = x * out_pixel_step * components;
			S32 t1 = index0 * in_pixel_step * components;
			U8* outp = out + t0;
			U8* inp = in + t1;
			for (S32 i = 0; i < components; ++i)
			{
				*outp = *inp;
				++outp;
				++inp;
			}
		}
		else
		{
			// Left straddle
			S32 t1 = index0 * in_pixel_step * components;
			F32 r = in[t1 + 0] * fract0;
			F32 g = in[t1 + goff] * fract0;
			F32 b = in[t1 + boff] * fract0;
			F32 a = 0;
			if( components == 4)
			{
				a = in[t1 + 3] * fract0;
			}
		
			// Central interval
			if (components < 4)
			{
				for( S32 u = index0 + 1; u < index1; u++ )
				{
					S32 t2 = u * in_pixel_step * components;
					r += in[t2 + 0];
					g += in[t2 + goff];
					b += in[t2 + boff];
				}
			}
			else
			{
				for( S32 u = index0 + 1; u < index1; u++ )
				{
					S32 t2 = u * in_pixel_step * components;
					r += in[t2 + 0];
					g += in[t2 + 1];
					b += in[t2 + 2];
					a += in[t2 + 3];
				}
			}

			// right straddle
			// Watch out for reading off of end of input array.
			if( fract1 && index1 < in_pixel_len )
			{
				S32 t3 = index1 * in_pixel_step * components;
				if (components < 4)
				{
					U8 in0 = in[t3 + 0];
					U8 in1 = in[t3 + goff];
					U8 in2 = in[t3 + boff];
					r += in0 * fract1;
					g += in1 * fract1;
					b += in2 * fract1;
				}
				else
				{
					U8 in0 = in[t3 + 0];
					U8 in1 = in[t3 + 1];
					U8 in2 = in[t3 + 2];
					U8 in3 = in[t3 + 3];
					r += in0 * fract1;
					g += in1 * fract1;
					b += in2 * fract1;
					a += in3 * fract1;
				}
			}

			r *= norm_factor;
			g *= norm_factor;
			b *= norm_factor;
			a *= norm_factor;  // skip conditional

			S32 t4 = x * out_pixel_step * components;
			out[t4 + 0] = U8(llround(r));
			if (components >= 2)
				out[t4 + 1] = U8(llround(g));
			if (components >= 3)
				out[t4 + 2] = U8(llround(b));
			if( components == 4)
				out[t4 + 3] = U8(llround(a));
		}
	}
}