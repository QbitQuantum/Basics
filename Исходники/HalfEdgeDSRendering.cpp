void renderHEActive(const HalfEdge* he)
{
	if (!he || !he->startV || !he->nextHE || !he->nextHE->startV) return;
	Vec3f& p1 = he->startV->coordinates;
	Vec3f& p2 = he->nextHE->startV->coordinates;
	Vec3f dir = p2 - p1;
	float diameter = dir.length() / 40.0f;
	glColor3f(1.0f, 0.0f, 0.0f);
	renderArrow(p1 + 0.15f * dir, p2 - 0.15f * dir, diameter);
}