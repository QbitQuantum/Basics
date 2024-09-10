void mgr_agent_remove_cb(LystElt elt, void *nil)
{
	eid_t   *agent_eid	= NULL;
	agent_t	*agent		= NULL;
	Object	*entry		= NULL;

	if(elt == NULL)
	{
		DTNMP_DEBUG_ERR("mgr_agent_remove_cb",
				        "Specified Lyst element was null.", NULL);
		DTNMP_DEBUG_EXIT("mgr_agent_remove_cb","", NULL);
		return;
	}

	lockResource(&agents_mutex);

	if((agent = (agent_t *) lyst_data(elt)) == NULL)
	{
		DTNMP_DEBUG_ERR("mgr_agent_remove_cb",
				        "Specified Lyst data was null.", NULL);
	}
	else
	{
		rpt_clear_lyst(&(agent->reports), &(agent->mutex), 1);
		def_lyst_clear(&(agent->custom_defs), &(agent->mutex), 1);

		killResourceLock(&(agent->mutex));
		MRELEASE(agent);
	}

	unlockResource(&agents_mutex);

	DTNMP_DEBUG_EXIT("mgr_agent_remove_cb","", NULL);

	return;
}