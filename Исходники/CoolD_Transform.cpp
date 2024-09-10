	//world -> perspective
	Matrix44 TransformHelper::CreatePerspective(Dfloat fov, Dfloat aspect, Dfloat nearZ, Dfloat farZ)
	{
		Dfloat d = 1.0f / Tan(fov * 0.5f);
		Dfloat recip = 1.0f / (nearZ - farZ);
		Matrix44 matPerspective;

		matPerspective(0, 0) = d / aspect;
		matPerspective(1, 1) = d;
		matPerspective(2, 2) = (nearZ + farZ)*recip;
		matPerspective(2, 3) = 2 * nearZ*farZ*recip;
		matPerspective(3, 2) = -1.0f;
		matPerspective(3, 3) = 0.0f;

		return matPerspective;
	}