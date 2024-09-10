/// <summary>
/// Concatenates a scaling matrix to this matrix.
/// </summary>
/// <param name="scaleX">Factor to scale by in the X direction.</param>
/// <param name="scaleY">Factor to scale by in the Y direction.</param>
/// <param name="scaleZ">Factor to scale by in the Z direction.</param>
void Matrix3D::Scale(double scaleX, double scaleY, double scaleZ)
{
    Matrix3D matrix = Matrix3D::wkMat3Da;
    matrix.SetToScaling(scaleX, scaleY, scaleZ);
    Concatenate(matrix);
}