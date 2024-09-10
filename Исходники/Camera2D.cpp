const CU::Matrix33<float> Camera2D::GetInverse() const
{
	CU::Vector3<float> translation(-myOrientation.myMatrix[6], -myOrientation.myMatrix[7], 1);
	CU::Matrix33<float> inverse(myOrientation);
	inverse.myMatrix[6] = 0;
	inverse.myMatrix[7] = 0;
	inverse = CU::Transpose(inverse);
	translation *= inverse;
	inverse.myMatrix[6] = translation.x;
	inverse.myMatrix[7] = translation.y;
	return inverse;
}