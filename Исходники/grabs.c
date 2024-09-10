Bool
DeletePassiveGrabFromList(GrabPtr pMinuendGrab)
{
    GrabPtr grab;
    GrabPtr *deletes, *adds;
    Mask ***updates, **details;
    int i, ndels, nadds, nups;
    Bool ok;
    unsigned int any_modifier;
    unsigned int any_key;

#define UPDATE(mask,exact) \
	if (!(details[nups] = DeleteDetailFromMask(mask, exact))) \
	  ok = FALSE; \
	else \
	  updates[nups++] = &(mask)

    i = 0;
    for (grab = wPassiveGrabs(pMinuendGrab->window); grab; grab = grab->next)
	i++;
    if (!i)
	return TRUE;
    deletes = malloc(i * sizeof(GrabPtr));
    adds = malloc(i * sizeof(GrabPtr));
    updates = malloc(i * sizeof(Mask **));
    details = malloc(i * sizeof(Mask *));
    if (!deletes || !adds || !updates || !details)
    {
	free(details);
	free(updates);
	free(adds);
	free(deletes);
	return FALSE;
    }

    any_modifier = (pMinuendGrab->grabtype == GRABTYPE_XI2) ?
                   (unsigned int)XIAnyModifier : (unsigned int)AnyModifier;
    any_key = (pMinuendGrab->grabtype == GRABTYPE_XI2) ?
                   (unsigned int)XIAnyKeycode : (unsigned int)AnyKey;
    ndels = nadds = nups = 0;
    ok = TRUE;
    for (grab = wPassiveGrabs(pMinuendGrab->window);
	 grab && ok;
	 grab = grab->next)
    {
	if ((CLIENT_BITS(grab->resource) != CLIENT_BITS(pMinuendGrab->resource)) ||
	    !GrabMatchesSecond(grab, pMinuendGrab,
                               (grab->grabtype == GRABTYPE_CORE)))
	    continue;
	if (GrabSupersedesSecond(pMinuendGrab, grab))
	{
	    deletes[ndels++] = grab;
	}
	else if ((grab->detail.exact == any_key)
		 && (grab->modifiersDetail.exact != any_modifier))
	{
	    UPDATE(grab->detail.pMask, pMinuendGrab->detail.exact);
	}
	else if ((grab->modifiersDetail.exact == any_modifier)
		 && (grab->detail.exact != any_key))
	{
	    UPDATE(grab->modifiersDetail.pMask,
		   pMinuendGrab->modifiersDetail.exact);
	}
	else if ((pMinuendGrab->detail.exact != any_key)
		 && (pMinuendGrab->modifiersDetail.exact != any_modifier))
	{
	    GrabPtr pNewGrab;
            GrabParameters param;

	    UPDATE(grab->detail.pMask, pMinuendGrab->detail.exact);

            memset(&param, 0, sizeof(param));
            param.ownerEvents = grab->ownerEvents;
            param.this_device_mode = grab->keyboardMode;
            param.other_devices_mode = grab->pointerMode;
            param.modifiers = any_modifier;

	    pNewGrab = CreateGrab(CLIENT_ID(grab->resource), grab->device,
				  grab->modifierDevice, grab->window,
                                  grab->grabtype,
				  (GrabMask*)&grab->eventMask,
                                  &param, (int)grab->type,
				  pMinuendGrab->detail.exact,
				  grab->confineTo, grab->cursor);
	    if (!pNewGrab)
		ok = FALSE;
	    else if (!(pNewGrab->modifiersDetail.pMask =
		       DeleteDetailFromMask(grab->modifiersDetail.pMask,
					 pMinuendGrab->modifiersDetail.exact))
		     ||
		     (!pNewGrab->window->optional &&
		      !MakeWindowOptional(pNewGrab->window)))
	    {
		FreeGrab(pNewGrab);
		ok = FALSE;
	    }
	    else if (!AddResource(pNewGrab->resource, RT_PASSIVEGRAB,
				  (pointer)pNewGrab))
		ok = FALSE;
	    else
		adds[nadds++] = pNewGrab;
	}   
	else if (pMinuendGrab->detail.exact == any_key)
	{
	    UPDATE(grab->modifiersDetail.pMask,
		   pMinuendGrab->modifiersDetail.exact);
	}
	else
	{
	    UPDATE(grab->detail.pMask, pMinuendGrab->detail.exact);
	}
    }

    if (!ok)
    {
	for (i = 0; i < nadds; i++)
	    FreeResource(adds[i]->resource, RT_NONE);
	for (i = 0; i < nups; i++)
	    free(details[i]);
    }
    else
    {
	for (i = 0; i < ndels; i++)
	    FreeResource(deletes[i]->resource, RT_NONE);
	for (i = 0; i < nadds; i++)
	{
	    grab = adds[i];
	    grab->next = grab->window->optional->passiveGrabs;
	    grab->window->optional->passiveGrabs = grab;
	}
	for (i = 0; i < nups; i++)
	{
	    free(*updates[i]);
	    *updates[i] = details[i];
	}
    }
    free(details);
    free(updates);
    free(adds);
    free(deletes);
    return ok;

#undef UPDATE
}