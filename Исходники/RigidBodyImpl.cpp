	void SetTransform(const btTransform& aT, VectorMap<void*, int>& set){
		if (set.Find(mSelf) != set.end())
			return;
		mSelf->setWorldTransform(aT);
		mSelf->clearForces();
		set[mSelf] = 1;
		if (mGameFlag != 0)
			Logger::Log(FB_DEFAULT_LOG_ARG, FormatString("(info) Setting rigid body transform for %d", mGameFlag).c_str());
		auto numConstraints = mSelf->getNumConstraintRefs();
		for (int i = 0; i < numConstraints; ++i){
			auto con = mSelf->getConstraintRef(i);
			auto conType = con->getConstraintType();
			if (conType == FIXED_CONSTRAINT_TYPE || conType == D6_SPRING_2_CONSTRAINT_TYPE){
				btFixedConstraint* fixedCon = (btFixedConstraint*)con;
				auto a = &con->getRigidBodyA();
				auto b = &con->getRigidBodyB();
				auto trA = fixedCon->getFrameOffsetA();
				auto trB = fixedCon->getFrameOffsetB();
				if (b->getUserPointer() == mSelf){
					std::swap(a, b);
					std::swap(trA, trB);
				}
				auto bT = aT * trA * trB.inverse();
				auto rigidBodyImpl = (RigidBodyImpl*)b->getUserPointer();
				rigidBodyImpl->mImpl->SetTransform(bT, set);				
			}
		}
		mSelf->activate();
	}