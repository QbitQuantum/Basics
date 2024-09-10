	// Two boundary points known
	Circle *makeCircleTwoPoints(vector<Point> &points, int fromIdx, int toIdx, Point p, Point q) {
		Circle *temp = makeDiameter(p, q);
		bool ContainsAll=1;
		for(int i = fromIdx; i < toIdx; ++i) if(!temp->contains(points[i])){
            ContainsAll = 0;
            break;
		}
		if (ContainsAll) return temp;

		Circle *left = NULL;
		Circle *right = NULL;
		for (int i = fromIdx; i < toIdx; ++i) {
            Point r = points[i];
			Point pq = q.subtract(p);
			double cross = pq.cross(r.subtract(p));
			Circle *c = makeCircumcircle(p, q, r);
			if (c == NULL)
				continue;
			else if (cross > 0 && (left == NULL || pq.cross(c->c.subtract(p)) > pq.cross(left->c.subtract(p))))
				left = c;
			else if (cross < 0 && (right == NULL || pq.cross(c->c.subtract(p)) < pq.cross(right->c.subtract(p))))
				right = c;
		}
		return right == NULL || (left != NULL && left->r) <= right->r ? left : right;
	}