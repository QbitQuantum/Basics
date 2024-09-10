Vector3 Basis::get_scale_local() const {
	real_t det_sign = SGN(determinant());
	return det_sign * Vector3(elements[0].length(), elements[1].length(), elements[2].length());
}