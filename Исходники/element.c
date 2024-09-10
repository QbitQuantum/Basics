/**
 * \brief Add new IPFIX element to a proper group
 *
 * Find a group of elements with same Enteprise ID and insert new element inside
 * it. If Enterprise group does not exists, it will create new one.
 * \warning Dupliticity of elements is not check. Groups must be sorted before
 * next usage for searching for elements.
 * \param[in,out] groups Structure with groups of IPFIX elements.
 * \param[in] elem New IPFIX element
 * \return O on success. Otherwise returns non-zero value.
 */
static int elem_add_element(struct elem_groups* groups, ipfix_element_t *elem)
{
	struct elem_en_group *key_ptr, *en_group = NULL;
	struct elem_en_group **aux_ptr;
	
	struct elem_en_group key;
	key.en_id = elem->en;
	key_ptr = &key;
	
	// Find the group with same Enterprise ID
	aux_ptr = bsearch(&key_ptr, groups->groups, groups->elem_used,
		sizeof(struct elem_en_group *), cmp_groups);
	if (aux_ptr) {
		en_group = *aux_ptr;
	}
	
	if (!en_group) {
		// Group not found -> create new one
		if (groups->elem_used == groups->elem_max) {
			// Array is full -> realloc
			struct elem_en_group **new_ptr;
			new_ptr = (struct elem_en_group **) realloc(groups->groups,
				2 * groups->elem_max * sizeof(struct elem_en_group *));
			if (!new_ptr) {
				MSG_ERROR(msg_module, "REALLOC FAILED! (%s:%d)", __FILE__,
					__LINE__);
				return 1;
			}
			
			groups->elem_max *= 2;
			groups->groups = new_ptr;
		}
		
		en_group = (struct elem_en_group *) calloc(1, sizeof(struct elem_en_group));
		if (!en_group) {
			MSG_ERROR(msg_module, "CALLOC FAILED! (%s:%d)", __FILE__, __LINE__);
			return 1;
		}
		
		en_group->en_id = elem->en;
		groups->groups[groups->elem_used++] = en_group;
		
		// We use binary search for searching for groups -> sort
		qsort(groups->groups, groups->elem_used, sizeof(struct elem_en_group *),
			cmp_groups);
	}

	// Add element to the group
	if (en_group->elem_used == en_group->elem_max) {
		// Array is empty or full -> realloc
		size_t new_size = (en_group->elem_max == 0)
			? ELEM_DEF_COUNT : (2 * en_group->elem_max);
		
		ipfix_element_t **new_ptr;
		new_ptr = (ipfix_element_t **) realloc(en_group->elements,
			new_size * sizeof(ipfix_element_t *));
		if (!new_ptr) {
			MSG_ERROR(msg_module, "CALLOC FAILED! (%s:%d)", __FILE__, __LINE__);
			return 1;
		}
		
		en_group->elements = new_ptr;
		en_group->elem_max = new_size;
	}
	
	// Success
	en_group->elements[en_group->elem_used++] = elem;
	return 0;
}