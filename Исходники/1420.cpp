	inline VII BabyStep(int a, int b, int c) {
		VII ret;
		int m = (int)sqrt(c) + 1, tmp = 1; a %= c; if (a == 0) return ret;
		insert(1, 0);
		for (int i = 1; i <= m; i++)
			tmp = (Int65) tmp * a % c, insert(tmp, i);
		int gss = b, opp = Pow(tmp, c - 2, c);
		for (int i = 0, d; i <= m; i++) {
			int index = gss % MOD;
			for (Edge *p = e[index]; p; p = p->next) if (p->index == gss)
				ret.push_back(i * m + p->value);
			gss = (Int65) gss * opp % c;
		}
		return ret;
	}