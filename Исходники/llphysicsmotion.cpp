// Return TRUE if character has to update visual params.
BOOL LLPhysicsMotion::onUpdate(F32 time)
{
        // static FILE *mFileWrite = fopen("c:\\temp\\avatar_data.txt","w");
        
        if (!mParamDriver)
                return FALSE;

        if (!mLastTime)
        {
                mLastTime = time;
                return FALSE;
        }

        ////////////////////////////////////////////////////////////////////////////////
        // Get all parameters and settings
        //

        const F32 time_delta = time - mLastTime;

	// Don't update too frequently, to avoid precision errors from small time slices.
	if (time_delta <= .01)
	{
		return FALSE;
	}
	
	// If less than 1FPS, we don't want to be spending time updating physics at all.
        if (time_delta > 1.0)
        {
                mLastTime = time;
                return FALSE;
        }

        // Higher LOD is better.  This controls the granularity
        // and frequency of updates for the motions.
        const F32 lod_factor = LLVOAvatar::sPhysicsLODFactor;
        if (lod_factor == 0)
        {
                return TRUE;
        }

        LLJoint *joint = mJointState->getJoint();

        const F32 behavior_mass = getParamValue("Mass");
        const F32 behavior_gravity = getParamValue("Gravity");
        const F32 behavior_spring = getParamValue("Spring");
        const F32 behavior_gain = getParamValue("Gain");
        const F32 behavior_damping = getParamValue("Damping");
        const F32 behavior_drag = getParamValue("Drag");
        const BOOL physics_test = FALSE; // Enable this to simulate bouncing on all parts.
        
        F32 behavior_maxeffect = getParamValue("MaxEffect");
        if (physics_test)
                behavior_maxeffect = 1.0f;

	// Normalize the param position to be from [0,1].
	// We have to use normalized values because there may be more than one driven param,
	// and each of these driven params may have its own range.
	// This means we'll do all our calculations in normalized [0,1] local coordinates.
	const F32 position_user_local = (mParamDriver->getWeight() - mParamDriver->getMinWeight()) / (mParamDriver->getMaxWeight() - mParamDriver->getMinWeight());
       	
	//
	// End parameters and settings
	////////////////////////////////////////////////////////////////////////////////
	
	
	////////////////////////////////////////////////////////////////////////////////
	// Calculate velocity and acceleration in parameter space.
	//
        
	//const F32 velocity_joint_local = calculateVelocity_local(time_iteration_step);
	const F32 velocity_joint_local = calculateVelocity_local();
	const F32 acceleration_joint_local = calculateAcceleration_local(velocity_joint_local);
	
	//
	// End velocity and acceleration
	////////////////////////////////////////////////////////////////////////////////
	
	BOOL update_visuals = FALSE;
	
	// Break up the physics into a bunch of iterations so that differing framerates will show
	// roughly the same behavior.
	for (F32 time_iteration = 0; time_iteration <= time_delta; time_iteration += TIME_ITERATION_STEP)
	{
		F32 time_iteration_step = TIME_ITERATION_STEP;
		if (time_iteration + TIME_ITERATION_STEP > time_delta)
		{
			time_iteration_step = time_delta-time_iteration;
		}
		
		// mPositon_local should be in normalized 0,1 range already.  Just making sure...
		const F32 position_current_local = llclamp(mPosition_local,
							   0.0f,
							   1.0f);
		// If the effect is turned off then don't process unless we need one more update
		// to set the position to the default (i.e. user) position.
		if ((behavior_maxeffect == 0) && (position_current_local == position_user_local))
		{
			return update_visuals;
		}

		////////////////////////////////////////////////////////////////////////////////
		// Calculate the total force 
		//

		// Spring force is a restoring force towards the original user-set breast position.
		// F = kx
		const F32 spring_length = position_current_local - position_user_local;
		const F32 force_spring = -spring_length * behavior_spring;

		// Acceleration is the force that comes from the change in velocity of the torso.
		// F = ma
		const F32 force_accel = behavior_gain * (acceleration_joint_local * behavior_mass);

		// Gravity always points downward in world space.
		// F = mg
		const LLVector3 gravity_world(0,0,1);
		const F32 force_gravity = (toLocal(gravity_world) * behavior_gravity * behavior_mass);
                
		// Damping is a restoring force that opposes the current velocity.
		// F = -kv
		const F32 force_damping = -behavior_damping * mVelocity_local;
                
		// Drag is a force imparted by velocity (intuitively it is similar to wind resistance)
		// F = .5kv^2
		const F32 force_drag = .5*behavior_drag*velocity_joint_local*velocity_joint_local*llsgn(velocity_joint_local);

		const F32 force_net = (force_accel + 
				       force_gravity +
				       force_spring + 
				       force_damping + 
				       force_drag);

		//
		// End total force
		////////////////////////////////////////////////////////////////////////////////

        
		////////////////////////////////////////////////////////////////////////////////
		// Calculate new params
		//

		// Calculate the new acceleration based on the net force.
		// a = F/m
		const F32 acceleration_new_local = force_net / behavior_mass;
		static const F32 max_velocity = 100.0f; // magic number, used to be customizable.
		F32 velocity_new_local = mVelocity_local + acceleration_new_local*time_iteration_step;
		velocity_new_local = llclamp(velocity_new_local, 
					     -max_velocity, max_velocity);
        
		// Temporary debugging setting to cause all avatars to move, for profiling purposes.
		if (physics_test)
		{
			velocity_new_local = sin(time*4.0);
		}
		// Calculate the new parameters, or remain unchanged if max speed is 0.
		F32 position_new_local = position_current_local + velocity_new_local*time_iteration_step;
		if (behavior_maxeffect == 0)
			position_new_local = position_user_local;

		// Zero out the velocity if the param is being pushed beyond its limits.
		if ((position_new_local < 0 && velocity_new_local < 0) || 
		    (position_new_local > 1 && velocity_new_local > 0))
		{
			velocity_new_local = 0;
		}
	
		// Check for NaN values.  A NaN value is detected if the variables doesn't equal itself.  
		// If NaN, then reset everything.
		if ((mPosition_local != mPosition_local) ||
		    (mVelocity_local != mVelocity_local) ||
		    (position_new_local != position_new_local))
		{
			position_new_local = 0;
			mVelocity_local = 0;
			mVelocityJoint_local = 0;
			mAccelerationJoint_local = 0;
			mPosition_local = 0;
			mPosition_world = LLVector3(0,0,0);
		}

		const F32 position_new_local_clamped = llclamp(position_new_local,
							       0.0f,
							       1.0f);

		LLDriverParam *driver_param = dynamic_cast<LLDriverParam *>(mParamDriver);
		llassert_always(driver_param);
		if (driver_param)
		{
			// If this is one of our "hidden" driver params, then make sure it's
			// the default value.
			if ((driver_param->getGroup() != VISUAL_PARAM_GROUP_TWEAKABLE) &&
			    (driver_param->getGroup() != VISUAL_PARAM_GROUP_TWEAKABLE_NO_TRANSMIT))
			{
				mCharacter->setVisualParamWeight(driver_param,
								 0,
								 FALSE);
			}
			for (LLDriverParam::entry_list_t::iterator iter = driver_param->mDriven.begin();
			     iter != driver_param->mDriven.end();
			     ++iter)
			{
				LLDrivenEntry &entry = (*iter);
				LLViewerVisualParam *driven_param = entry.mParam;
				setParamValue(driven_param,position_new_local_clamped, behavior_maxeffect);
			}
		}
        
		//
		// End calculate new params
		////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////
		// Conditionally update the visual params
		//
        
		// Updating the visual params (i.e. what the user sees) is fairly expensive.
		// So only update if the params have changed enough, and also take into account
		// the graphics LOD settings.
        
		// For non-self, if the avatar is small enough visually, then don't update.
		const F32 area_for_max_settings = 0.0;
		const F32 area_for_min_settings = 1400.0;
		const F32 area_for_this_setting = area_for_max_settings + (area_for_min_settings-area_for_max_settings)*(1.0-lod_factor);
		const F32 pixel_area = (F32) sqrt(mCharacter->getPixelArea());
        
		const BOOL is_self = (dynamic_cast<LLVOAvatar *>(mCharacter) != NULL && ((LLVOAvatar*)mCharacter)->isSelf());
		if ((pixel_area > area_for_this_setting) || is_self)
		{
			const F32 position_diff_local = llabs(mPositionLastUpdate_local-position_new_local_clamped);
			const F32 min_delta = (1.0001f-lod_factor)*0.4f;
			if (llabs(position_diff_local) > min_delta)
			{
				update_visuals = TRUE;
				mPositionLastUpdate_local = position_new_local;
			}
		}

		//
		// End update visual params
		////////////////////////////////////////////////////////////////////////////////

		mVelocity_local = velocity_new_local;
		mAccelerationJoint_local = acceleration_joint_local;
		mPosition_local = position_new_local;
	}
	mLastTime = time;
	mPosition_world = joint->getWorldPosition();
	mVelocityJoint_local = velocity_joint_local;


        /*
          // Write out debugging info into a spreadsheet.
          if (mFileWrite != NULL && is_self)
          {
          fprintf(mFileWrite,"%f\t%f\t%f \t\t%f \t\t%f\t%f\t%f\t \t\t%f\t%f\t%f\t%f\t%f \t\t%f\t%f\t%f\n",
          position_new_local,
          velocity_new_local,
          acceleration_new_local,

          time_delta,

          mPosition_world[0],
          mPosition_world[1],
          mPosition_world[2],

          force_net,
          force_spring,
          force_accel,
          force_damping,
          force_drag,

          spring_length,
          velocity_joint_local,
          acceleration_joint_local
          );
          }
        */

        return update_visuals;
}