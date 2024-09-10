CollisionData iTest(const AABB & rect, const Circle & circle)
{
	CollisionData cd = { false, 0, 0, 0 };
	cd.pointOfContact = { clamp(circle.pos.x, rect.min().x, rect.max().x), clamp(circle.pos.y, rect.min().y, rect.max().y) };

	if (cd.pointOfContact == circle.pos) {
		float dX = (cd.pointOfContact.x - rect.min().x < rect.max().x - cd.pointOfContact.x) ? rect.min().x : rect.max().x;
		float dY = (cd.pointOfContact.y - rect.min().y < rect.max().y - cd.pointOfContact.y) ? rect.min().y : rect.max().y;

		if (abs(dX - cd.pointOfContact.x) < abs(dY - cd.pointOfContact.y)) cd.pointOfContact.x = dX;
		else															   cd.pointOfContact.y = dY;
	}

	float dist =	pow(circle.pos.x - cd.pointOfContact.x, 2) + pow(circle.pos.y - cd.pointOfContact.y, 2);
	float radius =	pow(circle.radius, 2);

	cd.penetrationDepth = radius - dist;
	if (dist < radius) cd.inOverlap = true;
	cd.collisionNormal = (circle.pos - cd.pointOfContact).normal();

	return cd;
}