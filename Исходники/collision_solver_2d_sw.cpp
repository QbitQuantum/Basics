bool CollisionSolver2DSW::solve_static_line(const Shape2DSW *p_shape_A,const Matrix32& p_transform_A,const Shape2DSW *p_shape_B,const Matrix32& p_transform_B,CallbackResult p_result_callback,void *p_userdata,bool p_swap_result) {


	const LineShape2DSW *line = static_cast<const LineShape2DSW*>(p_shape_A);
	if (p_shape_B->get_type()==Physics2DServer::SHAPE_LINE)
		return false;


	Vector2 n = p_transform_A.basis_xform(line->get_normal()).normalized();
	Vector2 p = p_transform_A.xform(line->get_normal()*line->get_d());
	real_t d = n.dot(p);

	Vector2 supports[2];
	int support_count;

	p_shape_B->get_supports(p_transform_A.affine_inverse().basis_xform(-n).normalized(),supports,support_count);

	bool found=false;


	for(int i=0;i<support_count;i++) {

		supports[i] = p_transform_B.xform( supports[i] );
		real_t pd = n.dot(supports[i]);
		if (pd>=d)
			continue;
		found=true;

		Vector2 support_A = supports[i] - n*(pd-d);

		if (p_result_callback) {
			if (p_swap_result)
				p_result_callback(supports[i],support_A,p_userdata);
			else
				p_result_callback(support_A,supports[i],p_userdata);
		}

	}


	return found;
}