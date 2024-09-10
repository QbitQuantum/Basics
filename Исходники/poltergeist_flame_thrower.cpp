bool CPolterFlame::get_valid_flame_position(const CObject *target_object, Fvector &res_pos)
{
	const CGameObject *Obj = smart_cast<const CGameObject *>(target_object);
	if (!Obj) return (false);

	Fvector dir;
	float h,p;

	Fvector vertex_position;
	Fvector new_pos;

	for (u32 i=0; i<FIND_POINT_ATTEMPT_COUNT; i++) {
		
		target_object->Direction().getHP(h,p);
		h = Random.randF(0, PI_MUL_2);
		dir.setHP(h,p);
		dir.normalize();

		vertex_position = ai().level_graph().vertex_position(Obj->ai_location().level_vertex_id());
		new_pos.mad(vertex_position, dir, Random.randF(m_min_flame_dist, m_max_flame_dist));

		u32 node = ai().level_graph().check_position_in_direction(Obj->ai_location().level_vertex_id(), vertex_position, new_pos);
		if (node != u32(-1)) {
			res_pos = ai().level_graph().vertex_position(node);
			res_pos.y += Random.randF(m_min_flame_height, m_max_flame_height);
			return (true);
		}
	}


	float angle = ai().level_graph().vertex_high_cover_angle(Obj->ai_location().level_vertex_id(),PI_DIV_6,std::less<float>());

	dir.set(1.f,0.f,0.f);
	dir.setHP(angle + PI, 0.f);
	dir.normalize();

	vertex_position = ai().level_graph().vertex_position(Obj->ai_location().level_vertex_id());
	new_pos.mad(vertex_position, dir, Random.randF(m_min_flame_dist, m_max_flame_dist));

	u32 node = ai().level_graph().check_position_in_direction(Obj->ai_location().level_vertex_id(), vertex_position, new_pos);
	if (node != u32(-1)) {
		res_pos = ai().level_graph().vertex_position(node);
		res_pos.y += Random.randF(m_min_flame_height, m_max_flame_height);
		return (true);
	}

	return (false);
}