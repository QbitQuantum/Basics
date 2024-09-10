void CL_ActorStateChange (const eventRegister_t *self, struct dbuffer *msg)
{
	le_t *le;
	int entnum, state;
	character_t *chr;

	NET_ReadFormat(msg, self->formatString, &entnum, &state);

	le = LE_Get(entnum);
	if (!le)
		LE_NotFoundError(entnum);

	if (!LE_IsActor(le)) {
		Com_Printf("StateChange message ignored... LE is no actor (number: %i, state: %i, type: %i)\n",
			entnum, state, le->type);
		return;
	}

	/* If standing up or crouching down remove the reserved-state for crouching. */
	if (((state & STATE_CROUCHED) && !LE_IsCrouched(le)) ||
		 (!(state & STATE_CROUCHED) && LE_IsCrouched(le))) {
		if (CL_ActorUsableTUs(le) < TU_CROUCH && CL_ActorReservedTUs(le, RES_CROUCH) >= TU_CROUCH) {
			/* We have not enough non-reserved TUs,
			 * but some reserved for crouching/standing up.
			 * i.e. we only reset the reservation for crouching if it's the very last attempt. */
			CL_ActorReserveTUs(le, RES_CROUCH, 0); /* Reset reserved TUs (0 TUs) */
		}
	}

	/* killed by the server: no animation is played, etc. */
	if ((state & STATE_DEAD) && LE_IsLivingActor(le)) {
		le->state = state;
		FLOOR(le) = NULL;
		LE_SetThink(le, NULL);
		VectorCopy(player_dead_maxs, le->maxs);
		CL_ActorRemoveFromTeamList(le);
		return;
	} else {
		le->state = state;
		LE_SetThink(le, LET_StartIdle);
	}

	/* save those states that the actor should also carry over to other missions */
	chr = CL_ActorGetChr(le);
	if (!chr)
		return;

	chr->state = (le->state & STATE_REACTION);

	/* change reaction button state */
	if (!(le->state & STATE_REACTION)) {
		UI_ExecuteConfunc("disable_reaction");
	} else {
		UI_ExecuteConfunc("startreaction");
	}

	/* state change may have affected move length */
	CL_ActorConditionalMoveCalc(le);
}