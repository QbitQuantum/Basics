bool CPolterTele::tele_raise_objects()
{
	// find objects near actor
	xr_vector<CObject*>		tele_objects;
	tele_objects.reserve	(20);

	// получить список объектов вокруг врага
	tele_find_objects	(tele_objects, Actor()->Position());

	// получить список объектов вокруг монстра
	tele_find_objects	(tele_objects, m_object->Position());

	// получить список объектов между монстром и врагом
	float dist			= Actor()->Position().distance_to(m_object->Position());
	Fvector dir;
	dir.sub				(Actor()->Position(), m_object->Position());
	dir.normalize		();

	Fvector pos;
	pos.mad				(m_object->Position(), dir, dist / 2.f);
	tele_find_objects	(tele_objects, pos);	

	// сортировать и оставить только необходимое количество объектов
	std::sort(tele_objects.begin(),tele_objects.end(),best_object_predicate2(m_object->Position(), Actor()->Position()));
	
	// оставить уникальные объекты
	tele_objects.erase	(
		std::unique(
			tele_objects.begin(),
			tele_objects.end()
		),
		tele_objects.end()
	);

	// оставить необходимое количество объектов
	//if (tele_objects.size() > m_pmt_tele_object_count) tele_objects.resize	(m_pmt_tele_object_count);

	//// активировать
	//for (u32 i=0; i<tele_objects.size(); i++) {
	//	CPhysicsShellHolder *obj = smart_cast<CPhysicsShellHolder *>(tele_objects[i]);

	//	// применить телекинез на объект
	//	bool	rotate = false;

	//	CTelekinesis::activate		(obj, m_pmt_tele_raise_speed, m_pmt_tele_object_height, m_pmt_tele_time_object_keep, rotate);
	//}

	if (!tele_objects.empty()) {
		CPhysicsShellHolder *obj = smart_cast<CPhysicsShellHolder *>(tele_objects[0]);

		// применить телекинез на объект
		bool	rotate = false;

		CTelekineticObject		*tele_obj = m_object->CTelekinesis::activate		(obj, m_pmt_raise_speed, m_pmt_object_height, m_pmt_time_object_keep, rotate);
		tele_obj->set_sound		(m_sound_tele_hold,m_sound_tele_throw);

		return true;
	}

	return false;
}