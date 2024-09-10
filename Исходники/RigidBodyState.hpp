	operator Eigen::Transform<double, 3, Eigen::Affine, _Options>() const
	{
	    Eigen::Transform<double, 3, Eigen::Affine, _Options> ret;
	    ret.setIdentity();
	    ret.rotate(this->orientation);
	    ret.translation() = this->position;
	    return ret;
	}