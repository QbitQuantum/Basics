void OgreNewtonMesh::ApplyTransform (const Vector3& posit, const Vector3& scale, const Quaternion& rotation)
{
	Matrix4 matrix;
	matrix.makeTransform (posit, scale, rotation);
	matrix = matrix.transpose();
	dNewtonMesh::ApplyTransform (&matrix[0][0]);
}