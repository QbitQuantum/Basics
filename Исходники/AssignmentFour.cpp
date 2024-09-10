Vector2f AssignmentFour::FieldValue(Vector2f xi) {
	StaticVector<float, 2U> vec = Field.sample(xi[0], xi[1]);
	Vector2f v = makeVector2f(vec[0], vec[1]);
	if (DirectionFieldOnly) v.normalize();
	return IntegrateBackwards ? -v : v;
}