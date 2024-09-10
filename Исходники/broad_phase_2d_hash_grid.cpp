int BroadPhase2DHashGrid::cull_segment(const Vector2& p_from, const Vector2& p_to,CollisionObject2DSW** p_results,int p_max_results,int *p_result_indices) {

	pass++;

	Vector2 dir = (p_to-p_from);
	if (dir==Vector2())
		return 0;
	//avoid divisions by zero
	dir.normalize();
	if (dir.x==0.0)
		dir.x=0.000001;
	if (dir.y==0.0)
		dir.y=0.000001;
	Vector2 delta = dir.abs();

	delta.x=cell_size/delta.x;
	delta.y=cell_size/delta.y;

	Point2i pos = p_from.floor() / cell_size;
	Point2i end = p_to.floor() / cell_size;
	Point2i step = Vector2( SGN(dir.x), SGN(dir.y));

	Vector2 max;

	if (dir.x<0)
		max.x= (Math::floor(pos.x)*cell_size - p_from.x) / dir.x;
	else
		max.x= (Math::floor(pos.x + 1)*cell_size - p_from.x) / dir.x;

	if (dir.y<0)
		max.y= (Math::floor(pos.y)*cell_size - p_from.y) / dir.y;
	else
		max.y= (Math::floor(pos.y + 1)*cell_size - p_from.y) / dir.y;

	int cullcount=0;
	_cull<false,true>(pos,Rect2(),p_from,p_to,p_results,p_max_results,p_result_indices,cullcount);

	bool reached_x=false;
	bool reached_y=false;

	while(true) {

		if (max.x < max.y) {

			max.x+=delta.x;
			pos.x+=step.x;
		} else {

			max.y+=delta.y;
			pos.y+=step.y;

		}

		if (step.x>0) {
			if (pos.x>=end.x)
				reached_x=true;
		} else if (pos.x<=end.x) {

			reached_x=true;
		}

		if (step.y>0) {
			if (pos.y>=end.y)
				reached_y=true;
		} else if (pos.y<=end.y) {

			reached_y=true;
		}

		_cull<false,true>(pos,Rect2(),p_from,p_to,p_results,p_max_results,p_result_indices,cullcount);

		if (reached_x && reached_y)
			break;

	}

	return cullcount;
}