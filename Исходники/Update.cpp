void pSubChain::disassembly_leaf()
{
	Joint* target_joint = links[0]->joint;
//	if(!target_joint->parent) return;  // skip space
	// convert all forces/moments to joint frame
	cerr << "---- " << target_joint->name << ": disassembly_leaf" << endl;
	int i;
	static fVec3 total_f, total_n;
	static fVec3 pos;
	static fMat33 att, t_att;
	static fVec acc(6);
	static fVec allf(6);
	total_f.zero();
	total_n.zero();
	acc.zero();
	pos.set(target_joint->abs_pos);
	att.set(target_joint->abs_att);
	t_att.tran(att);
	for(i=0; i<n_outer_joints; i++)
	{
		static fVec3 loc_f, loc_n, f, n, fn;
		static fVec3 jpos, rel_pos, pp;
		static fMat33 jatt, rel_att;
		cerr << "outer[" << i << "]: " << outer_joints[i]->joint->name << endl;
		cerr << "f_final = " << tran(outer_joints[i]->f_final) << endl;
		loc_f(0) = outer_joints[i]->f_final(0);
		loc_f(1) = outer_joints[i]->f_final(1);
		loc_f(2) = outer_joints[i]->f_final(2);
		loc_n(0) = outer_joints[i]->f_final(3);
		loc_n(1) = outer_joints[i]->f_final(4);
		loc_n(2) = outer_joints[i]->f_final(5);
		jpos.set(outer_joints[i]->joint->abs_pos);
		jatt.set(outer_joints[i]->joint->abs_att);
		pp.sub(jpos, pos);
		rel_pos.mul(t_att, pp);
		rel_att.mul(t_att, jatt);
		f.mul(rel_att, loc_f);  // force
		n.mul(rel_att, loc_n);
		fn.cross(rel_pos, f);
		n += fn;
		cerr << "(f n) = " << f << n << endl;
		total_f += f;
		total_n += n;
	}
	allf(0) = total_f(0);
	allf(1) = total_f(1);
	allf(2) = total_f(2);
	allf(3) = total_n(0);
	allf(4) = total_n(1);
	allf(5) = total_n(2);
	cerr << "total_f = " << total_f << endl;
	cerr << "total_n = " << total_n << endl;
	acc.lineq_posv(links[0]->M, allf);
	acc += links[0]->acc;
	cerr << "Minv = " << links[0]->Minv << endl;
	cerr << "acc = " << tran(links[0]->acc) << endl;
	cerr << "link acc = " << tran(acc) << endl;
}