void bpatch::evalBPatch() {
	double v = 0;
	double w = 0;
	double delta = 0.01;
	double nDelta = 1;
	Vector4 q0;
	Vector4 q1;
	Vector4 q2;
	Vector4 q3;
	Vector4 p0;
	Vector4 p1;
	Vector4 p2;
	Vector4 p3;
	Vector4 tanp;
	Vector4 tanq;
	Matrix4 pm0 = setMatrix(0, 1, 2, 3);
	Matrix4 pm1 = setMatrix(4, 5, 6, 7);
	Matrix4 pm2 = setMatrix(8, 9, 10, 11);
	Matrix4 pm3 = setMatrix(12, 13, 14, 15);
	Matrix4 pm;
	Matrix4 qm;
	for (int i = 0; i < 101; i++) {
		q0 = evalBCurve(pm0, v);
		q1 = evalBCurve(pm1, v);
		q2 = evalBCurve(pm2, v);
		q3 = evalBCurve(pm3, v);
		p0 = evalBCurve(pm0, v+nDelta);
		p1 = evalBCurve(pm1, v+nDelta);
		p2 = evalBCurve(pm2, v+nDelta);
		p3 = evalBCurve(pm3, v+nDelta);
		w = 0;
		for (int j = 0; j < 101; j++) {
			qm = setMatrix(q0, q1, q2, q3);
			pm = setMatrix(p0, p1, p2, p3);
			vertices[i][j] = evalBCurve(qm , w);
			tanp = evalBCurve(qm, w + nDelta);
			//std::cout << w << "AS" << w + nDelta << std::endl;
			//tanp.print("ASD");
			//vertices[i][j].print("HOHO");
			//std::cout << tanp.get(2) << std::endl;
			tanp = tanp - vertices[i][j];
			//tanp.print("RESLTU");
			tanq = evalBCurve(pm, w) - vertices[i][j];
			//tanq.print("AS");
			tanp.normalize();
			tanq.normalize();
			normals[i][j] = tanp.cross(tanp,tanq);
			normals[i][j].setValue(3, 1);
			//normals[i][j].print("AS");
			w = w + delta;
		}
		v = v + delta;
	}
}