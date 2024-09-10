/*
\brief 判断点a是否在b的上方。
*/
bool IsAbove(const Point2D& a , const Point2D& b, const Vector2D& u)
{
	return u.dot(a-b) > 0;
}