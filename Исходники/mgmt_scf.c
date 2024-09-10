/*
 * mgmt_get_main_config() loads main configuration
 * from scf into a node tree.
 * Main configuration includes: admin/target/tpgt/initiator info.
 * admin info is stored in "iscsitgt" property group
 * target info is stored in "target_<name>" property group
 * initiator info is stored in "initiator_<name>" property group
 * tpgt info is stored in "tpgt_<number>" property group
 */
Boolean_t
mgmt_get_main_config(tgt_node_t **node)
{
	targ_scf_t *h = NULL;
	scf_property_t *prop = NULL;
	scf_value_t *value = NULL;
	scf_iter_t *iter = NULL;
	scf_iter_t *iter_v = NULL;
	scf_iter_t *iter_pv = NULL;
	char *pname = NULL;
	char *valuebuf = NULL;
	ssize_t max_name_len;
	ssize_t max_value_len;
	char passcode[32];
	unsigned int outlen;
	tgt_node_t	*n;
	tgt_node_t	*pn;
	tgt_node_t	*vn;
	Boolean_t	status = False;

	h = mgmt_handle_init();

	if (h == NULL)
		return (status);

	prop = scf_property_create(h->t_handle);
	value = scf_value_create(h->t_handle);
	iter = scf_iter_create(h->t_handle);

	if ((alloc_scf_name(&max_name_len, (void *)&pname) == False) ||
	    (alloc_scf_value(&max_value_len, (void *)&valuebuf) == False)) {
		goto error;
	}

	(void) pthread_mutex_lock(&scf_conf_mutex);

	/* Basic Information is stored in iscsitgt pg */
	if (scf_service_get_pg(h->t_service, "iscsitgt", h->t_pg) == -1) {
		goto error;
	}

	*node = NULL;
	*node = tgt_node_alloc("main_config", String, NULL);
	if (*node == NULL)
		goto error;

	if (scf_iter_pg_properties(iter, h->t_pg) == -1) {
		goto error;
	}

	while (scf_iter_next_property(iter, prop) > 0) {
		(void) scf_property_get_value(prop, value);
		(void) scf_value_get_as_string(value, valuebuf, max_value_len);
		(void) scf_property_get_name(prop, pname, max_name_len);

		/* avoid load auth to incore data */
		if (strcmp(pname, ISCSI_READ_AUTHNAME) == 0 ||
		    strcmp(pname, ISCSI_MODIFY_AUTHNAME) == 0 ||
		    strcmp(pname, ISCSI_VALUE_AUTHNAME) == 0)
			continue;

		n = tgt_node_alloc(pname, String, valuebuf);
		if (n == NULL)
			goto error;

		/* put version info into root node's attr */
		if (strcmp(pname, XML_ELEMENT_VERS) == 0) {
			tgt_node_add_attr(*node, n);
		} else {
		/* add other basic info into root node */
			tgt_node_add(*node, n);
		}
	}

	/*
	 * targets/initiators/tpgt information is
	 * stored as type "configuration" in scf
	 * each target's param is stored as type "parameter"
	 */
	if (scf_iter_service_pgs_typed(iter, h->t_service, "configuration")
	    == -1) {
		goto error;
	}

	while (scf_iter_next_pg(iter, h->t_pg) > 0) {
		char *iname;

		(void) scf_pg_get_name(h->t_pg, pname, max_name_len);
		pgname_decode(pname);
		iname = strchr(pname, '_');
		if (iname == NULL) {
			/* the pg found here is not a tgt/initiator/tpgt */
			continue;
		}
		*iname = '\0';
		iname++;
		/*
		 * now pname is "target" or "initiator" or "tpgt"
		 * meanwhile iname is the actual name of the item
		 */

		n = tgt_node_alloc(pname, String, iname);
		if (n == NULL)
			goto error;

		iter_v = scf_iter_create(h->t_handle);
		if (scf_iter_pg_properties(iter_v, h->t_pg) == -1) {
			goto error;
		}
		while (scf_iter_next_property(iter_v, prop) > 0) {
			/* there may be many values in one property */
			char *vname;

			(void) scf_property_get_name(prop, pname,
			    max_name_len);
			/* avoid load auth to incore data */
			if (strcmp(pname, ISCSI_READ_AUTHNAME) == 0 ||
			    strcmp(pname, ISCSI_MODIFY_AUTHNAME) == 0 ||
			    strcmp(pname, ISCSI_VALUE_AUTHNAME) == 0)
				continue;

			vname = strstr(pname, "-list");
			if (vname == NULL) {
				(void) scf_property_get_value(prop, value);
				(void) scf_value_get_as_string(value, valuebuf,
				    max_value_len);

				pn = tgt_node_alloc(pname, String, valuebuf);
				if (pn == NULL)
					goto error;
				tgt_node_add(n, pn);
			} else {
				pn = tgt_node_alloc(pname, String, NULL);
				if (pn == NULL)
					goto error;
				tgt_node_add(n, pn);
				*vname = '\0';

				iter_pv = scf_iter_create(h->t_handle);
				(void) scf_iter_property_values(iter_pv, prop);
				while (scf_iter_next_value(iter_pv, value)
				    > 0) {
					(void) scf_value_get_as_string(
					    value, valuebuf, max_value_len);
					/*
					 * map 'acl' to 'initiator' since that
					 * is what used inside the acl-list.
					 */
					if (strcmp(pname, XML_ELEMENT_ACL)
					    == 0) {
						vn = tgt_node_alloc(
						    XML_ELEMENT_INIT,
						    String, valuebuf);
					} else {
						vn = tgt_node_alloc(
						    pname, String, valuebuf);
					}
					if (vn == NULL)
						goto error;
					tgt_node_add(pn, vn);
				}
				scf_iter_destroy(iter_pv);
				iter_pv = NULL;
			}
		}
		tgt_node_add(*node, n);
		scf_iter_destroy(iter_v);
		iter_v = NULL;
	}

	/* chap-secrets are stored in "passwords" pgroup as "application" */
	if (scf_service_get_pg(h->t_service, "passwords", h->t_pg) == 0) {
		if (scf_iter_pg_properties(iter, h->t_pg) == -1) {
			goto error;
		}

		while (scf_iter_next_property(iter, prop) > 0) {
			(void) scf_property_get_value(prop, value);
			(void) scf_value_get_as_string(value, valuebuf,
			    max_value_len);
			(void) scf_property_get_name(prop, pname,
			    max_name_len);

			/* avoid load auth to incore data */
			if (strcmp(pname, ISCSI_READ_AUTHNAME) == 0 ||
			    strcmp(pname, ISCSI_MODIFY_AUTHNAME) == 0 ||
			    strcmp(pname, ISCSI_VALUE_AUTHNAME) == 0)
				continue;

			/* max length of decoded passwd is 16B */
			(void) sasl_decode64(valuebuf, strlen(valuebuf),
			    passcode, sizeof (passcode), &outlen);

			if (strcmp(pname, "radius") == 0) {
				pn = tgt_node_alloc(XML_ELEMENT_RAD_SECRET,
				    String, passcode);
				tgt_node_add(*node, pn);
			} else if (strcmp(pname, "main") == 0) {
				pn = tgt_node_alloc(XML_ELEMENT_CHAPSECRET,
				    String, passcode);
				tgt_node_add(*node, pn);
			} else {
				/* find corresponding initiator */
				n = NULL;
				while (n = tgt_node_next_child(*node,
				    XML_ELEMENT_INIT, n)) {
					if (strcmp(pname + 2, n->x_value) != 0)
						continue;
					pn = tgt_node_alloc(
					    XML_ELEMENT_CHAPSECRET,
					    String, passcode);
					tgt_node_add(n, pn);
				}
			}
		}
	}

	status = True;
error:
	if ((status != True) && (*node != NULL))
		tgt_node_free(*node);
	(void) pthread_mutex_unlock(&scf_conf_mutex);
	if (iter_pv != NULL)
		scf_iter_destroy(iter_pv);
	if (iter_v != NULL)
		scf_iter_destroy(iter_v);

	free(valuebuf);
	free(pname);

	scf_iter_destroy(iter);
	scf_value_destroy(value);
	scf_property_destroy(prop);
	mgmt_handle_fini(h);
	return (status);
}