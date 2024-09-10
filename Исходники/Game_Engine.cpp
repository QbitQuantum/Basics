Polygon2D < double > Game_Engine::Polygon_from(const Point2D < double > &C_p, const Vector2D < double > &V, const double &w) {
	vector < Point2D < double > > Pol;
	if (abs(V.y) < EPS) {
		Pol.push_back(Point2D < double >(C_p.x, C_p.y - w / 2.0));
		Pol.push_back(Point2D < double >(C_p.x, C_p.y + w / 2.0));
		Pol.push_back(Pol[0] + V);
		Pol.push_back(Pol[1] + V);
	}
	else {
		if (abs(V.x) < EPS) {
			Pol.push_back(Point2D < double >(C_p.x - w / 2.0, C_p.y));
			Pol.push_back(Point2D < double >(C_p.x + w / 2.0, C_p.y));
			Pol.push_back(Pol[0] + V);
			Pol.push_back(Pol[1] + V);
		}
		else {
			Pol.push_back(Point2D < double >(C_p.x + w / (2.0*SQRT(1 + SQR(V.x / V.y))), 0));
			Pol[0].y = C_p.y - V.x*(Pol[0].x - C_p.x) / V.y;
			Pol.push_back(Point2D < double >(C_p.x - w / (2.0*SQRT(1 + SQR(V.x / V.y))), 0));
			Pol[1].y = C_p.y - V.x*(Pol[1].x - C_p.x) / V.y;
			Pol.push_back(Pol[1] + V);
			Pol.push_back(Pol[0] + V);
		}
	}
	return Polygon2D < double >(Pol);
}