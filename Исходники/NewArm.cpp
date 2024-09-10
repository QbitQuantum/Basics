// Returns coordinates of point a fraction between p1 and p2
// 0 <= fraction <= 1
vec2 NewArm::interpolate(Point p1, Point p2, float fraction) {
	if (fraction < 0)
		fraction = 0;
	else if (fraction > 1) 
		fraction = 1;

	float bearing = p1.angle(p2);
	float dist = p1.distance(p2);
	float dx = dist * fraction * cos(bearing);
	float dy = dist * fraction * sin(bearing);
	return vec2(p1.x + dx, p1.y + dy);
}