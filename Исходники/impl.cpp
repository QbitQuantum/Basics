//we don't have to bother with making sure that gcd(R,M) == 1 since M is odd.
uberzahl modexp_mm(mm_t & mm, uberzahl base, uberzahl exp, uberzahl M){
	if(!mm.initialized){
		mm.R = next_power(M);
		mm.Rbits = mm.R.bitLength();
		mm.Mprime = (mm.R-M.inverse(mm.R));
		uberzahl z("1");
		uberzahl t("2");
		mm.Rsq = modexp(mm.R,t,M);
		//mm.z_init = mm.R % M;
		mm.z_init = montgomery_reduction(mm.Rsq, M, mm.Mprime, mm.Rbits, mm.R);
		mm.initialized = true;
	}

	//convert into Montgomery space
	uberzahl z = mm.z_init;

	//According to Piazza post we don't even need to calculate the residues with mod
	if(base * mm.Rsq < mm.R*M)
		base = montgomery_reduction(base * mm.Rsq, M, mm.Mprime, mm.Rbits, mm.R);
	else
		base = base * mm.R % M;

	mediumType i = exp.bitLength() - 1;

	while(i >= 0) {
		z = montgomery_reduction(z * z, M, mm.Mprime, mm.Rbits, mm.R);
		if(exp.bit(i) == 1){
			z = montgomery_reduction(z * base , M, mm.Mprime, mm.Rbits, mm.R);
		}
		if(i == 0)
			break;
		i -= 1;
	}
	return montgomery_reduction(z, M, mm.Mprime, mm.Rbits, mm.R);
}