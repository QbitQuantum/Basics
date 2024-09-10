void __CLRCALL_PURE_OR_CDECL _MP_Rem(_MP_arr u, _Max_type v0)
	{	// divide multi-word value by value, leaving remainder in u
	_Max_type v[2];
	v[0] = v0 & mask;
	v[1] = v0 >> shift;
	const int n = limit(v, 2);
	const int m = limit(u, _MP_len) - n;

	// Knuth, vol. 2, p. 272, Algorithm D
	// D1: [Normalize.]
	_Max_type d = max / (v[n - 1] + 1);
	if (d != 1)
		{	// scale numerator and divisor
		mul(u, _MP_len, d);
		mul(v, n, d);
		}
	// D2: [Initialize j.]
	for (int j = m; 0 <= j; --j)
		{	// D3: [Calculate qh.]
		_Max_type qh = ((u[j + n] << shift) + u[j + n - 1]) / v[n - 1];
		if (qh == 0)
			continue;
		_Max_type rh = ((u[j + n] << shift) + u[j + n - 1]) % v[n - 1];
		for (;;)
			if (qh < max && qh * v[n - 2] <= (rh << shift) + u[j + n - 2])
				break;
			else
				{	// reduce tentative value and retry
				--qh;
				rh += v[n - 1];
				if (max <= rh)
					break;
				}
		// D4: [Multiply and subtract.]
		_Max_type k = 0;
		int i;
		for (i = 0; i < n; ++i)
			{	// multiply and subtract
			u[j + i] -= qh * v[i] + k;
			k = u[j + i] >> shift;
			if (k)
				k = max - k;
			u[j + i] &= mask;
			}
		for (; k != 0 && j + i < _MP_len; ++i)
			{	// propagate borrow
			u[j + i] -= k;
			k = u[j + i] >> shift;
			if (k)
				k = max - k;
			u[j + i] &= mask;
			}
		// D5: [Test remainder.]
		if (k != 0)
			{	// D6: [Add back.]
			--qh;
			add(u + j, n + 1, v, n);
			}
		// D7: [Loop on j.]
		}
	// D8: [Unnormalize.]
	if (d != 1)
		div(u, d);
	}