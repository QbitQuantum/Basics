void LFrustum::CalcFrustumInBasis( const LVector3& Pos, const LVector3& To, const LVector3& Up, float fw, float fh, float nw, float nh )
{
	LVector3 Z = Pos - To;
	Z.Normalize();

	LVector3 X = Up.Cross( Z );
	X.Normalize();

	LVector3 Y = Z.Cross( X );

	LVector3 nc = Pos - Z * FNearClipPlane;
	LVector3 fc = Pos - Z * FFarClipPlane;

	FCornerPoints[FRUSTUM_ntl] = nc + Y * nh - X * nw;
	FCornerPoints[FRUSTUM_ntr] = nc + Y * nh + X * nw;
	FCornerPoints[FRUSTUM_nbl] = nc - Y * nh - X * nw;
	FCornerPoints[FRUSTUM_nbr] = nc - Y * nh + X * nw;

	FCornerPoints[FRUSTUM_ftl] = fc + Y * fh - X * fw;
	FCornerPoints[FRUSTUM_ftr] = fc + Y * fh + X * fw;
	FCornerPoints[FRUSTUM_fbl] = fc - Y * fh - X * fw;
	FCornerPoints[FRUSTUM_fbr] = fc - Y * fh + X * fw;

	for ( int i = PLANE_LEFT ; i < PLANE_FAR + 1 ; i++ )
	{
		LVector3 P1 = FCornerPoints[ static_cast<int>( FrustumPlanePoints[i].X ) ];
		LVector3 P2 = FCornerPoints[ static_cast<int>( FrustumPlanePoints[i].Y ) ];
		LVector3 P3 = FCornerPoints[ static_cast<int>( FrustumPlanePoints[i].Z ) ];

		TODO( "store planes as LPlane, not as Vector4 !" )

//    FPlanes[i].From3Points(P1, P2, P3);
	}
}