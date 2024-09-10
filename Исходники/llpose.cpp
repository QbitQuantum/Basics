//-----------------------------------------------------------------------------
// blendJointStates()
//-----------------------------------------------------------------------------
void LLJointStateBlender::blendJointStates(BOOL apply_now)
{
	// we need at least one joint to blend
	// if there is one, it will be in slot zero according to insertion logic
	// instead of resetting joint state to default, just leave it unchanged from last frame
	if (mJointStates[0].isNull())
	{
		return;
	}

	LLJoint* target_joint = apply_now ? mJointStates[0]->getJoint() : &mJointCache;

	const S32 POS_WEIGHT = 0;
	const S32 ROT_WEIGHT = 1;
	const S32 SCALE_WEIGHT = 2;

	F32				sum_weights[3];
	U32				sum_usage = 0;

	LLVector3		blended_pos = target_joint->getPosition();
	LLQuaternion	blended_rot = target_joint->getRotation();
	LLVector3		blended_scale = target_joint->getScale();

	LLVector3		added_pos;
	LLQuaternion	added_rot;
	LLVector3		added_scale;

	//S32				joint_state_index;

	sum_weights[POS_WEIGHT] = 0.f;
	sum_weights[ROT_WEIGHT] = 0.f;
	sum_weights[SCALE_WEIGHT] = 0.f;

	for(S32 joint_state_index = 0; 
		joint_state_index < JSB_NUM_JOINT_STATES && mJointStates[joint_state_index].notNull();
		joint_state_index++)
	{
		LLJointState* jsp = mJointStates[joint_state_index];
		U32 current_usage = jsp->getUsage();
		F32 current_weight = jsp->getWeight();

		if (current_weight == 0.f)
		{
			continue;
		}

		if (mAdditiveBlends[joint_state_index])
		{
			if(current_usage & LLJointState::POS)
			{
				F32 new_weight_sum = llmin(1.f, current_weight + sum_weights[POS_WEIGHT]);

				// add in pos for this jointstate modulated by weight
				added_pos += jsp->getPosition() * (new_weight_sum - sum_weights[POS_WEIGHT]);
			}

			if(current_usage & LLJointState::SCALE)
			{
				F32 new_weight_sum = llmin(1.f, current_weight + sum_weights[SCALE_WEIGHT]);

				// add in scale for this jointstate modulated by weight
				added_scale += jsp->getScale() * (new_weight_sum - sum_weights[SCALE_WEIGHT]);
			}

			if (current_usage & LLJointState::ROT)
			{
				F32 new_weight_sum = llmin(1.f, current_weight + sum_weights[ROT_WEIGHT]);

				// add in rotation for this jointstate modulated by weight
				added_rot = nlerp((new_weight_sum - sum_weights[ROT_WEIGHT]), added_rot, jsp->getRotation()) * added_rot;
			}
		}
		else
		{
			// blend two jointstates together
		
			// blend position
			if(current_usage & LLJointState::POS)
			{
				if(sum_usage & LLJointState::POS)
				{
					F32 new_weight_sum = llmin(1.f, current_weight + sum_weights[POS_WEIGHT]);

					// blend positions from both
					blended_pos = lerp(jsp->getPosition(), blended_pos, sum_weights[POS_WEIGHT] / new_weight_sum);
					sum_weights[POS_WEIGHT] = new_weight_sum;
				} 
				else
				{
					// copy position from current
					blended_pos = jsp->getPosition();
					sum_weights[POS_WEIGHT] = current_weight;
				}
			}
			
			// now do scale
			if(current_usage & LLJointState::SCALE)
			{
				if(sum_usage & LLJointState::SCALE)
				{
					F32 new_weight_sum = llmin(1.f, current_weight + sum_weights[SCALE_WEIGHT]);

					// blend scales from both
					blended_scale = lerp(jsp->getScale(), blended_scale, sum_weights[SCALE_WEIGHT] / new_weight_sum);
					sum_weights[SCALE_WEIGHT] = new_weight_sum;
				} 
				else
				{
					// copy scale from current
					blended_scale = jsp->getScale();
					sum_weights[SCALE_WEIGHT] = current_weight;
				}
			}

			// rotation
			if (current_usage & LLJointState::ROT)
			{
				if(sum_usage & LLJointState::ROT)
				{
					F32 new_weight_sum = llmin(1.f, current_weight + sum_weights[ROT_WEIGHT]);

					// blend rotations from both
					blended_rot = nlerp(sum_weights[ROT_WEIGHT] / new_weight_sum, jsp->getRotation(), blended_rot);
					sum_weights[ROT_WEIGHT] = new_weight_sum;
				} 
				else
				{
					// copy rotation from current
					blended_rot = jsp->getRotation();
					sum_weights[ROT_WEIGHT] = current_weight;
				}
			}

			// update resulting usage mask
			sum_usage = sum_usage | current_usage;
		}
	}

	if (!added_scale.isFinite())
	{
		added_scale.clearVec();
	}

	if (!blended_scale.isFinite())
	{
		blended_scale.setVec(1,1,1);
	}

	// apply transforms
	target_joint->setPosition(blended_pos + added_pos);
	target_joint->setScale(blended_scale + added_scale);
	target_joint->setRotation(added_rot * blended_rot);

	if (apply_now)
	{
		// now clear joint states
		for(S32 i = 0; i < JSB_NUM_JOINT_STATES; i++)
		{
			mJointStates[i] = NULL;
		}
	}
}