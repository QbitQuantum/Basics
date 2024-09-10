Complex Complex::operator/(const Complex& other){
	Complex temp = other.conjugate();
	double mag = other.modulus();
	Complex t1 = *this * temp;
	return Complex((t1.real/(mag*mag)), (t1.imag/(mag*mag)));
}