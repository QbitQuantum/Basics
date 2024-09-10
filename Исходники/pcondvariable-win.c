static pboolean
pp_cond_variable_init_xp (PCondVariable *cond)
{
	PCondVariableXP *cv_xp;

	if ((cond->cv = p_malloc0 (sizeof (PCondVariableXP))) == NULL) {
		P_ERROR ("PCondVariable::pp_cond_variable_init_xp: failed to allocate memory (internal)");
		return FALSE;
	}

	cv_xp = ((PCondVariableXP *) cond->cv);

	cv_xp->waiters_count = 0;
	cv_xp->waiters_sema  = CreateSemaphoreA (NULL, 0, MAXLONG, NULL);

	if (P_UNLIKELY (cv_xp->waiters_sema == NULL)) {
		P_ERROR ("PCondVariable::pp_cond_variable_init_xp: failed to initialize semaphore");
		p_free (cond->cv);
		cond->cv = NULL;
		return FALSE;
	}

	return TRUE;
}