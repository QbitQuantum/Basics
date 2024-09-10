void Tessellation::addQuadradratic(const Vector& B, const Vector& C, float pointsPerUnitLength) {
	Vector U, V, A = positions.back().toVec();

	//TODO actually add points evaluating the "curvyness" of the path
	float length = A.distance(B) + B.distance(C); //compute a rough length of this arc
	int subdivs = (int)(length * pointsPerUnitLength + 1);

	for (int i = 1; i <= subdivs; i++)
	{
		float t = (float)i / subdivs;

		U = A.lerpTo(t, B);
		V = B.lerpTo(t, C);

		addSegment(U.lerpTo(t, V));
	}
}