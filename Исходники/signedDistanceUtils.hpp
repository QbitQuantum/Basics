Vector2d signed_distance_2d::closestPointOnLineSegment(Vector2d point, Vector2d p1, Vector2d p2) {

	// We are working with line representation L = {u*z + d | z is a real number, u is normalized}
	// u and d are in R^2 (2D vectors)

	// Get Unit vector in direction of edge
	Vector2d u = p1 - p2;
	if ((u.cwiseAbs()).sum() != 0) {
		u.normalize(); // Assuming u has nonzero length
	} else {
		u << 0, 0;
	}
	Vector2d d = p1; // d can be any point on the line. p1 or p2 will do

	double t = (point - d).dot(u);

	// Find if point is on line segment or if it needs to be projected to an end of segment
	// Do this in projected 1D space. Find t for both p1 and p2, and compare to t from the point.
	double p1t = (p1 - d).dot(u);
	double p2t = (p2 - d).dot(u);
	if (t <= min(p1t, p2t)) {
		t = min(p1t, p2t);
	} else if (t >= max(p1t, p2t)) {
		t = max(p1t, p2t);
	}
	Vector2d proj = u.array() * t;
	proj += d;

	// Sanity check
	Vector2d a = perpendicularAxis(u);
	double c = a.dot(p1); // Constant, a'*x + d = 0
	double eps = 1e-5;
	if (abs(a.dot(proj) - c) > eps) {
		std::cout << "Warning: Projection on line is not on line with tolerance " << eps << std::endl;
	}

	return proj;

}