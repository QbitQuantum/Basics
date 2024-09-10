// operand /
Fraction3 operator/(const Fraction3 &a, const Fraction3 &b) {
	Fraction3 aF = a; Fraction3 bF = b;
	aF.div(bF);
	return aF;
}