void IkConstraint::apply(Bone &parent, Bone &child, float targetX, float targetY, int bendDir, bool stretch, float alpha) {
	float px, py, psx, sx, psy;
	float cx, cy, csx, cwx, cwy;
	int o1, o2, s2, u;
	Bone *pp = parent.getParent();
	float tx, ty, dx, dy, dd, l1, l2, a1, a2, r;
	float id, x, y;
	if (alpha == 0) {
		child.updateWorldTransform();
		return;
	}
	if (!parent._appliedValid) parent.updateAppliedTransform();
	if (!child._appliedValid) child.updateAppliedTransform();
	px = parent._ax;
	py = parent._ay;
	psx = parent._ascaleX;
	sx = psx;
	psy = parent._ascaleY;
	csx = child._ascaleX;
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
	cx = child._ax;
	u = (r < 0 ? -r : r) <= 0.0001f;
	if (!u) {
		cy = 0;
		cwx = parent._a * cx + parent._worldX;
		cwy = parent._c * cx + parent._worldY;
	} else {
		cy = child._ay;
		cwx = parent._a * cx + parent._b * cy + parent._worldX;
		cwy = parent._c * cx + parent._d * cy + parent._worldY;
	}
	id = 1 / (pp->_a * pp->_d - pp->_b * pp->_c);
	x = targetX - pp->_worldX;
	y = targetY - pp->_worldY;
	tx = (x * pp->_d - y * pp->_b) * id - px;
	ty = (y * pp->_a - x * pp->_c) * id - py;
	dd = tx * tx + ty * ty;
	x = cwx - pp->_worldX;
	y = cwy - pp->_worldY;
	dx = (x * pp->_d - y * pp->_b) * id - px;
	dy = (y * pp->_a - x * pp->_c) * id - py;
	l1 = MathUtil::sqrt(dx * dx + dy * dy);
	l2 = child.getData().getLength() * csx;
	if (u) {
		float cosine, a, b;
		l2 *= psx;
		cosine = (dd - l1 * l1 - l2 * l2) / (2 * l1 * l2);
		if (cosine < -1) cosine = -1;
		else if (cosine > 1) {
			cosine = 1;
			if (stretch && l1 + l2 > 0.0001f) sx *= (MathUtil::sqrt(dd) / (l1 + l2) - 1) * alpha + 1;
		}
		a2 = MathUtil::acos(cosine) * bendDir;
		a = l1 + l2 * cosine;
		b = l2 * MathUtil::sin(a2);
		a1 = MathUtil::atan2(ty * a - tx * b, tx * a + ty * b);
	} else {
		float a = psx * l2, b = psy * l2;
		float aa = a * a, bb = b * b, ll = l1 * l1, ta = MathUtil::atan2(ty, tx);
		float c0 = bb * ll + aa * dd - aa * bb, c1 = -2 * bb * l1, c2 = bb - aa;
		float d = c1 * c1 - 4 * c2 * c0;
		if (d >= 0) {
			float q = MathUtil::sqrt(d), r0, r1;
			if (c1 < 0) q = -q;
			q = -(c1 + q) / 2;
			r0 = q / c2;
			r1 = c0 / q;
			r = MathUtil::abs(r0) < MathUtil::abs(r1) ? r0 : r1;
			if (r * r <= dd) {
				y = MathUtil::sqrt(dd - r * r) * bendDir;
				a1 = ta - MathUtil::atan2(y, r);
				a2 = MathUtil::atan2(y / psy, (r - l1) / psx);
				goto break_outer;
			}
		}
		{
			float minAngle = MathUtil::Pi, minX = l1 - a, minDist = minX * minX, minY = 0;
			float maxAngle = 0, maxX = l1 + a, maxDist = maxX * maxX, maxY = 0;
			c0 = -a * l1 / (aa - bb);
			if (c0 >= -1 && c0 <= 1) {
				c0 = MathUtil::acos(c0);
				x = a * MathUtil::cos(c0) + l1;
				y = b * MathUtil::sin(c0);
				d = x * x + y * y;
				if (d < minDist) {
					minAngle = c0;
					minDist = d;
					minX = x;
					minY = y;
				}
				if (d > maxDist) {
					maxAngle = c0;
					maxDist = d;
					maxX = x;
					maxY = y;
				}
			}
			if (dd <= (minDist + maxDist) / 2) {
				a1 = ta - MathUtil::atan2(minY * bendDir, minX);
				a2 = minAngle * bendDir;
			} else {
				a1 = ta - MathUtil::atan2(maxY * bendDir, maxX);
				a2 = maxAngle * bendDir;
			}
		}
	}
	break_outer:
	{
		float os = MathUtil::atan2(cy, cx) * s2;
		a1 = (a1 - os) * MathUtil::Rad_Deg + o1 - parent._arotation;
		if (a1 > 180) a1 -= 360;
		else if (a1 < -180) a1 += 360;
		parent.updateWorldTransform(px, py, parent._rotation + a1 * alpha, sx, parent._ascaleY, 0, 0);
		a2 = ((a2 + os) * MathUtil::Rad_Deg - child._ashearX) * s2 + o2 - child._arotation;
		if (a2 > 180) a2 -= 360;
		else if (a2 < -180) a2 += 360;
		child.updateWorldTransform(cx, cy, child._arotation + a2 * alpha, child._ascaleX, child._ascaleY,
								   child._ashearX, child._ashearY);
	}
}