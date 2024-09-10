static Joint* createLink(::World* world, const char* charname, int index, LinkInfoSequence_var iLinks, Joint* pjoint)
{
	Chain* _chain = (Chain*)world->Chain();
	LinkInfo iLink = iLinks[index];

//	logfile << "create: " << iLink->name() << ", jointId = " << iLink->jointId() << endl;
	CORBA::String_var name = iLink.name;
	std::string myname;
	char sep[2];
	sep[0] = charname_separator;
	sep[1] = '\0';
	myname = std::string(name) + std::string(sep) + std::string(charname);
	Joint* jnt = new Joint(myname.c_str());

	_chain->AddJoint(jnt, pjoint);

	int jointId = iLink.jointId;
	jnt->i_joint = jointId;

	CORBA::String_var jointType = iLink.jointType;
	const std::string jt(jointType);

	if(jt == "fixed")
	{
		jnt->j_type = ::JFIXED;
	}
	else if(jt == "free")
	{
		jnt->j_type = ::JFREE;
	}
	else if(jt == "rotate")
	{
		jnt->j_type = ::JROTATE;
	}
	else if(jt == "slide")
	{
		jnt->j_type = ::JSLIDE;
	}
	else
	{
		jnt->j_type = ::JFREE;
	}

	if(jointId < 0)
	{
		if(jnt->j_type == ::JROTATE || jnt->j_type == ::JSLIDE)
		{
			std::cerr << "Warning:  Joint ID is not given to joint " << jnt->name
					  << " of character " << charname << "." << std::endl;
		}
	}

	const DblArray3& t =iLink.translation;
	static fVec3 rel_pos;
	array_to_vec3(t, rel_pos);

	const DblArray4& r = iLink.rotation;
	static fMat33 rel_att;
	array_to_mat33(r, rel_att);

	// joint axis is always set to z axis; use init_att as the origin
	// of the joint axis
	if(jnt->j_type == ::JROTATE || jnt->j_type == ::JSLIDE)
	{
		const DblArray3& a = iLink.jointAxis;
		static fVec3 loc_axis;
		array_to_vec3(a, loc_axis);
//		logfile << "loc_axis = " << loc_axis << endl;
//		logfile << "rel_att = " << rel_att << endl;
//		logfile << "rel_pos = " << rel_pos << endl;
#if 0
		static fMat33 init_att;
		static fVec3 p_axis;
		p_axis.mul(rel_att, loc_axis);  // joint axis in parent frame -> z axis
		static fVec3 x, y;
		x.set(1.0, 0.0, 0.0);
		y.set(0.0, 1.0, 0.0);
		double zx = p_axis*x;
		x -= zx * p_axis;
		double xlen = x.length();
		if(xlen > 1e-8)
		{
			x /= xlen;
			y.cross(p_axis, x);
		}
		else
		{
			double yz = y*p_axis;
			y -= yz * p_axis;
			double ylen = y.length();
			y /= ylen;
			x.cross(y, p_axis);
		}
		init_att(0,0) = x(0); init_att(1,0) = x(1); init_att(2,0) = x(2);
		init_att(0,1) = y(0); init_att(1,1) = y(1); init_att(2,1) = y(2);
		init_att(0,2) = p_axis(0); init_att(1,2) = p_axis(1); init_att(2,2) = p_axis(2);
		if(jnt->j_type == JROTATE)
			jnt->SetRotateJointType(rel_pos, init_att, AXIS_Z);
		else if(jnt->j_type == JSLIDE)
			jnt->SetSlideJointType(rel_pos, init_att, AXIS_Z);
//		logfile << "init_att = " << init_att << endl;
#else
		AxisIndex axis = AXIS_NULL;
		if(loc_axis(0) > 0.95) axis = AXIS_X;
		else if(loc_axis(1) > 0.95) axis = AXIS_Y;
		else if(loc_axis(2) > 0.95) axis = AXIS_Z;
        else{ 
            std::cerr << "unsupported joint axis for " << myname
                      << ", only X, Y and Z axes are supported" << std::endl;
        }
		assert(axis != AXIS_NULL);
		if(jnt->j_type == JROTATE)
			jnt->SetRotateJointType(rel_pos, rel_att, axis);
		else if(jnt->j_type == JSLIDE)
			jnt->SetSlideJointType(rel_pos, rel_att, axis);
#endif
//		logfile << "n_dof = " << jnt->n_dof << endl;
	}
	else if(jnt->j_type == ::JSPHERE)
	{
		jnt->SetSphereJointType(rel_pos, rel_att);
	}
	else if(jnt->j_type == ::JFIXED)
	{
		jnt->SetFixedJointType(rel_pos, rel_att);
	}
	else if(jnt->j_type == ::JFREE)
	{
//		logfile << "rel_pos = " << rel_pos << endl;
//		logfile << "rel_att = " << rel_att << endl;
		jnt->SetFreeJointType(rel_pos, rel_att);
	}
	
	jnt->mass = iLink.mass;

	//double equivalentInertia = iLink.equivalentInertia();

	//if(equivalentInertia == 0.0){
	//	jnt->rotor_inertia = iLink.rotorInertia;
	//	jnt->gear_ratio = iLink.gearRatio;
	//} else {
	//	//jnt->rotor_inertia = equivalentInertia;
	//	jnt->gear_ratio = 1.0;
	//}
		
	//link->Jm2	        = iLink.equivalentInertia();
	//link->torqueConst	= iLink.torqueConst();
	//if (link->Jm2 == 0){
	//	link->Jm2 = link->Ir * link->gearRatio * link->gearRatio;
	//}
	//link->encoderPulse	= iLink.encoderPulse();

	//DblSequence_var ulimit  = iLink.ulimit();
	//DblSequence_var llimit  = iLink.llimit();
	//DblSequence_var uvlimit = iLink.uvlimit();
	//DblSequence_var lvlimit = iLink.lvlimit();

	//double maxlimit = numeric_limits<double>::max();

	//link->ulimit  = getLimitValue(ulimit,  +maxlimit);
	//link->llimit  = getLimitValue(llimit,  -maxlimit);
	//link->uvlimit = getLimitValue(uvlimit, +maxlimit);
	//link->lvlimit = getLimitValue(lvlimit, -maxlimit);

	const DblArray3& rc = iLink.centerOfMass;
	static fVec3 com;
	array_to_vec3(rc, com);
	jnt->loc_com.set(com);

	const DblArray9& I = iLink.inertia;
	static fMat33 inertia;
	array_to_mat33(I, inertia);
	jnt->inertia.set(inertia);

	//int sindex = iLinks[index].sister();
	//	createLink(world, charname, sindex, iLinks, pjoint);

	for( unsigned int i = 0 ; i < iLinks[index].childIndices.length() ; i++ ) 
	{
		if( 0 <= iLinks[index].childIndices[i] )
		{
			createLink(world, charname, iLinks[index].childIndices[i], iLinks, jnt);
		}
	}

	createSensors(world, jnt, iLink.sensors);

	return jnt;
}