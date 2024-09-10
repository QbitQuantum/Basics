	void addVertexStates(PotentialVertex *potential, CMSModel3D &input, Vector &vert)
	{
		PotentialVertexState state;
		Vector offset;

		//IN_IN_IN
		if(potential->volumes[IN_IN_IN] != NULL)
		{
			offset =
				(potential->edgeDirections[SET1IN]) +
				(potential->edgeDirections[SET2IN]) +
				(potential->edgeDirections[SET3IN]);
			offset.normalize();
			state.volumes[IN_IN_IN] =
				vertexInsideModel(input, vert + (offset * 0.10f), offset) ? INTERIOR:EXTERIOR;
		}
		else
			state.volumes[IN_IN_IN] = EXTERIOR;
		//IN_IN_OUT
		if(potential->volumes[IN_IN_OUT] != NULL)
		{
			offset =
				(potential->edgeDirections[SET1IN]) +
				(potential->edgeDirections[SET2IN]) +
				(potential->edgeDirections[SET3OUT]);
			offset.normalize();
			state.volumes[IN_IN_OUT] =
				vertexInsideModel(input, vert + (offset * 0.10f), offset) ? INTERIOR:EXTERIOR;
		}
		else
			state.volumes[IN_IN_OUT] = EXTERIOR;
		//IN_OUT_IN
		if(potential->volumes[IN_OUT_IN] != NULL)
		{
			offset =
				(potential->edgeDirections[SET1IN]) +
				(potential->edgeDirections[SET2OUT]) +
				(potential->edgeDirections[SET3IN]);
			offset.normalize();
			state.volumes[IN_OUT_IN] =
				vertexInsideModel(input, vert + (offset * 0.10f), offset) ? INTERIOR:EXTERIOR;
		}
		else
			state.volumes[IN_OUT_IN] = EXTERIOR;
		//IN_OUT_OUT 
		if(potential->volumes[IN_OUT_OUT] != NULL)
		{
			offset =
				(potential->edgeDirections[SET1IN]) +
				(potential->edgeDirections[SET2OUT]) +
				(potential->edgeDirections[SET3OUT]);
			offset.normalize();
			state.volumes[IN_OUT_OUT] =
				vertexInsideModel(input, vert + (offset * 0.10f), offset) ? INTERIOR:EXTERIOR;
		}
		else
			state.volumes[IN_OUT_OUT] = EXTERIOR;
		//OUT_IN_IN
		if(potential->volumes[OUT_IN_IN] != NULL)
		{
			offset =
				(potential->edgeDirections[SET1OUT]) +
				(potential->edgeDirections[SET2IN]) +
				(potential->edgeDirections[SET3IN]);
			offset.normalize();
			state.volumes[OUT_IN_IN] =
				vertexInsideModel(input, vert + (offset * 0.10f), offset) ? INTERIOR:EXTERIOR;
		}
		else
			state.volumes[OUT_IN_IN] = EXTERIOR;
		//OUT_IN_OUT
		if(potential->volumes[OUT_IN_OUT] != NULL)
		{
			offset =
				(potential->edgeDirections[SET1OUT]) +
				(potential->edgeDirections[SET2IN]) +
				(potential->edgeDirections[SET3OUT]);
			offset.normalize();
			state.volumes[OUT_IN_OUT] =
				vertexInsideModel(input, vert + (offset * 0.10f), offset) ? INTERIOR:EXTERIOR;
		}
		else
			state.volumes[OUT_IN_OUT] = EXTERIOR;
		//OUT_OUT_IN
		if(potential->volumes[OUT_OUT_IN] != NULL)
		{
			offset =
				(potential->edgeDirections[SET1OUT]) +
				(potential->edgeDirections[SET2OUT]) +
				(potential->edgeDirections[SET3IN]);
			offset.normalize();
			state.volumes[OUT_OUT_IN] =
				vertexInsideModel(input, vert + (offset * 0.10f), offset) ? INTERIOR:EXTERIOR;
		}
		else
			state.volumes[OUT_OUT_IN] = EXTERIOR;
		//OUT_OUT_OUT
		if(potential->volumes[OUT_OUT_OUT] != NULL)
		{
			offset =
				(potential->edgeDirections[SET1OUT]) +
				(potential->edgeDirections[SET2OUT]) +
				(potential->edgeDirections[SET3OUT]);
			offset.normalize();
			state.volumes[OUT_OUT_OUT] =
				vertexInsideModel(input, vert + (offset * 0.10f), offset) ? INTERIOR:EXTERIOR;
		}
		else
			state.volumes[OUT_OUT_OUT] = EXTERIOR;

		//push state
		potential->states.push_back(state);
	}