void FieldController::GetProjection(const RectangleF* pRect, const Vector2F& dir, Vector2F& min, Vector2F& max)
{
	Vector2F	projectionAxis(-dir.Y(), dir.X());
	float		sqrlen = projectionAxis.X() * projectionAxis.X() + projectionAxis.Y() * projectionAxis.Y();


	// projection rectangle points to projAxis
	float dp = pRect->GetTopLeft().X() * projectionAxis.X() + pRect->GetTopLeft().Y() * projectionAxis.Y();
	float tempValue = dp / sqrlen;

	min.X() = tempValue * projectionAxis.X();
	min.Y() = tempValue * projectionAxis.Y();

	dp = pRect->GetBottomRight().X() * projectionAxis.X() + pRect->GetBottomRight().Y() * projectionAxis.Y();
	tempValue = dp / sqrlen;

	max.X() = tempValue * projectionAxis.X();
	max.Y() = tempValue * projectionAxis.Y();

}