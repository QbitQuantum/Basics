void set_view_matrix(const Matrix4x4 &mat)
{
	static int sidx = -1, sidx_transp, sidx_mat3, sidx_inv;

	if(sidx == -1) {
		sidx = add_unistate("st_view_matrix", ST_MATRIX4);
		sidx_mat3 = add_unistate("st_view_matrix3", ST_MATRIX3);
		sidx_transp = add_unistate("st_view_matrix_transpose", ST_MATRIX4);
		sidx_inv = add_unistate("st_view_matrix_inverse", ST_MATRIX4);
	}

	set_unistate(sidx, mat);
	set_unistate(sidx_mat3, Matrix3x3(mat));
	set_unistate(sidx_transp, mat[0]);	// by using the float* variant, we unset the transpose flag
	set_unistate(sidx_inv, mat.inverse());
}