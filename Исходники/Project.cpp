bool UnProject(const Vector3& winPos, const Matrix4& modelMatrix, const Matrix4& projMatrix,
		int viewX, int viewY, int viewW, int viewH, Vector3& objPos)
{
	// Calculate the inverse matrix
	Matrix4 invPM = projMatrix * modelMatrix;
	invPM.invert();

	/*const float* ma = invPM.toArray();
	printf("invPM (\n");
	printf("    %.3f   %.3f   %.3f   %.3f\n", ma[0], ma[1], ma[2], ma[3]);
	printf("    %.3f   %.3f   %.3f   %.3f\n", ma[4], ma[5], ma[6], ma[7]);
	printf("    %.3f   %.3f   %.3f   %.3f\n", ma[8], ma[9], ma[10], ma[11]);
	printf("    %.3f   %.3f   %.3f   %.3f\n", ma[12], ma[13], ma[14], ma[15]);
	printf(")\n");*/

	Vector3 normDevPos (
			((winPos.getX() - viewX) / viewW) * 2.0f - 1.0f,
			((winPos.getY() - viewY) / viewH) * 2.0f - 1.0f,
			2.0f * winPos.getZ() - 1.0f
	);

	Vector4 tmpObjPos(invPM * Vector4(normDevPos.getX(), normDevPos.getY(), normDevPos.getZ(), 1.0f));
	float ow = tmpObjPos.getW();

	if (ow == 0.0f)
		return false;

	objPos = Vector3(tmpObjPos.getX() / ow, tmpObjPos.getY() / ow, tmpObjPos.getZ() / ow);
	return true;
}