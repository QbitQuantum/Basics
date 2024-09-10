void MlRachis::moveForward(const Matrix33F & space, float distance, Vector3F & dst)
{
	Vector3F wv = space.transform(Vector3F::ZAxis);
	wv.normalize();
	dst += wv * distance;
}