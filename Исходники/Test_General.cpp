void randomizePlaintext(Plaintext &ptxt, unsigned deg, unsigned p) {
	ZZ_pX poly;
	poly.rep.SetLength(deg);
	for(unsigned i = 0; i < deg; i++) {
		poly.rep[i] = RandomBnd(p);
	}

	poly.normalize();
	ptxt.Init(poly);
}