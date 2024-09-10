void BL_Action::Update(float curtime, bool applyToObject)
{
	/* Don't bother if we're done with the animation and if the animation was already applied to the object.
	 * of if the animation made a double update for the same time and that it was applied to the object.
	 */
	if ((m_done && m_appliedToObject) || (m_prevUpdate == curtime && m_appliedToObject)) {
		return;
	}
	m_prevUpdate = curtime;

	curtime -= (float)KX_KetsjiEngine::GetSuspendedDelta();

	if (m_calc_localtime)
		SetLocalTime(curtime);
	else
	{
		ResetStartTime(curtime);
		m_calc_localtime = true;
	}

	// Handle wrap around
	if (m_localframe < std::min(m_startframe, m_endframe) || m_localframe > std::max(m_startframe, m_endframe)) {
		switch (m_playmode) {
			case ACT_MODE_PLAY:
				// Clamp
				m_localframe = m_endframe;
				m_done = true;
				break;
			case ACT_MODE_LOOP:
				// Put the time back to the beginning
				m_localframe = m_startframe;
				m_starttime = curtime;
				break;
			case ACT_MODE_PING_PONG:
				// Swap the start and end frames
				float temp = m_startframe;
				m_startframe = m_endframe;
				m_endframe = temp;

				m_starttime = curtime;

				break;
		}
	}

	m_appliedToObject = applyToObject;
	// In case of culled armatures (doesn't requesting to transform the object) we only manages time.
	if (!applyToObject) {
		return;
	}

	if (m_obj->GetGameObjectType() == SCA_IObject::OBJ_ARMATURE)
	{
		BL_ArmatureObject *obj = (BL_ArmatureObject*)m_obj;

		if (m_layer_weight >= 0)
			obj->GetPose(&m_blendpose);

		// Extract the pose from the action
		obj->SetPoseByAction(m_tmpaction, m_localframe);

		// Handle blending between armature actions
		if (m_blendin && m_blendframe<m_blendin)
		{
			IncrementBlending(curtime);

			// Calculate weight
			float weight = 1.f - (m_blendframe/m_blendin);

			// Blend the poses
			obj->BlendInPose(m_blendinpose, weight, ACT_BLEND_BLEND);
		}


		// Handle layer blending
		if (m_layer_weight >= 0)
			obj->BlendInPose(m_blendpose, m_layer_weight, m_blendmode);

		obj->UpdateTimestep(curtime);
	}
	else
	{
		BL_DeformableGameObject *obj = (BL_DeformableGameObject*)m_obj;
		BL_ShapeDeformer *shape_deformer = dynamic_cast<BL_ShapeDeformer*>(obj->GetDeformer());

		// Handle shape actions if we have any
		if (shape_deformer && shape_deformer->GetKey())
		{
			Key *key = shape_deformer->GetKey();

			PointerRNA ptrrna;
			RNA_id_pointer_create(&key->id, &ptrrna);

			animsys_evaluate_action(&ptrrna, m_tmpaction, NULL, m_localframe);

			// Handle blending between shape actions
			if (m_blendin && m_blendframe < m_blendin)
			{
				IncrementBlending(curtime);

				float weight = 1.f - (m_blendframe/m_blendin);

				// We go through and clear out the keyblocks so there isn't any interference
				// from other shape actions
				KeyBlock *kb;
				for (kb=(KeyBlock *)key->block.first; kb; kb=(KeyBlock *)kb->next)
					kb->curval = 0.f;

				// Now blend the shape
				BlendShape(key, weight, m_blendinshape);
			}

			// Handle layer blending
			if (m_layer_weight >= 0)
			{
				obj->GetShape(m_blendshape);
				BlendShape(key, m_layer_weight, m_blendshape);
			}

			obj->SetActiveAction(0, curtime);
		}
	}
}