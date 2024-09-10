	Common::Plane Transform_Plane_By_Mat44(const Plane& plane, const Matrix44& mat)
	{
		Vector4 v(plane.n, plane.d);

		// To transform normal, we can not use the matrix directly
		// See: http://www.songho.ca/opengl/gl_normaltransform.html
		Matrix44 matInvTranspose = mat.Inverse();
		matInvTranspose.Transpose();

		v = Common::Transform_Vec4_By_Mat44(v, matInvTranspose);

		Plane ret;
		ret.n = v.GetVec3();
		ret.d = v.w / ret.n.Normalize();

		return ret;
	}