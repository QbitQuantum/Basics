double VectFuns::angle_between(const Vect2& a, const Vect2& b, const Vect2& c) {
	Vect2 A = b.Sub(a);
	Vect2 B = b.Sub(c);
	return Util::acos_safe(A.dot(B)/(A.norm()*B.norm()));
}