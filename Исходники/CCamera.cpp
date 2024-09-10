void CCamera::RebuildMatrices() {
	if(!needsRebuild) {
		return;
	}

	needsRebuild = false;
	CVector forward = CVector::Subtract(lookat,pos);
	CVector up = CVector(0,1,0);
	CVector right = CVector::GetNormal(up,forward);

	forward.Normalize();
	up.Normalize();
	right.Normalize();

	normalmatrix = CMatrix(right,up,forward);
	normalmatrix.Rotate(0,0,roll);
	normalmatrix.Clone(matrix);
	matrix.Shift(pos._x,pos._y,pos._z);
	
	normalmatrix = normalmatrix.Inverse();
	matrix = matrix.Inverse();
}