	inline bool Check(Int64 n) {
		if (n == 1) return false;
		if (n == 2) return true;
		for (int i = 0; i < 4; i++) {
			int a = fim[i];
			Int64 d = n - 1;
			while (!(d&1)) d >>= 1;
			Int64 t = Pow(a, d, n);
			while (d != n - 1 && t != 1 && t != n - 1) {
				d <<= 1;
				t = Mult(t, t, n);
			}
			if (t != n - 1 && ((d & 1) != 1)) return false;
		}
		return true;
	}