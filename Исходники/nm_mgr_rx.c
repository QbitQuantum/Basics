int msg_rx_data_rpt(eid_t *sender_eid, uint8_t *cursor, uint32_t size, uint32_t *bytes_used)
{
    agent_t *agent = NULL;
    int result = -1;

	DTNMP_DEBUG_ENTRY("msg_rx_data_rpt","()",NULL);


	/* Step 0: Sanity Check */
	if((sender_eid == NULL) || (cursor == NULL) || (bytes_used == NULL))
	{
		DTNMP_DEBUG_ERR("msg_rx_data_rpt","Bad Parms", NULL);
		DTNMP_DEBUG_EXIT("msg_rx_data_rpt","-->-1",NULL);
		return -1;
	}

	DTNMP_DEBUG_ALWAYS("msg_rx_data_rpt", "Processing a data report.\n", NULL);
	*bytes_used = 0;

	/* Step 1: Retrieve stored information about this agent. */
	if((agent = mgr_agent_get(sender_eid)) == NULL)
	{
		DTNMP_DEBUG_WARN("msg_rx_data_rpt",
				         "Received group is from an unknown sender (%s); ignoring it.",
				         sender_eid->name);
	}
	else
	{
		rpt_data_t *report = NULL;

		if((report = rpt_deserialize_data(cursor, size, bytes_used)) == NULL)
		{
			DTNMP_DEBUG_ERR("msg_rx_data_rpt","Can't deserialize rpt",NULL);
		}
		else
		{
			/* Step 1.1: Add the report. */
			lockResource(&(agent->mutex));
			lyst_insert_last(agent->reports, report);
			unlockResource(&(agent->mutex));

			result = 0;

			/* Step 1.2: Update statistics. */
			g_reports_total++;
		}
	}

	DTNMP_DEBUG_EXIT("msg_rx_data_rpt","-->%d", result);
	return result;
}