CGnuplot::CGnuplot()
{
	Fp = _popen("pgnuplot", "w");
	if (Fp == NULL) {
		printf("pipe error\n");
	}
}