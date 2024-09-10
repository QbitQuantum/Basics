	void Work(void) {
		int64 P[5] = {1, 2};
		while (!Zero(a) && !Zero(b)) {
			bool Odda = a[1] & 1, Oddb = b[1] & 1;
			if (Odda && Oddb) {
				Decreas(a, b);
			}else
			if (!Odda && !Oddb) {
				Div(a);
				Div(b);
				Mult(delta, P);
			}else
			if (Odda && !Oddb) {
				Div(b);
			}else
			if (!Odda && Oddb) {
				Div(a);
			}
		}
		if (Zero(a)) {
			Mult(b, delta);
			Print(b);
		}
		else {
			Mult(a, delta);
			Print(a);
		}
	}