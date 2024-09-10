bool KX_ObjectActuator::Update()
{
	
	bool bNegativeEvent = IsNegativeEvent();
	RemoveAllEvents();
		
	KX_GameObject *parent = static_cast<KX_GameObject *>(GetParent()); 
	PHY_ICharacter *character = parent->GetScene()->GetPhysicsEnvironment()->GetCharacterController(parent);

	if (bNegativeEvent) {
		// If we previously set the linear velocity we now have to inform
		// the physics controller that we no longer wish to apply it and that
		// it should reconcile the externally set velocity with it's 
		// own velocity.
		if (m_active_combined_velocity) {
			if (parent)
				parent->ResolveCombinedVelocities(
						m_linear_velocity,
						m_angular_velocity,
						(m_bitLocalFlag.LinearVelocity) != 0,
						(m_bitLocalFlag.AngularVelocity) != 0
					);
			m_active_combined_velocity = false;
		}

		// Explicitly stop the movement if we're using character motion
		if (m_bitLocalFlag.CharacterMotion) {
			character->SetWalkDirection(MT_Vector3 (0.0f, 0.0f, 0.0f));
		}

		m_linear_damping_active = false;
		m_angular_damping_active = false;
		m_error_accumulator.setValue(0.0f,0.0f,0.0f);
		m_previous_error.setValue(0.0f,0.0f,0.0f);
		m_jumping = false;
		return false; 

	} else if (parent)
	{
		if (m_bitLocalFlag.ServoControl) 
		{
			// In this mode, we try to reach a target speed using force
			// As we don't know the friction, we must implement a generic 
			// servo control to achieve the speed in a configurable
			// v = current velocity
			// V = target velocity
			// e = V-v = speed error
			// dt = time interval since previous update
			// I = sum(e(t)*dt)
			// dv = e(t) - e(t-1)
			// KP, KD, KI : coefficient
			// F = KP*e+KI*I+KD*dv
			MT_Scalar mass = parent->GetMass();
			if (mass < MT_EPSILON)
				return false;
			MT_Vector3 v = parent->GetLinearVelocity(m_bitLocalFlag.LinearVelocity);
			if (m_reference)
			{
				const MT_Point3& mypos = parent->NodeGetWorldPosition();
				const MT_Point3& refpos = m_reference->NodeGetWorldPosition();
				MT_Point3 relpos;
				relpos = (mypos-refpos);
				MT_Vector3 vel= m_reference->GetVelocity(relpos);
				if (m_bitLocalFlag.LinearVelocity)
					// must convert in local space
					vel = parent->NodeGetWorldOrientation().transposed()*vel;
				v -= vel;
			}
			MT_Vector3 e = m_linear_velocity - v;
			MT_Vector3 dv = e - m_previous_error;
			MT_Vector3 I = m_error_accumulator + e;

			m_force = m_pid.x()*e+m_pid.y()*I+m_pid.z()*dv;
			// to automatically adapt the PID coefficient to mass;
			m_force *= mass;
			if (m_bitLocalFlag.Torque) 
			{
				if (m_force[0] > m_dloc[0])
				{
					m_force[0] = m_dloc[0];
					I[0] = m_error_accumulator[0];
				} else if (m_force[0] < m_drot[0])
				{
					m_force[0] = m_drot[0];
					I[0] = m_error_accumulator[0];
				}
			}
			if (m_bitLocalFlag.DLoc) 
			{
				if (m_force[1] > m_dloc[1])
				{
					m_force[1] = m_dloc[1];
					I[1] = m_error_accumulator[1];
				} else if (m_force[1] < m_drot[1])
				{
					m_force[1] = m_drot[1];
					I[1] = m_error_accumulator[1];
				}
			}
			if (m_bitLocalFlag.DRot) 
			{
				if (m_force[2] > m_dloc[2])
				{
					m_force[2] = m_dloc[2];
					I[2] = m_error_accumulator[2];
				} else if (m_force[2] < m_drot[2])
				{
					m_force[2] = m_drot[2];
					I[2] = m_error_accumulator[2];
				}
			}
			m_previous_error = e;
			m_error_accumulator = I;
			parent->ApplyForce(m_force,(m_bitLocalFlag.LinearVelocity) != 0);
		}
		else if (m_bitLocalFlag.CharacterMotion) {
			MT_Vector3 dir = m_dloc;

			if (m_bitLocalFlag.DLoc) {
				MT_Matrix3x3 basis = parent->GetPhysicsController()->GetOrientation();
				dir = basis * dir;
			}

			if (m_bitLocalFlag.AddOrSetCharLoc) {
				MT_Vector3 old_dir = character->GetWalkDirection();

				if (!old_dir.fuzzyZero()) {
					MT_Scalar mag = old_dir.length();

					dir = dir + old_dir;
					if (!dir.fuzzyZero())
						dir = dir.normalized() * mag;
				}
			}

			// We always want to set the walk direction since a walk direction of (0, 0, 0) should stop the character
			character->SetWalkDirection(dir/parent->GetScene()->GetPhysicsEnvironment()->GetNumTimeSubSteps());

			if (!m_bitLocalFlag.ZeroDRot)
			{
				parent->ApplyRotation(m_drot,(m_bitLocalFlag.DRot) != 0);
			}

			if (m_bitLocalFlag.CharacterJump) {
				if (!m_jumping) {
					character->Jump();
					m_jumping = true;
				}
				else if (character->OnGround())
					m_jumping = false;
			}
		}
		else {
			if (!m_bitLocalFlag.ZeroForce)
			{
				parent->ApplyForce(m_force,(m_bitLocalFlag.Force) != 0);
			}
			if (!m_bitLocalFlag.ZeroTorque)
			{
				parent->ApplyTorque(m_torque,(m_bitLocalFlag.Torque) != 0);
			}
			if (!m_bitLocalFlag.ZeroDLoc)
			{
				parent->ApplyMovement(m_dloc,(m_bitLocalFlag.DLoc) != 0);
			}
			if (!m_bitLocalFlag.ZeroDRot)
			{
				parent->ApplyRotation(m_drot,(m_bitLocalFlag.DRot) != 0);
			}

			if (m_bitLocalFlag.ZeroLinearVelocity) {
				if (!m_bitLocalFlag.AddOrSetLinV) {
					/* No need to select local or world, as the velocity is zero anyway,
					 * and setLinearVelocity() converts local to world first. We do need to
					 * pass a true zero vector, as m_linear_velocity is only fuzzily zero. */
					parent->setLinearVelocity(MT_Vector3(0, 0, 0), false);
				}
			}
			else {
				if (m_bitLocalFlag.AddOrSetLinV) {
					parent->addLinearVelocity(m_linear_velocity,(m_bitLocalFlag.LinearVelocity) != 0);
				} else {
					m_active_combined_velocity = true;
					if (m_damping > 0) {
						MT_Vector3 linV;
						if (!m_linear_damping_active) {
							// delta and the start speed (depends on the existing speed in that direction)
							linV = parent->GetLinearVelocity(m_bitLocalFlag.LinearVelocity);
							// keep only the projection along the desired direction
							m_current_linear_factor = linV.dot(m_linear_velocity)/m_linear_length2;
							m_linear_damping_active = true;
						}
						if (m_current_linear_factor < 1.0f)
							m_current_linear_factor += 1.0f/m_damping;
						if (m_current_linear_factor > 1.0f)
							m_current_linear_factor = 1.0f;
						linV = m_current_linear_factor * m_linear_velocity;
						parent->setLinearVelocity(linV,(m_bitLocalFlag.LinearVelocity) != 0);
					} else {
						parent->setLinearVelocity(m_linear_velocity,(m_bitLocalFlag.LinearVelocity) != 0);
					}
				}
			}
			if (m_bitLocalFlag.ZeroAngularVelocity) {
				/* No need to select local or world, as the velocity is zero anyway,
				 * and setAngularVelocity() converts local to world first. We do need to
				 * pass a true zero vector, as m_angular_velocity is only fuzzily zero. */
				parent->setAngularVelocity(MT_Vector3(0, 0, 0), false);
			}
			else {
				m_active_combined_velocity = true;
				if (m_damping > 0) {
					MT_Vector3 angV;
					if (!m_angular_damping_active) {
						// delta and the start speed (depends on the existing speed in that direction)
						angV = parent->GetAngularVelocity(m_bitLocalFlag.AngularVelocity);
						// keep only the projection along the desired direction
						m_current_angular_factor = angV.dot(m_angular_velocity)/m_angular_length2;
						m_angular_damping_active = true;
					}
					if (m_current_angular_factor < 1.0f)
						m_current_angular_factor += 1.0f/m_damping;
					if (m_current_angular_factor > 1.0f)
						m_current_angular_factor = 1.0f;
					angV = m_current_angular_factor * m_angular_velocity;
					parent->setAngularVelocity(angV,(m_bitLocalFlag.AngularVelocity) != 0);
				} else {
					parent->setAngularVelocity(m_angular_velocity,(m_bitLocalFlag.AngularVelocity) != 0);
				}
			}
		}
		
	}
	return true;
}