void Physics::TestCollision(Circle *a, Circle *b) {
	Vector2D n = (b->GetCentroidPosition() - a->GetCentroidPosition());
	double depth = a->radius + b->radius - n.GetLength();
	if (depth < 0) return;
	n.Normalize();
	constraints.push_back(new Contact(a, b, a->GetCentroidPosition() + n * a->radius, n, depth));
}