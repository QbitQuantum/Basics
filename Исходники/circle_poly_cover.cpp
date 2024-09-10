/* called by Area(const Polygon&) */
double calc(const Point &rhs1, const Point &rhs2){
	vector<Point> p;
	bool in1 = (cmp(rhs1.Abs()-R) < 0);
	bool in2 = (cmp(rhs2.Abs()-R) < 0);
	if(in1){
		if(in2)
			return fabs(rhs1.Cross(rhs2)) / 2.0;
		else{
			p = Intersection(Line(rhs1, rhs2));
			return SectorArea(rhs2, p[0]) + fabs(rhs1.Cross(p[0])) / 2.0;
		}
	}else{
		if(in2){
			p = Intersection(Line(rhs1, rhs2));
			return SectorArea(p[0], rhs1) + fabs(rhs2.Cross(p[0])) / 2.0;
		}else{
			p = Intersection(Line(rhs1, rhs2));
			if((int)p.size() == 2){
				return SectorArea(rhs1, p[0]) + SectorArea(p[1], rhs2) + fabs(p[0].Cross(p[1])) / 2.0;
			}else{
				return SectorArea(rhs1, rhs2);
			}
		}
	}
}