void DCT::calcDCTIII(float *data) {
	int n = 1 << _bits;

	float next  = data[n - 1];
	float inv_n = 1.0 / n;

	for (int i = n - 2; i >= 2; i -= 2) {
		float val1 = data[i    ];
		float val2 = data[i - 1] - data[i + 1];

		float c = COS(n, i);
		float s = SIN(n, i);

		data[i    ] = c * val1 + s * val2;
		data[i + 1] = s * val1 - c * val2;
	}

	data[1] = 2 * next;

	_rdft->calc(data);

	for (int i = 0; i < (n / 2); i++) {
		float tmp1 = data[i        ] * inv_n;
		float tmp2 = data[n - i - 1] * inv_n;

		float csc = _csc2[i] * (tmp1 - tmp2);

		tmp1 += tmp2;

		data[i        ] = tmp1 + csc;
		data[n - i - 1] = tmp1 - csc;
	}
}