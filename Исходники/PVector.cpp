void PVector::normalize() {
	float m = mag();
	if (m != 0) {
		div(m);
	}
}