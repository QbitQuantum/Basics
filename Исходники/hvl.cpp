inline double HVL_da2_internal(const HVL_Context *ctx,
			       const hvl_float &a0, const hvl_float &a2, const hvl_float &a3,
			       const hvl_float &gauss_base, const hvl_float &b1pb2, const hvl_float &reca3, const hvl_float &nmr, const hvl_float &xmu)
{
	const hvl_float gauss_der = a0 * (xmu * xmu * gauss_base / Pow(a2, 3) - gauss_base / a2);

	if (a3 == ctx->HVL_ZERO)
		return ToDouble(gauss_der);

	const hvl_float rnmr = nmr * xmu / a2;
	const hvl_float result = reca3 * ((gauss_der / b1pb2) + rnmr / (b1pb2 * b1pb2));

	return ToDouble(result);
}