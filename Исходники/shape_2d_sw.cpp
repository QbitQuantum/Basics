void ConcavePolygonShape2DSW::get_supports(const Vector2& p_normal,Vector2 *r_supports,int & r_amount) const {

	real_t d=-1e10;
	int idx=-1;
	for(int i=0;i<points.size();i++) {

		real_t ld = p_normal.dot(points[i]);
		if (ld>d) {
			d=ld;
			idx=i;
		}
	}


	r_amount=1;
	ERR_FAIL_COND(idx==-1);
	*r_supports=points[idx];

}