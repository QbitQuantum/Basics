	void BodyRigid::forceAccumGlobal(Vect3 const &globalForce, Vect3 const &globalPnt)
	{
	    Vect3 fLocal = m_q.inverse() * globalForce;
	    Vect3 pntLocal = m_q.inverse() * (globalPnt-m_pos);
	    Vect3 tLocal = pntLocal.cross(fLocal);
		//std::cout << "dfadsfads" << std::endl;
	    m_appliedForce +=  globalForce;
		m_appliedTorque += tLocal;
	}