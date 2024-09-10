void spIkConstraint_apply2 (spBone* parent, spBone* child, float targetX, float targetY, int bendDir, float alpha) {
	float px = parent->x, py = parent->y, psx = parent->scaleX, psy = parent->scaleY;
	float cx = child->x, cy, csx = child->scaleX, cwx, cwy;
	int o1, o2, s2, u;
	spBone* pp = parent->parent;
	float tx, ty, dx, dy, l1, l2, a1, a2, r;
	float id, x, y;
	if (alpha == 0) {
		spBone_updateWorldTransform(child);
		return;
	}
	if (psx < 0) {
		psx = -psx;
		o1 = 180;
		s2 = -1;
	} else {
		o1 = 0;
		s2 = 1;
	}
	if (psy < 0) {
		psy = -psy;
		s2 = -s2;
	}
	if (csx < 0) {
		csx = -csx;
		o2 = 180;
	} else
		o2 = 0;
	r = psx - psy;
	u = (r < 0 ? -r : r) <= 0.0001f;
	if (!u) {
		cy = 0;
		cwx = parent->a * cx + parent->worldX;
		cwy = parent->c * cx + parent->worldY;
	} else {
		cy = child->y;
		cwx = parent->a * cx + parent->b * cy + parent->worldX;
		cwy = parent->c * cx + parent->d * cy + parent->worldY;
	}
	id = 1 / (pp->a * pp->d - pp->b * pp->c);
	x = targetX - pp->worldX;
	y = targetY - pp->worldY;
	tx = (x * pp->d - y * pp->b) * id - px;
	ty = (y * pp->a - x * pp->c) * id - py;
	x = cwx - pp->worldX;
	y = cwy - pp->worldY;
	dx = (x * pp->d - y * pp->b) * id - px;
	dy = (y * pp->a - x * pp->c) * id - py;
	l1 = SQRT(dx * dx + dy * dy);
	l2 = child->data->length * csx;
	if (u) {
		float cosine, a, b;
		l2 *= psx;
		cosine = (tx * tx + ty * ty - l1 * l1 - l2 * l2) / (2 * l1 * l2);
		if (cosine < -1) cosine = -1;
		else if (cosine > 1) cosine = 1;
		a2 = ACOS(cosine) * bendDir;
		a = l1 + l2 * cosine;
		b = l2 * SIN(a2);
		a1 = ATAN2(ty * a - tx * b, tx * a + ty * b);
	} else {
		float a = psx * l2, b = psy * l2;
		float aa = a * a, bb = b * b, ll = l1 * l1, dd = tx * tx + ty * ty, ta = ATAN2(ty, tx);
		float c0 = bb * ll + aa * dd - aa * bb, c1 = -2 * bb * l1, c2 = bb - aa;
		float d = c1 * c1 - 4 * c2 * c0;
		float minAngle = 0, minDist = FLT_MAX, minX = 0, minY = 0;
		float maxAngle = 0, maxDist = 0, maxX = 0, maxY = 0;
		float x = l1 + a, dist = x * x, angle, y;
		if (d >= 0) {
			float q = SQRT(d), r0, r1;
			if (c1 < 0) q = -q;
			q = -(c1 + q) / 2;
			r0 = q / c2; r1 = c0 / q;
			r = ABS(r0) < ABS(r1) ? r0 : r1;
			if (r * r <= dd) {
				y = SQRT(dd - r * r) * bendDir;
				a1 = ta - ATAN2(y, r);
				a2 = ATAN2(y / psy, (r - l1) / psx);
				goto outer;
			}
		}
		if (dist > maxDist) {
			maxAngle = 0;
			maxDist = dist;
			maxX = x;
		}
		x = l1 - a;
		dist = x * x;
		if (dist < minDist) {
			minAngle = PI;
			minDist = dist;
			minX = x;
		}
		angle = ACOS(-a * l1 / (aa - bb));
		x = a * COS(angle) + l1;
		y = b * SIN(angle);
		dist = x * x + y * y;
		if (dist < minDist) {
			minAngle = angle;
			minDist = dist;
			minX = x;
			minY = y;
		}
		if (dist > maxDist) {
			maxAngle = angle;
			maxDist = dist;
			maxX = x;
			maxY = y;
		}
		if (dd <= (minDist + maxDist) / 2) {
			a1 = ta - ATAN2(minY * bendDir, minX);
			a2 = minAngle * bendDir;
		} else {
			a1 = ta - ATAN2(maxY * bendDir, maxX);
			a2 = maxAngle * bendDir;
		}
	}
	outer: {
		float os = ATAN2(cy, cx) * s2;
		a1 = (a1 - os) * RAD_DEG + o1 - parent->rotation;
		if (a1 > 180) a1 -= 360;
		else if (a1 < -180) a1 += 360;
		spBone_updateWorldTransformWith(parent, px, py, parent->rotation + a1 * alpha, parent->scaleX, parent->scaleY, 0, 0);
		a2 = ((a2 + os) * RAD_DEG - child->shearX) * s2 + o2 - child->rotation;
		if (a2 > 180) a2 -= 360;
		else if (a2 < -180) a2 += 360;
		spBone_updateWorldTransformWith(child, cx, cy, child->rotation + a2 * alpha, child->scaleX, child->scaleY, child->shearX, child->shearY);
	}
}