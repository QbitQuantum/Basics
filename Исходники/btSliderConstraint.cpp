void btSliderConstraint::getInfo2NonVirtual(btConstraintInfo2* info, const btTransform& transA,const btTransform& transB, const btVector3& linVelA,const btVector3& linVelB, btScalar rbAinvMass,btScalar rbBinvMass  )
{
	const btTransform& trA = getCalculatedTransformA();
	const btTransform& trB = getCalculatedTransformB();
	
	btAssert(!m_useSolveConstraintObsolete);
	int i, s = info->rowskip;
	
	btScalar signFact = m_useLinearReferenceFrameA ? btScalar(1.0f) : btScalar(-1.0f);
	
	// difference between frames in WCS
	btVector3 ofs = trB.getOrigin() - trA.getOrigin();
	// now get weight factors depending on masses
	btScalar miA = rbAinvMass;
	btScalar miB = rbBinvMass;
	bool hasStaticBody = (miA < SIMD_EPSILON) || (miB < SIMD_EPSILON);
	btScalar miS = miA + miB;
	btScalar factA, factB;
	if(miS > btScalar(0.f))
	{
		factA = miB / miS;
	}
	else 
	{
		factA = btScalar(0.5f);
	}
	factB = btScalar(1.0f) - factA;
	btVector3 ax1, p, q;
	btVector3 ax1A = trA.getBasis().getColumn(0);
	btVector3 ax1B = trB.getBasis().getColumn(0);
	if(m_useOffsetForConstraintFrame)
	{
		// get the desired direction of slider axis
		// as weighted sum of X-orthos of frameA and frameB in WCS
		ax1 = ax1A * factA + ax1B * factB;
		ax1.normalize();
		// construct two orthos to slider axis
		btPlaneSpace1 (ax1, p, q);
	}
	else
	{ // old way - use frameA
		ax1 = trA.getBasis().getColumn(0);
		// get 2 orthos to slider axis (Y, Z)
		p = trA.getBasis().getColumn(1);
		q = trA.getBasis().getColumn(2);
	}
	// make rotations around these orthos equal
	// the slider axis should be the only unconstrained
	// rotational axis, the angular velocity of the two bodies perpendicular to
	// the slider axis should be equal. thus the constraint equations are
	//    p*w1 - p*w2 = 0
	//    q*w1 - q*w2 = 0
	// where p and q are unit vectors normal to the slider axis, and w1 and w2
	// are the angular velocity vectors of the two bodies.
	info->m_J1angularAxis[0] = p[0];
	info->m_J1angularAxis[1] = p[1];
	info->m_J1angularAxis[2] = p[2];
	info->m_J1angularAxis[s+0] = q[0];
	info->m_J1angularAxis[s+1] = q[1];
	info->m_J1angularAxis[s+2] = q[2];

	info->m_J2angularAxis[0] = -p[0];
	info->m_J2angularAxis[1] = -p[1];
	info->m_J2angularAxis[2] = -p[2];
	info->m_J2angularAxis[s+0] = -q[0];
	info->m_J2angularAxis[s+1] = -q[1];
	info->m_J2angularAxis[s+2] = -q[2];
	// compute the right hand side of the constraint equation. set relative
	// body velocities along p and q to bring the slider back into alignment.
	// if ax1A,ax1B are the unit length slider axes as computed from bodyA and
	// bodyB, we need to rotate both bodies along the axis u = (ax1 x ax2).
	// if "theta" is the angle between ax1 and ax2, we need an angular velocity
	// along u to cover angle erp*theta in one step :
	//   |angular_velocity| = angle/time = erp*theta / stepsize
	//                      = (erp*fps) * theta
	//    angular_velocity  = |angular_velocity| * (ax1 x ax2) / |ax1 x ax2|
	//                      = (erp*fps) * theta * (ax1 x ax2) / sin(theta)
	// ...as ax1 and ax2 are unit length. if theta is smallish,
	// theta ~= sin(theta), so
	//    angular_velocity  = (erp*fps) * (ax1 x ax2)
	// ax1 x ax2 is in the plane space of ax1, so we project the angular
	// velocity to p and q to find the right hand side.
//	btScalar k = info->fps * info->erp * getSoftnessOrthoAng();
	btScalar currERP = (m_flags & BT_SLIDER_FLAGS_ERP_ORTANG) ? m_softnessOrthoAng : m_softnessOrthoAng * info->erp;
	btScalar k = info->fps * currERP;

	btVector3 u = ax1A.cross(ax1B);
	info->m_constraintError[0] = k * u.dot(p);
	info->m_constraintError[s] = k * u.dot(q);
	if(m_flags & BT_SLIDER_FLAGS_CFM_ORTANG)
	{
		info->cfm[0] = m_cfmOrthoAng;
		info->cfm[s] = m_cfmOrthoAng;
	}

	int nrow = 1; // last filled row
	int srow;
	btScalar limit_err;
	int limit;
	int powered;

	// next two rows. 
	// we want: velA + wA x relA == velB + wB x relB ... but this would
	// result in three equations, so we project along two orthos to the slider axis

	btTransform bodyA_trans = transA;
	btTransform bodyB_trans = transB;
	nrow++;
	int s2 = nrow * s;
	nrow++;
	int s3 = nrow * s;
	btVector3 tmpA(0,0,0), tmpB(0,0,0), relA(0,0,0), relB(0,0,0), c(0,0,0);
	if(m_useOffsetForConstraintFrame)
	{
		// get vector from bodyB to frameB in WCS
		relB = trB.getOrigin() - bodyB_trans.getOrigin();
		// get its projection to slider axis
		btVector3 projB = ax1 * relB.dot(ax1);
		// get vector directed from bodyB to slider axis (and orthogonal to it)
		btVector3 orthoB = relB - projB;
		// same for bodyA
		relA = trA.getOrigin() - bodyA_trans.getOrigin();
		btVector3 projA = ax1 * relA.dot(ax1);
		btVector3 orthoA = relA - projA;
		// get desired offset between frames A and B along slider axis
		btScalar sliderOffs = m_linPos - m_depth[0];
		// desired vector from projection of center of bodyA to projection of center of bodyB to slider axis
		btVector3 totalDist = projA + ax1 * sliderOffs - projB;
		// get offset vectors relA and relB
		relA = orthoA + totalDist * factA;
		relB = orthoB - totalDist * factB;
		// now choose average ortho to slider axis
		p = orthoB * factA + orthoA * factB;
		btScalar len2 = p.length2();
		if(len2 > SIMD_EPSILON)
		{
			p /= btSqrt(len2);
		}
		else
		{
			p = trA.getBasis().getColumn(1);
		}
		// make one more ortho
		q = ax1.cross(p);
		// fill two rows
		tmpA = relA.cross(p);
		tmpB = relB.cross(p);
		for (i=0; i<3; i++) info->m_J1angularAxis[s2+i] = tmpA[i];
		for (i=0; i<3; i++) info->m_J2angularAxis[s2+i] = -tmpB[i];
		tmpA = relA.cross(q);
		tmpB = relB.cross(q);
		if(hasStaticBody && getSolveAngLimit())
		{ // to make constraint between static and dynamic objects more rigid
			// remove wA (or wB) from equation if angular limit is hit
			tmpB *= factB;
			tmpA *= factA;
		}
		for (i=0; i<3; i++) info->m_J1angularAxis[s3+i] = tmpA[i];
		for (i=0; i<3; i++) info->m_J2angularAxis[s3+i] = -tmpB[i];
		for (i=0; i<3; i++) info->m_J1linearAxis[s2+i] = p[i];
		for (i=0; i<3; i++) info->m_J1linearAxis[s3+i] = q[i];
		for (i=0; i<3; i++) info->m_J2linearAxis[s2+i] = -p[i];
		for (i=0; i<3; i++) info->m_J2linearAxis[s3+i] = -q[i];
	}
	else
	{	// old way - maybe incorrect if bodies are not on the slider axis
		// see discussion "Bug in slider constraint" http://bulletphysics.org/Bullet/phpBB3/viewtopic.php?f=9&t=4024&start=0
		c = bodyB_trans.getOrigin() - bodyA_trans.getOrigin();
		btVector3 tmp = c.cross(p);
		for (i=0; i<3; i++) info->m_J1angularAxis[s2+i] = factA*tmp[i];
		for (i=0; i<3; i++) info->m_J2angularAxis[s2+i] = factB*tmp[i];
		tmp = c.cross(q);
		for (i=0; i<3; i++) info->m_J1angularAxis[s3+i] = factA*tmp[i];
		for (i=0; i<3; i++) info->m_J2angularAxis[s3+i] = factB*tmp[i];

		for (i=0; i<3; i++) info->m_J1linearAxis[s2+i] = p[i];
		for (i=0; i<3; i++) info->m_J1linearAxis[s3+i] = q[i];
		for (i=0; i<3; i++) info->m_J2linearAxis[s2+i] = -p[i];
		for (i=0; i<3; i++) info->m_J2linearAxis[s3+i] = -q[i];
	}
	// compute two elements of right hand side

	//	k = info->fps * info->erp * getSoftnessOrthoLin();
	currERP = (m_flags & BT_SLIDER_FLAGS_ERP_ORTLIN) ? m_softnessOrthoLin : m_softnessOrthoLin * info->erp;
	k = info->fps * currERP;

	btScalar rhs = k * p.dot(ofs);
	info->m_constraintError[s2] = rhs;
	rhs = k * q.dot(ofs);
	info->m_constraintError[s3] = rhs;
	if(m_flags & BT_SLIDER_FLAGS_CFM_ORTLIN)
	{
		info->cfm[s2] = m_cfmOrthoLin;
		info->cfm[s3] = m_cfmOrthoLin;
	}


	// check linear limits
	limit_err = btScalar(0.0);
	limit = 0;
	if(getSolveLinLimit())
	{
		limit_err = getLinDepth() *  signFact;
		limit = (limit_err > btScalar(0.0)) ? 2 : 1;
	}
	powered = 0;
	if(getPoweredLinMotor())
	{
		powered = 1;
	}
	// if the slider has joint limits or motor, add in the extra row
	if (limit || powered) 
	{
		nrow++;
		srow = nrow * info->rowskip;
		info->m_J1linearAxis[srow+0] = ax1[0];
		info->m_J1linearAxis[srow+1] = ax1[1];
		info->m_J1linearAxis[srow+2] = ax1[2];
		info->m_J2linearAxis[srow+0] = -ax1[0];
		info->m_J2linearAxis[srow+1] = -ax1[1];
		info->m_J2linearAxis[srow+2] = -ax1[2];
		// linear torque decoupling step:
		//
		// we have to be careful that the linear constraint forces (+/- ax1) applied to the two bodies
		// do not create a torque couple. in other words, the points that the
		// constraint force is applied at must lie along the same ax1 axis.
		// a torque couple will result in limited slider-jointed free
		// bodies from gaining angular momentum.
		if(m_useOffsetForConstraintFrame)
		{
			// this is needed only when bodyA and bodyB are both dynamic.
			if(!hasStaticBody)
			{
				tmpA = relA.cross(ax1);
				tmpB = relB.cross(ax1);
				info->m_J1angularAxis[srow+0] = tmpA[0];
				info->m_J1angularAxis[srow+1] = tmpA[1];
				info->m_J1angularAxis[srow+2] = tmpA[2];
				info->m_J2angularAxis[srow+0] = -tmpB[0];
				info->m_J2angularAxis[srow+1] = -tmpB[1];
				info->m_J2angularAxis[srow+2] = -tmpB[2];
			}
		}
		else
		{ // The old way. May be incorrect if bodies are not on the slider axis
			btVector3 ltd;	// Linear Torque Decoupling vector (a torque)
			ltd = c.cross(ax1);
			info->m_J1angularAxis[srow+0] = factA*ltd[0];
			info->m_J1angularAxis[srow+1] = factA*ltd[1];
			info->m_J1angularAxis[srow+2] = factA*ltd[2];
			info->m_J2angularAxis[srow+0] = factB*ltd[0];
			info->m_J2angularAxis[srow+1] = factB*ltd[1];
			info->m_J2angularAxis[srow+2] = factB*ltd[2];
		}
		// right-hand part
		btScalar lostop = getLowerLinLimit();
		btScalar histop = getUpperLinLimit();
		if(limit && (lostop == histop))
		{  // the joint motor is ineffective
			powered = 0;
		}
		info->m_constraintError[srow] = 0.;
		info->m_lowerLimit[srow] = 0.;
		info->m_upperLimit[srow] = 0.;
		currERP = (m_flags & BT_SLIDER_FLAGS_ERP_LIMLIN) ? m_softnessLimLin : info->erp;
		if(powered)
		{
			if(m_flags & BT_SLIDER_FLAGS_CFM_DIRLIN)
			{
				info->cfm[srow] = m_cfmDirLin;
			}
			btScalar tag_vel = getTargetLinMotorVelocity();
			btScalar mot_fact = getMotorFactor(m_linPos, m_lowerLinLimit, m_upperLinLimit, tag_vel, info->fps * currERP);
			info->m_constraintError[srow] -= signFact * mot_fact * getTargetLinMotorVelocity();
			info->m_lowerLimit[srow] += -getMaxLinMotorForce() * info->fps;
			info->m_upperLimit[srow] += getMaxLinMotorForce() * info->fps;
		}
		if(limit)
		{
			k = info->fps * currERP;
			info->m_constraintError[srow] += k * limit_err;
			if(m_flags & BT_SLIDER_FLAGS_CFM_LIMLIN)
			{
				info->cfm[srow] = m_cfmLimLin;
			}
			if(lostop == histop) 
			{	// limited low and high simultaneously
				info->m_lowerLimit[srow] = -SIMD_INFINITY;
				info->m_upperLimit[srow] = SIMD_INFINITY;
			}
			else if(limit == 1) 
			{ // low limit
				info->m_lowerLimit[srow] = -SIMD_INFINITY;
				info->m_upperLimit[srow] = 0;
			}
			else 
			{ // high limit
				info->m_lowerLimit[srow] = 0;
				info->m_upperLimit[srow] = SIMD_INFINITY;
			}
			// bounce (we'll use slider parameter abs(1.0 - m_dampingLimLin) for that)
			btScalar bounce = btFabs(btScalar(1.0) - getDampingLimLin());
			if(bounce > btScalar(0.0))
			{
				btScalar vel = linVelA.dot(ax1);
				vel -= linVelB.dot(ax1);
				vel *= signFact;
				// only apply bounce if the velocity is incoming, and if the
				// resulting c[] exceeds what we already have.
				if(limit == 1)
				{	// low limit
					if(vel < 0)
					{
						btScalar newc = -bounce * vel;
						if (newc > info->m_constraintError[srow])
						{
							info->m_constraintError[srow] = newc;
						}
					}
				}
				else
				{ // high limit - all those computations are reversed
					if(vel > 0)
					{
						btScalar newc = -bounce * vel;
						if(newc < info->m_constraintError[srow]) 
						{
							info->m_constraintError[srow] = newc;
						}
					}
				}
			}
			info->m_constraintError[srow] *= getSoftnessLimLin();
		} // if(limit)
	} // if linear limit
	// check angular limits
	limit_err = btScalar(0.0);
	limit = 0;
	if(getSolveAngLimit())
	{
		limit_err = getAngDepth();
		limit = (limit_err > btScalar(0.0)) ? 1 : 2;
	}
	// if the slider has joint limits, add in the extra row
	powered = 0;
	if(getPoweredAngMotor())
	{
		powered = 1;
	}
	if(limit || powered) 
	{
		nrow++;
		srow = nrow * info->rowskip;
		info->m_J1angularAxis[srow+0] = ax1[0];
		info->m_J1angularAxis[srow+1] = ax1[1];
		info->m_J1angularAxis[srow+2] = ax1[2];

		info->m_J2angularAxis[srow+0] = -ax1[0];
		info->m_J2angularAxis[srow+1] = -ax1[1];
		info->m_J2angularAxis[srow+2] = -ax1[2];

		btScalar lostop = getLowerAngLimit();
		btScalar histop = getUpperAngLimit();
		if(limit && (lostop == histop))
		{  // the joint motor is ineffective
			powered = 0;
		}
		currERP = (m_flags & BT_SLIDER_FLAGS_ERP_LIMANG) ? m_softnessLimAng : info->erp;
		if(powered)
		{
			if(m_flags & BT_SLIDER_FLAGS_CFM_DIRANG)
			{
				info->cfm[srow] = m_cfmDirAng;
			}
			btScalar mot_fact = getMotorFactor(m_angPos, m_lowerAngLimit, m_upperAngLimit, getTargetAngMotorVelocity(), info->fps * currERP);
			info->m_constraintError[srow] = mot_fact * getTargetAngMotorVelocity();
			info->m_lowerLimit[srow] = -getMaxAngMotorForce() * info->fps;
			info->m_upperLimit[srow] = getMaxAngMotorForce() * info->fps;
		}
		if(limit)
		{
			k = info->fps * currERP;
			info->m_constraintError[srow] += k * limit_err;
			if(m_flags & BT_SLIDER_FLAGS_CFM_LIMANG)
			{
				info->cfm[srow] = m_cfmLimAng;
			}
			if(lostop == histop) 
			{
				// limited low and high simultaneously
				info->m_lowerLimit[srow] = -SIMD_INFINITY;
				info->m_upperLimit[srow] = SIMD_INFINITY;
			}
			else if(limit == 1) 
			{ // low limit
				info->m_lowerLimit[srow] = 0;
				info->m_upperLimit[srow] = SIMD_INFINITY;
			}
			else 
			{ // high limit
				info->m_lowerLimit[srow] = -SIMD_INFINITY;
				info->m_upperLimit[srow] = 0;
			}
			// bounce (we'll use slider parameter abs(1.0 - m_dampingLimAng) for that)
			btScalar bounce = btFabs(btScalar(1.0) - getDampingLimAng());
			if(bounce > btScalar(0.0))
			{
				btScalar vel = m_rbA.getAngularVelocity().dot(ax1);
				vel -= m_rbB.getAngularVelocity().dot(ax1);
				// only apply bounce if the velocity is incoming, and if the
				// resulting c[] exceeds what we already have.
				if(limit == 1)
				{	// low limit
					if(vel < 0)
					{
						btScalar newc = -bounce * vel;
						if(newc > info->m_constraintError[srow])
						{
							info->m_constraintError[srow] = newc;
						}
					}
				}
				else
				{	// high limit - all those computations are reversed
					if(vel > 0)
					{
						btScalar newc = -bounce * vel;
						if(newc < info->m_constraintError[srow])
						{
							info->m_constraintError[srow] = newc;
						}
					}
				}
			}
			info->m_constraintError[srow] *= getSoftnessLimAng();
		} // if(limit)
	} // if angular limit or powered
}