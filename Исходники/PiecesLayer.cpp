void PiecesLayer::calReflectedRay( Vec2 tobeReflectPoint,Vec2 symmetryAxisVertax1,Vec2 symmetryAxisVertax2)
{
	Vec2 vec1 = symmetryAxisVertax1;
	Vec2 vec2 = symmetryAxisVertax2;

	vec1.subtract(vec2);

	float x_1,y_1,x_2,y_2;

	Vec2 normalVec = vec1;
	normalVec.normalize();
	x_1 = m_x - CIRCLE_RADIUS * normalVec.x;
	y_1 = m_y - CIRCLE_RADIUS * normalVec.y;
	x_2 = m_x;
	y_2 = m_y;

	//drawNode->drawSegment(Vec2(m_x, m_y), Vec2(x_1, y_1), 3.0f, Color4F(1, 1, 1, 1));
	float x_0 = tobeReflectPoint.x;
	float y_0 = tobeReflectPoint.y;

	float A_ = y_2 - y_1;
	float B_ = x_1 - x_2;
	float C_ = x_2 * y_1 - x_1 * y_2;
	float k_ = -2 * (A_ * x_0 + B_ * y_0 + C_) / (A_ * A_ + B_ * B_);

	if (x_2 - x_1 != 0 && y_2 - y_1 != 0) {
		mReflectX = x_0 + k_ * A_;
		mReflectY = y_0 + k_ * B_;
	}
}