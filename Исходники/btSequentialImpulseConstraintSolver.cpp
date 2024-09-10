 void btSequentialImpulseConstraintSolver::resolveSplitPenetrationSIMD(btRigidBody& body1,btRigidBody& body2,const btSolverConstraint& c)
{
#ifdef USE_SIMD
	if (!c.m_rhsPenetration)
		return;

	gNumSplitImpulseRecoveries++;

	__m128 cpAppliedImp = _mm_set1_ps(c.m_appliedPushImpulse);
	__m128	lowerLimit1 = _mm_set1_ps(c.m_lowerLimit);
	__m128	upperLimit1 = _mm_set1_ps(c.m_upperLimit);
	__m128 deltaImpulse = _mm_sub_ps(_mm_set1_ps(c.m_rhsPenetration), _mm_mul_ps(_mm_set1_ps(c.m_appliedPushImpulse),_mm_set1_ps(c.m_cfm)));
	__m128 deltaVel1Dotn	=	_mm_add_ps(btSimdDot3(c.m_contactNormal.mVec128,body1.internalGetPushVelocity().mVec128), btSimdDot3(c.m_relpos1CrossNormal.mVec128,body1.internalGetTurnVelocity().mVec128));
	__m128 deltaVel2Dotn	=	_mm_sub_ps(btSimdDot3(c.m_relpos2CrossNormal.mVec128,body2.internalGetTurnVelocity().mVec128),btSimdDot3((c.m_contactNormal).mVec128,body2.internalGetPushVelocity().mVec128));
	deltaImpulse	=	_mm_sub_ps(deltaImpulse,_mm_mul_ps(deltaVel1Dotn,_mm_set1_ps(c.m_jacDiagABInv)));
	deltaImpulse	=	_mm_sub_ps(deltaImpulse,_mm_mul_ps(deltaVel2Dotn,_mm_set1_ps(c.m_jacDiagABInv)));
	btSimdScalar sum = _mm_add_ps(cpAppliedImp,deltaImpulse);
	btSimdScalar resultLowerLess,resultUpperLess;
	resultLowerLess = _mm_cmplt_ps(sum,lowerLimit1);
	resultUpperLess = _mm_cmplt_ps(sum,upperLimit1);
	__m128 lowMinApplied = _mm_sub_ps(lowerLimit1,cpAppliedImp);
	deltaImpulse = _mm_or_ps( _mm_and_ps(resultLowerLess, lowMinApplied), _mm_andnot_ps(resultLowerLess, deltaImpulse) );
	c.m_appliedImpulse = _mm_or_ps( _mm_and_ps(resultLowerLess, lowerLimit1), _mm_andnot_ps(resultLowerLess, sum) );
	__m128	linearComponentA = _mm_mul_ps(c.m_contactNormal.mVec128,body1.internalGetInvMass().mVec128);
	__m128	linearComponentB = _mm_mul_ps((c.m_contactNormal).mVec128,body2.internalGetInvMass().mVec128);
	__m128 impulseMagnitude = deltaImpulse;
	body1.internalGetPushVelocity().mVec128 = _mm_add_ps(body1.internalGetPushVelocity().mVec128,_mm_mul_ps(linearComponentA,impulseMagnitude));
	body1.internalGetTurnVelocity().mVec128 = _mm_add_ps(body1.internalGetTurnVelocity().mVec128 ,_mm_mul_ps(c.m_angularComponentA.mVec128,impulseMagnitude));
	body2.internalGetPushVelocity().mVec128 = _mm_sub_ps(body2.internalGetPushVelocity().mVec128,_mm_mul_ps(linearComponentB,impulseMagnitude));
	body2.internalGetTurnVelocity().mVec128 = _mm_add_ps(body2.internalGetTurnVelocity().mVec128 ,_mm_mul_ps(c.m_angularComponentB.mVec128,impulseMagnitude));
#else
	resolveSplitPenetrationImpulseCacheFriendly(body1,body2,c);
#endif
}