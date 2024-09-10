wxSVGMatrix wxSVGMatrix::Multiply(const wxSVGMatrix& secondMatrix) const {
	wxSVGMatrix res;
	res.SetA(GetA() * secondMatrix.GetA() + GetC() * secondMatrix.GetB());
	res.SetB(GetB() * secondMatrix.GetA() + GetD() * secondMatrix.GetB());
	res.SetC(GetA() * secondMatrix.GetC() + GetC() * secondMatrix.GetD());
	res.SetD(GetB() * secondMatrix.GetC() + GetD() * secondMatrix.GetD());
	res.SetE(GetA() * secondMatrix.GetE() + GetC() * secondMatrix.GetF() + GetE());
	res.SetF(GetB() * secondMatrix.GetE() + GetD() * secondMatrix.GetF() + GetF());
	return res;
}