/**
 * This function searches for a transistor by size
 * - lower: (Return value) The lower-bound matching transistor
 * - upper: (Return value) The upper-bound matching transistor
 * - type: The transistor type to search for
 * - size: The transistor size to search for (size = W/L)
 */
boolean power_find_transistor_info(t_transistor_size_inf ** lower,
		t_transistor_size_inf ** upper, e_tx_type type, float size) {
	char msg[1024];
	t_transistor_size_inf key;
	t_transistor_size_inf * found;
	t_transistor_inf * trans_info;
	float min_size, max_size;
	boolean error = FALSE;

	key.size = size;

	/* Find the appropriate global transistor records */
	if (type == NMOS) {
		trans_info = &g_power_tech->NMOS_inf;
	} else if (type == PMOS) {
		trans_info = &g_power_tech->PMOS_inf;
	} else {
		assert(0);
	}

	/* No transistor data exists */
	if (trans_info->size_inf == NULL) {
		power_log_msg(POWER_LOG_ERROR,
				"No transistor information exists.  Cannot determine transistor properties.");
		error = TRUE;
		return error;
	}

	/* Make note of the transistor record we are searching in, and the bounds */
	g_transistor_last_searched = trans_info;
	min_size = trans_info->size_inf[0].size;
	max_size = trans_info->size_inf[trans_info->num_size_entries - 1].size;

	found = (t_transistor_size_inf*) bsearch(&key, trans_info->size_inf,
			trans_info->num_size_entries, sizeof(t_transistor_size_inf),
			&power_compare_transistor_size);
	assert(found);

	if (size < min_size) {
		/* Too small */
		assert(found == &trans_info->size_inf[0]);
		sprintf(msg,
				"Using %s transistor of size '%f', which is smaller than the smallest modeled transistor (%f) in the technology behavior file.",
				transistor_type_name(type), size, min_size);
		power_log_msg(POWER_LOG_WARNING, msg);
		*lower = NULL;
		*upper = found;
	} else if (size > max_size) {
		/* Too large */
		assert(
				found == &trans_info->size_inf[trans_info->num_size_entries - 1]);
		sprintf(msg,
				"Using %s transistor of size '%f', which is larger than the largest modeled transistor (%f) in the technology behavior file.",
				transistor_type_name(type), size, max_size);
		power_log_msg(POWER_LOG_WARNING, msg);
		*lower = found;
		*upper = NULL;
	} else {
		*lower = found;
		*upper = found + 1;
	}

	return error;
}