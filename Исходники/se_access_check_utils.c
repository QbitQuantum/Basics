SEC_ACL *build_acl(struct ace_entry *ace_list)
{
	SEC_ACE *aces = NULL;
	SEC_ACL *result;
	int num_aces = 0;

	if (ace_list == NULL) return NULL;

	/* Create aces */

	while(ace_list->sid) {
		SEC_ACCESS sa;
		struct dom_sid sid;

		/* Create memory for new ACE */

		if (!(aces = Realloc(aces, 
				     sizeof(SEC_ACE) * (num_aces + 1)))) {
			return NULL;
		}

		/* Create ace */

		init_sec_access(&sa, ace_list->mask);

		char_to_sid(&sid, ace_list->sid);
		init_sec_ace(&aces[num_aces], &sid, ace_list->type,
			     sa, ace_list->flags);

		num_aces++;
		ace_list++;
	}

	/* Create ACL from list of ACEs */

	result = make_sec_acl(ACL_REVISION, num_aces, aces);
	free(aces);

	return result;
}