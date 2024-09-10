Transform<Scalar,3>::Transform(const Transform<Scalar, 3> &trans)
{
	this->translation_ = trans.translation();
	this->rotation_ = trans.rotation();
	this->scale_ = trans.scale();
}