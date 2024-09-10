static void
s1 (
	KTYPE	a1,
	KTYPE	a2,
	KTYPE	a3,
	KTYPE	a4,
	KTYPE	a5,
	KTYPE	a6,
	KTYPE	*out1,
	KTYPE	*out2,
	KTYPE	*out3,
	KTYPE	*out4
) {
	aligned register KTYPE	x1, x2, x3, x4, x5, x6, x7, x8;
	aligned register KTYPE	x9, x10, x11, x12, x13, x14, x15, x16;
	aligned register KTYPE	x17, x18, x19, x20, x21, x22, x23, x24;
	aligned register KTYPE	x25, x26, x27, x28, x29, x30, x31, x32;
	aligned register KTYPE	x33, x34, x35, x36, x37, x38, x39, x40;
	aligned register KTYPE	x41, x42, x43, x44, x45, x46, x47, x48;
	aligned register KTYPE	x49, x50, x51, x52, x53, x54, x55, x56;
	aligned register KTYPE	x57, x58, x59, x60, x61, x62, x63;

	x1 = _mm_andnot_si128(a4, KCONST_1);
	x2 = _mm_andnot_si128(a1, KCONST_1);
	x3 = a4 ^ a3;
	x4 = x3 ^ x2;
	x5 = a3 | x2;
	x6 = x5 & x1;
	x7 = a6 | x6;
	x8 = x4 ^ x7;
	x9 = x1 | x2;
	x10 = a6 & x9;
	x11 = x7 ^ x10;
	x12 = a2 | x11;
	x13 = x8 ^ x12;
	x14 = x9 ^ x13;
	x15 = a6 | x14;
	x16 = x1 ^ x15;
	x17 = _mm_andnot_si128(x14, KCONST_1);
	x18 = x17 & x3;
	x19 = a2 | x18;
	x20 = x16 ^ x19;
	x21 = a5 | x20;
	x22 = x13 ^ x21;
	*out4 ^= x22;
	x23 = a3 | x4;
	x24 = _mm_andnot_si128(x23, KCONST_1);
	x25 = a6 | x24;
	x26 = x6 ^ x25;
	x27 = x1 & x8;
	x28 = a2 | x27;
	x29 = x26 ^ x28;
	x30 = x1 | x8;
	x31 = x30 ^ x6;
	x32 = x5 & x14;
	x33 = x32 ^ x8;
	x34 = a2 & x33;
	x35 = x31 ^ x34;
	x36 = a5 | x35;
	x37 = x29 ^ x36;
	*out1 ^= x37;
	x38 = a3 & x10;
	x39 = x38 | x4;
	x40 = a3 & x33;
	x41 = x40 ^ x25;
	x42 = a2 | x41;
	x43 = x39 ^ x42;
	x44 = a3 | x26;
	x45 = x44 ^ x14;
	x46 = a1 | x8;
	x47 = x46 ^ x20;
	x48 = a2 | x47;
	x49 = x45 ^ x48;
	x50 = a5 & x49;
	x51 = x43 ^ x50;
	*out2 ^= x51;
	x52 = x8 ^ x40;
	x53 = a3 ^ x11;
	x54 = x53 & x5;
	x55 = a2 | x54;
	x56 = x52 ^ x55;
	x57 = a6 | x4;
	x58 = x57 ^ x38;
	x59 = x13 & x56;
	x60 = a2 & x59;
	x61 = x58 ^ x60;
	x62 = a5 & x61;
	x63 = x56 ^ x62;
	*out3 ^= x63;
}