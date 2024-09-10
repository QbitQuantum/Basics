void CBurer::UpdateGraviObject()
{
	if ( !m_gravi_object.active ) 
	{
		return;
	}
	
	if ( !m_gravi_object.enemy || (m_gravi_object.enemy && m_gravi_object.enemy->getDestroy()) ) 
	{
		m_gravi_object.deactivate();
		return;
	}

	if ( m_gravi_object.from_pos.distance_to(m_gravi_object.cur_pos) 
				> 
		 m_gravi_object.from_pos.distance_to(m_gravi_object.target_pos) ) 
	{
		m_gravi_object.deactivate();
		return;
	}

	float dt = float(Device.dwTimeGlobal - m_gravi_object.time_last_update);
	float dist = dt * float(m_gravi.speed)/1000.f;
		
	if (dist < m_gravi.step) return;
	
	Fvector new_pos;
	Fvector dir;
	dir.sub(m_gravi_object.target_pos,m_gravi_object.cur_pos);
	dir.normalize();
	
	new_pos.mad(m_gravi_object.cur_pos,dir,dist);

	// Trace to enemy 
	Fvector enemy_center;
	m_gravi_object.enemy->Center(enemy_center);
	dir.sub(enemy_center, new_pos);
	dir.normalize();

	float trace_dist = float(m_gravi.step);

	collide::rq_result	l_rq;
	if (Level().ObjectSpace.RayPick(new_pos, dir, trace_dist, collide::rqtBoth, l_rq, NULL)) {
		const CObject *enemy = smart_cast<const CObject *>(m_gravi_object.enemy);
		if ((l_rq.O == enemy) && (l_rq.range < trace_dist)) {
			
			// check for visibility
			bool b_enemy_visible = false;
			xr_vector<CObject *> visible_objects;
			feel_vision_get(visible_objects);

			// find object
			for (u32 i = 0; i<visible_objects.size(); i++) {
				if (visible_objects[i] == enemy) {
					b_enemy_visible = true;
					break;
				}
			}
			
			if (b_enemy_visible) {
				Fvector impulse_dir;

				impulse_dir.set(0.0f,0.0f,1.0f);
				impulse_dir.normalize();

				HitEntity(m_gravi_object.enemy, m_gravi.hit_power, m_gravi.impulse_to_enemy, impulse_dir, ALife::eHitTypeStrike, false);
				m_gravi_object.deactivate();
				return;
			}
		}
	}
																								
	m_gravi_object.cur_pos				= new_pos;
	m_gravi_object.time_last_update		= Device.dwTimeGlobal;

	// ---------------------------------------------------------------------
	// draw particle
	CParticlesObject* ps = CParticlesObject::Create(particle_gravi_wave,TRUE);

	// вычислить позицию и направленность партикла
	Fmatrix pos; 
	pos.identity();
	pos.k.set(dir);
	Fvector::generate_orthonormal_basis_normalized(pos.k,pos.j,pos.i);
	// установить позицию
	pos.translate_over(m_gravi_object.cur_pos);

	ps->UpdateParent(pos, zero_vel);
	ps->Play(false);
	
	// hit objects
	m_nearest.clear_not_free		();
	Level().ObjectSpace.GetNearest	(m_nearest,m_gravi_object.cur_pos, m_gravi.radius, NULL); 
	//xr_vector<CObject*> &m_nearest = Level().ObjectSpace.q_nearest;

	for (u32 i=0;i<m_nearest.size();i++) {
		CPhysicsShellHolder  *obj = smart_cast<CPhysicsShellHolder *>(m_nearest[i]);
		if (!obj || !obj->m_pPhysicsShell) continue;
		
		Fvector dir;
		dir.sub(obj->Position(), m_gravi_object.cur_pos);
		dir.normalize();
		obj->m_pPhysicsShell->applyImpulse(dir,m_gravi.impulse_to_objects * obj->m_pPhysicsShell->getMass());
	}

	// играть звук
	Fvector snd_pos = m_gravi_object.cur_pos;
	snd_pos.y += 0.5f;
	if (sound_gravi_wave._feedback())		{
		sound_gravi_wave.set_position	(snd_pos);
	} else ::Sound->play_at_pos			(sound_gravi_wave,0,snd_pos);
}