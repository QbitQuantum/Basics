void Tet_mesh3_mes_neg (Mesh3 &Th3) {
	int iv[4];

	for (int ii = 0; ii < Th3.nt; ii++) {
		int lab;

		const Tet &K(Th3.t(ii));
		lab = K.lab;

		iv[0] = Th3.operator () (K[0]);
		iv[2] = Th3.operator () (K[1]);
		iv[1] = Th3.operator () (K[2]);
		iv[3] = Th3.operator () (K[3]);
		R3 A(Th3.vertices[iv[0]]);
		R3 B(Th3.vertices[iv[1]]);
		R3 C(Th3.vertices[iv[2]]);
		R3 D(Th3.vertices[iv[3]]);
		double mes = det(A, B, C, D) / 6.;
		Th3.t(ii).set(Th3.vertices, iv, lab, mes);
	}
}