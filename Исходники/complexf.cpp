F32    ComplexfAbs    (const Complexf&   inComplex) {
	F32 z;
	z = (inComplex.real * inComplex.real) + (inComplex.img * inComplex.img);
	return Sqrtf(z);
}