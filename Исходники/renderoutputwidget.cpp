void QRenderOutputWidget::Orbit(float DownDegrees, float RightDegrees)
{
	Vec3f ReverseLoS = Position - FocalPoint;

	Vec3f right		= ViewUp.Cross(ReverseLoS);
	Vec3f orthogUp	= ReverseLoS.Cross(right);
	Vec3f Up = Vec3f(0.0f, 1.0f, 0.0f);
		
	ReverseLoS.RotateAxis(right, DownDegrees);
	ReverseLoS.RotateAxis(Up, RightDegrees);
	ViewUp.RotateAxis(right, DownDegrees);
	ViewUp.RotateAxis(Up, RightDegrees);

	Position = ReverseLoS + FocalPoint;
}