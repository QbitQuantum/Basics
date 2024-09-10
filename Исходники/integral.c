int main() {
//	nemu_assert(int2F(1) + F_mul_int(F_mul_F(f2F(-0.8),f2F(-0.8)),25) > int2F(16.9));
//	nemu_assert(int2F(1) + F_mul_int(F_mul_F(f2F(-0.8),f2F(-0.8)),25) < int2F(17));
//	nemu_assert();
//	nemu_assert(F_div_F(int2F(1) , int2F(1) + F_mul_int(F_mul_F(f2F(-0.8),f2F(-0.8)),25)) > f2F(0));
//	nemu_assert(F_div_F(int2F(1) , f2F(17)) > f2F(0.05));
/*	nemu_assert(F_div_int(int2F(2),10) <= f2F(0.2));
	nemu_assert(F_div_int(int2F(2),10) > f2F(0.1999));
	nemu_assert(F_mul_F(f2F(1.0),int2F(25)) == f2F(25));
	nemu_assert(f(int2F(1)) < f2F(0.039));
	nemu_assert(F_mul_int(f2F(0.2),9 ) > f2F(1.7));*/
//	nemu_assert(F_mul_F(f2F(-0.8),f2F(-0.8)) == f2F(0.64));
 // nemu_assert(F_div_F(0x10000,0x10ffcd) == int2F(0));
//	nemu_assert(f(-0.8) > f2F(0.05));
//	nemu_assert(F_mul_F(f2F(0.8),f2F(0.8)) < f2F(0.64));
//	nemu_assert(f(f2F(0.8)) > f2F(0.05));
//	nemu_assert(f(f2F(0.8)) < f2F(0.06));
//	nemu_assert(F_mul_F(f2F(-0.2),f2F(-0.2)) == f2F(0.04));
//	nemu_assert(f(f2F(-0.2)) == int2F(0));
//	nemu_assert(f2F(-1.0) + F_mul_int(f2F(0.2),9) < f2F(0.9));
//	nemu_assert(f(f2F(-1.0) + F_mul_int(f2F(0.2), 9)) > f2F(0.03));
//	nemu_assert(f2F(0.2) == 0x3333);
//	nemu_assert(F_mul_F(f2F(2.756),f2F(0.2)) > f2F(0.55));
//	nemu_assert(F_mul_F(f2F(2.756),f2F(0.2)) < f2F(0.5515));
//	nemu_assert( < f2F(0.05));
//	nemu_assert(f(1.8)<f2F(0.040));
	FLOAT a = computeT(10, f2F(-1.0), f2F(1.0), f);
//	nemu_assert(a > int2F(1));
	FLOAT ans = f2F(0.551222);
	nemu_assert(Fabs(a - ans) < f2F(1e-4));
//	nemu_assert(a < f2F(0.019));
//	FLOAT ans = f2F(2.756);
	//nemu_assert(a <= ans);
//	nemu_assert(a > f2F(0.1));
//	nemu_assert(Fabs(a - ans) < f2F(1e-4));
	HIT_GOOD_TRAP;
	return 0;
}