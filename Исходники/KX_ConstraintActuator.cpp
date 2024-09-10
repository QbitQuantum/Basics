bool KX_ConstraintActuator::Update(double curtime, bool frame)
{

	bool result = false;
	bool bNegativeEvent = IsNegativeEvent();
	RemoveAllEvents();

	if (!bNegativeEvent) {
		/* Constraint clamps the values to the specified range, with a sort of    */
		/* low-pass filtered time response, if the damp time is unequal to 0.     */

		/* Having to retrieve location/rotation and setting it afterwards may not */
		/* be efficient enough... Something to look at later.                     */
		KX_GameObject  *obj = (KX_GameObject*) GetParent();
		MT_Vector3    position = obj->NodeGetWorldPosition();
		MT_Vector3    newposition;
		MT_Vector3   normal, direction, refDirection;
		MT_Matrix3x3 rotation = obj->NodeGetWorldOrientation();
		MT_Scalar    filter, newdistance, cosangle;
		int axis, sign;

		if (m_posDampTime) {
			filter = m_posDampTime/(1.0f+m_posDampTime);
		} else {
			filter = 0.0f;
		}
		switch (m_locrot) {
		case KX_ACT_CONSTRAINT_ORIX:
		case KX_ACT_CONSTRAINT_ORIY:
		case KX_ACT_CONSTRAINT_ORIZ:
			switch (m_locrot) {
			case KX_ACT_CONSTRAINT_ORIX:
				direction[0] = rotation[0][0];
				direction[1] = rotation[1][0];
				direction[2] = rotation[2][0];
				axis = 0;
				break;
			case KX_ACT_CONSTRAINT_ORIY:
				direction[0] = rotation[0][1];
				direction[1] = rotation[1][1];
				direction[2] = rotation[2][1];
				axis = 1;
				break;
			default:
				direction[0] = rotation[0][2];
				direction[1] = rotation[1][2];
				direction[2] = rotation[2][2];
				axis = 2;
				break;
			}
			if ((m_maximumBound < (1.0f-FLT_EPSILON)) || (m_minimumBound < (1.0f-FLT_EPSILON))) {
				// reference direction needs to be evaluated
				// 1. get the cosine between current direction and target
				cosangle = direction.dot(m_refDirVector);
				if (cosangle >= (m_maximumBound-FLT_EPSILON) && cosangle <= (m_minimumBound+FLT_EPSILON)) {
					// no change to do
					result = true;
					goto CHECK_TIME;
				}
				// 2. define a new reference direction
				//    compute local axis with reference direction as X and
				//    Y in direction X refDirection plane
				MT_Vector3 zaxis = m_refDirVector.cross(direction);
				if (MT_fuzzyZero2(zaxis.length2())) {
					// direction and refDirection are identical,
					// choose any other direction to define plane
					if (direction[0] < 0.9999f)
						zaxis = m_refDirVector.cross(MT_Vector3(1.0f,0.0f,0.0f));
					else
						zaxis = m_refDirVector.cross(MT_Vector3(0.0f,1.0f,0.0f));
				}
				MT_Vector3 yaxis = zaxis.cross(m_refDirVector);
				yaxis.normalize();
				if (cosangle > m_minimumBound) {
					// angle is too close to reference direction,
					// choose a new reference that is exactly at minimum angle
					refDirection = m_minimumBound * m_refDirVector + m_minimumSine * yaxis;
				} else {
					// angle is too large, choose new reference direction at maximum angle
					refDirection = m_maximumBound * m_refDirVector + m_maximumSine * yaxis;
				}
			} else {
				refDirection = m_refDirVector;
			}
			// apply damping on the direction
			direction = filter*direction + (1.0f-filter)*refDirection;
			obj->AlignAxisToVect(direction, axis);
			result = true;
			goto CHECK_TIME;
		case KX_ACT_CONSTRAINT_DIRPX:
		case KX_ACT_CONSTRAINT_DIRPY:
		case KX_ACT_CONSTRAINT_DIRPZ:
		case KX_ACT_CONSTRAINT_DIRNX:
		case KX_ACT_CONSTRAINT_DIRNY:
		case KX_ACT_CONSTRAINT_DIRNZ:
			switch (m_locrot) {
			case KX_ACT_CONSTRAINT_DIRPX:
				normal[0] = rotation[0][0];
				normal[1] = rotation[1][0];
				normal[2] = rotation[2][0];
				axis = 0;		// axis according to KX_GameObject::AlignAxisToVect()
				sign = 0;		// X axis will be parrallel to direction of ray
				break;
			case KX_ACT_CONSTRAINT_DIRPY:
				normal[0] = rotation[0][1];
				normal[1] = rotation[1][1];
				normal[2] = rotation[2][1];
				axis = 1;
				sign = 0;
				break;
			case KX_ACT_CONSTRAINT_DIRPZ:
				normal[0] = rotation[0][2];
				normal[1] = rotation[1][2];
				normal[2] = rotation[2][2];
				axis = 2;
				sign = 0;
				break;
			case KX_ACT_CONSTRAINT_DIRNX:
				normal[0] = -rotation[0][0];
				normal[1] = -rotation[1][0];
				normal[2] = -rotation[2][0];
				axis = 0;
				sign = 1;
				break;
			case KX_ACT_CONSTRAINT_DIRNY:
				normal[0] = -rotation[0][1];
				normal[1] = -rotation[1][1];
				normal[2] = -rotation[2][1];
				axis = 1;
				sign = 1;
				break;
			case KX_ACT_CONSTRAINT_DIRNZ:
				normal[0] = -rotation[0][2];
				normal[1] = -rotation[1][2];
				normal[2] = -rotation[2][2];
				axis = 2;
				sign = 1;
				break;
			}
			normal.normalize();
			if (m_option & KX_ACT_CONSTRAINT_LOCAL) {
				// direction of the ray is along the local axis
				direction = normal;
			} else {
				switch (m_locrot) {
				case KX_ACT_CONSTRAINT_DIRPX:
					direction = MT_Vector3(1.0f,0.0f,0.0f);
					break;
				case KX_ACT_CONSTRAINT_DIRPY:
					direction = MT_Vector3(0.0f,1.0f,0.0f);
					break;
				case KX_ACT_CONSTRAINT_DIRPZ:
					direction = MT_Vector3(0.0f,0.0f,1.0f);
					break;
				case KX_ACT_CONSTRAINT_DIRNX:
					direction = MT_Vector3(-1.0f,0.0f,0.0f);
					break;
				case KX_ACT_CONSTRAINT_DIRNY:
					direction = MT_Vector3(0.0f,-1.0f,0.0f);
					break;
				case KX_ACT_CONSTRAINT_DIRNZ:
					direction = MT_Vector3(0.0f,0.0f,-1.0f);
					break;
				}
			}
			{
				MT_Vector3 topoint = position + (m_maximumBound) * direction;
				PHY_IPhysicsEnvironment* pe = KX_GetActiveScene()->GetPhysicsEnvironment();
				PHY_IPhysicsController *spc = obj->GetPhysicsController();

				if (!pe) {
					CM_LogicBrickWarning(this, "there is no physics environment!");
					goto CHECK_TIME;
				}	 
				if (!spc) {
					// the object is not physical, we probably want to avoid hitting its own parent
					KX_GameObject *parent = obj->GetParent();
					if (parent) {
						spc = parent->GetPhysicsController();
					}
				}
				KX_RayCast::Callback<KX_ConstraintActuator, void> callback(this,dynamic_cast<PHY_IPhysicsController*>(spc));
				result = KX_RayCast::RayTest(pe, position, topoint, callback);
				if (result)	{
					MT_Vector3 newnormal = callback.m_hitNormal;
					// compute new position & orientation
					if ((m_option & (KX_ACT_CONSTRAINT_NORMAL|KX_ACT_CONSTRAINT_DISTANCE)) == 0) {
						// if none option is set, the actuator does nothing but detect ray 
						// (works like a sensor)
						goto CHECK_TIME;
					}
					if (m_option & KX_ACT_CONSTRAINT_NORMAL) {
						MT_Scalar rotFilter;
						// apply damping on the direction
						if (m_rotDampTime) {
							rotFilter = m_rotDampTime/(1.0f+m_rotDampTime);
						} else {
							rotFilter = filter;
						}
						newnormal = rotFilter*normal - (1.0f-rotFilter)*newnormal;
						obj->AlignAxisToVect((sign)?-newnormal:newnormal, axis);
						if (m_option & KX_ACT_CONSTRAINT_LOCAL) {
							direction = newnormal;
							direction.normalize();
						}
					}
					if (m_option & KX_ACT_CONSTRAINT_DISTANCE) {
						if (m_posDampTime) {
							newdistance = filter*(position-callback.m_hitPoint).length()+(1.0f-filter)*m_minimumBound;
						} else {
							newdistance = m_minimumBound;
						}
						// logically we should cancel the speed along the ray direction as we set the
						// position along that axis
						spc = obj->GetPhysicsController();
						if (spc && spc->IsDynamic()) {
							MT_Vector3 linV = spc->GetLinearVelocity();
							// cancel the projection along the ray direction
							MT_Scalar fallspeed = linV.dot(direction);
							if (!MT_fuzzyZero(fallspeed))
								spc->SetLinearVelocity(linV-fallspeed*direction,false);
						}
					} else {
						newdistance = (position-callback.m_hitPoint).length();
					}
					newposition = callback.m_hitPoint-newdistance*direction;
				} else if (m_option & KX_ACT_CONSTRAINT_PERMANENT) {
					// no contact but still keep running
					result = true;
					goto CHECK_TIME;
				}
			}
			break; 
		case KX_ACT_CONSTRAINT_FHPX:
		case KX_ACT_CONSTRAINT_FHPY:
		case KX_ACT_CONSTRAINT_FHPZ:
		case KX_ACT_CONSTRAINT_FHNX:
		case KX_ACT_CONSTRAINT_FHNY:
		case KX_ACT_CONSTRAINT_FHNZ:
			switch (m_locrot) {
			case KX_ACT_CONSTRAINT_FHPX:
				normal[0] = -rotation[0][0];
				normal[1] = -rotation[1][0];
				normal[2] = -rotation[2][0];
				direction = MT_Vector3(1.0f,0.0f,0.0f);
				break;
			case KX_ACT_CONSTRAINT_FHPY:
				normal[0] = -rotation[0][1];
				normal[1] = -rotation[1][1];
				normal[2] = -rotation[2][1];
				direction = MT_Vector3(0.0f,1.0f,0.0f);
				break;
			case KX_ACT_CONSTRAINT_FHPZ:
				normal[0] = -rotation[0][2];
				normal[1] = -rotation[1][2];
				normal[2] = -rotation[2][2];
				direction = MT_Vector3(0.0f,0.0f,1.0f);
				break;
			case KX_ACT_CONSTRAINT_FHNX:
				normal[0] = rotation[0][0];
				normal[1] = rotation[1][0];
				normal[2] = rotation[2][0];
				direction = MT_Vector3(-1.0f,0.0f,0.0f);
				break;
			case KX_ACT_CONSTRAINT_FHNY:
				normal[0] = rotation[0][1];
				normal[1] = rotation[1][1];
				normal[2] = rotation[2][1];
				direction = MT_Vector3(0.0f,-1.0f,0.0f);
				break;
			case KX_ACT_CONSTRAINT_FHNZ:
				normal[0] = rotation[0][2];
				normal[1] = rotation[1][2];
				normal[2] = rotation[2][2];
				direction = MT_Vector3(0.0f,0.0f,-1.0f);
				break;
			}
			normal.normalize();
			{
				PHY_IPhysicsEnvironment* pe = KX_GetActiveScene()->GetPhysicsEnvironment();
				PHY_IPhysicsController *spc = obj->GetPhysicsController();

				if (!pe) {
					CM_LogicBrickWarning(this, "there is no physics environment!");
					goto CHECK_TIME;
				}	 
				if (!spc || !spc->IsDynamic()) {
					// the object is not dynamic, it won't support setting speed
					goto CHECK_TIME;
				}
				m_hitObject = NULL;
				// distance of Fh area is stored in m_minimum
				MT_Vector3 topoint = position + (m_minimumBound+spc->GetRadius()) * direction;
				KX_RayCast::Callback<KX_ConstraintActuator, void> callback(this, spc);
				result = KX_RayCast::RayTest(pe, position, topoint, callback);
				// we expect a hit object
				if (!m_hitObject)
					result = false;
				if (result)
				{
					MT_Vector3 newnormal = callback.m_hitNormal;
					// compute new position & orientation
					MT_Scalar distance = (callback.m_hitPoint-position).length()-spc->GetRadius(); 
					// estimate the velocity of the hit point
					MT_Vector3 relativeHitPoint;
					relativeHitPoint = (callback.m_hitPoint-m_hitObject->NodeGetWorldPosition());
					MT_Vector3 velocityHitPoint = m_hitObject->GetVelocity(relativeHitPoint);
					MT_Vector3 relativeVelocity = spc->GetLinearVelocity() - velocityHitPoint;
					MT_Scalar relativeVelocityRay = direction.dot(relativeVelocity);
					MT_Scalar springExtent = 1.0f - distance/m_minimumBound;
					// Fh force is stored in m_maximum
					MT_Scalar springForce = springExtent * m_maximumBound;
					// damping is stored in m_refDirection [0] = damping, [1] = rot damping
					MT_Scalar springDamp = relativeVelocityRay * m_refDirVector[0];
					MT_Vector3 newVelocity = spc->GetLinearVelocity()-(springForce+springDamp)*direction;
					if (m_option & KX_ACT_CONSTRAINT_NORMAL)
					{
						newVelocity+=(springForce+springDamp)*(newnormal-newnormal.dot(direction)*direction);
					}
					spc->SetLinearVelocity(newVelocity, false);
					if (m_option & KX_ACT_CONSTRAINT_DOROTFH)
					{
						MT_Vector3 angSpring = (normal.cross(newnormal))*m_maximumBound;
						MT_Vector3 angVelocity = spc->GetAngularVelocity();
						// remove component that is parallel to normal
						angVelocity -= angVelocity.dot(newnormal)*newnormal;
						MT_Vector3 angDamp = angVelocity * ((m_refDirVector[1]>MT_EPSILON)?m_refDirVector[1]:m_refDirVector[0]);
						spc->SetAngularVelocity(spc->GetAngularVelocity()+(angSpring-angDamp), false);
					}
				} else if (m_option & KX_ACT_CONSTRAINT_PERMANENT) {
					// no contact but still keep running
					result = true;
				}
				// don't set the position with this constraint
				goto CHECK_TIME;
			}
			break; 
		case KX_ACT_CONSTRAINT_LOCX:
		case KX_ACT_CONSTRAINT_LOCY:
		case KX_ACT_CONSTRAINT_LOCZ:
			newposition = position = obj->GetSGNode()->GetLocalPosition();
			switch (m_locrot) {
			case KX_ACT_CONSTRAINT_LOCX:
				Clamp(newposition[0], m_minimumBound, m_maximumBound);
				break;
			case KX_ACT_CONSTRAINT_LOCY:
				Clamp(newposition[1], m_minimumBound, m_maximumBound);
				break;
			case KX_ACT_CONSTRAINT_LOCZ:
				Clamp(newposition[2], m_minimumBound, m_maximumBound);
				break;
			}
			result = true;
			if (m_posDampTime) {
				newposition = filter*position + (1.0f-filter)*newposition;
			}
			obj->NodeSetLocalPosition(newposition);
			goto CHECK_TIME;
		}
		if (result) {
			// set the new position but take into account parent if any
			obj->NodeSetWorldPosition(newposition);
		}
	CHECK_TIME:
		if (result && m_activeTime > 0 ) {
			if (++m_currentTime >= m_activeTime)
				result = false;
		}
	}
	if (!result) {
		m_currentTime = 0;
	}
	return result;
} /* end of KX_ConstraintActuator::Update(double curtime,double deltatime)   */