double TP_trendofdelivery_tp_sentido::getAngle(const Vector2d &u,
		const Vector2d &v, const double &t) {
	Vector2d w = v - u;
	Vector2d k = w.normal();
	k = k.normalize() * t;
	k = k + v;
	return k.angle(w);
}