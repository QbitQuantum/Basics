ArrayXXd CMT::TanhBlobNonlinearity::operator()(const ArrayXXd& inputs) const {
	return tanh(mNonlinearity(inputs));
}