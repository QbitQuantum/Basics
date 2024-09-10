void Joint::calc_acceleration()
{
	if(!this) return;
	if(parent)
	{
		static fMat33 t_rel_att;
		static fVec3 v1, v2, v3, v4;
		t_rel_att.tran(rel_att);
		// Éð»Ê±ñ1¡¦x
		v1.mul(t_rel_att, parent->loc_ang_vel);
//		v1 += loc_ang_vel;
		v1 *= 2.0;
		v2.cross(v1, rel_lin_vel);
		loc_lin_acc.add(rel_lin_acc, v2);
		v2.cross(parent->loc_ang_acc, rel_pos);
		v1.add(parent->loc_lin_acc, v2);
		v2.cross(parent->loc_ang_vel, rel_pos);
		v3.cross(parent->loc_ang_vel, v2);
		v1 += v3;
		v4.mul(t_rel_att, v1);
		loc_lin_acc += v4;
		// ³Ñ±ñ1¡¦x
//		v1.cross(loc_ang_vel, parent->rel_ang_vel);
		v1.cross(loc_ang_vel, rel_ang_vel);
		loc_ang_acc.add(rel_ang_acc, v1);
		v1.mul(t_rel_att, parent->loc_ang_acc);
		loc_ang_acc += v1;
		// ½Å¿´£öÅð»Ê±ñ1¡¦x
		v1.cross(loc_ang_acc, loc_com);
		loc_com_acc.add(loc_lin_acc, v1);
		v1.cross(loc_ang_vel, loc_com);
		v2.cross(loc_ang_vel, v1);
		loc_com_acc += v2;

//		cerr << name << ": loc_lin_acc = " << loc_lin_acc << endl;
//		cerr << name << ": loc_ang_acc = " << loc_ang_acc << endl;
//		if(real)
//			cerr << name << ": acc = " << abs_att*loc_lin_acc << abs_att*loc_ang_acc << endl;
	}
	else
	{
		// ¥ë¡¼¥È¥ê¥ó¥¯
		// loc_lin_acc£õ"¡¦dÍ÷)¡¦¡¦x£åÂð€¡¦Ãà¡à¡¦Ëà¡¦±êùç¡¦¡¦Çà
		loc_ang_acc.zero();
		loc_com_acc.zero();
	}
	child->calc_acceleration();
	brother->calc_acceleration();
}