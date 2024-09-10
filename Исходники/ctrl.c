void ctrl_clear_lyst(Lyst *list, ResourceLock *mutex, int destroy)
{
	LystElt elt;
	ctrl_exec_t *entry = NULL;

	AMP_DEBUG_ENTRY("ctrl_clear_lyst","(0x%x, 0x%x, %d)",
			          (unsigned long) list, (unsigned long) mutex, destroy);

    if((list == NULL) || (*list == NULL))
    {
    	AMP_DEBUG_ERR("ctrl_clear_lyst","Bad Params.", NULL);
    	return;
    }

	if(mutex != NULL)
	{
		lockResource(mutex);
	}

	/* Free any reports left in the reports list. */
	for (elt = lyst_first(*list); elt; elt = lyst_next(elt))
	{
		/* Grab the current item */
		if((entry = (ctrl_exec_t *) lyst_data(elt)) == NULL)
		{
			AMP_DEBUG_ERR("ctrl_clear_lyst","Can't get report from lyst!", NULL);
		}
		else
		{
			ctrl_release(entry);
		}
	}

	lyst_clear(*list);

	if(destroy != 0)
	{
		lyst_destroy(*list);
		*list = NULL;
	}

	if(mutex != NULL)
	{
		unlockResource(mutex);
	}

	AMP_DEBUG_EXIT("ctrl_clear_lyst","->.",NULL);
}