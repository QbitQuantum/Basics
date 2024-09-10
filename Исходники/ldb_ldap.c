/* return false if the request is still in progress
 * return true if the request is completed
 */
static bool lldb_parse_result(struct lldb_context *ac, LDAPMessage *result)
{
	struct ldb_context *ldb;
	struct lldb_private *lldb = ac->lldb;
	LDAPControl **serverctrlsp = NULL;
	char **referralsp = NULL;
	char *matcheddnp = NULL;
	char *errmsgp = NULL;
	LDAPMessage *msg;
	int type;
	struct ldb_message *ldbmsg;
	char *referral;
	bool callback_failed;
	bool request_done;
	bool lret;
	unsigned int i;
	int ret;

	ldb = ldb_module_get_ctx(ac->module);

	type = ldap_msgtype(result);
	callback_failed = false;
	request_done = false;

	switch (type) {
	case LDAP_RES_SEARCH_ENTRY:

		msg = ldap_first_entry(lldb->ldap, result);
	       	if (msg != NULL) {
			BerElement *berptr = NULL;
			char *attr, *dn;

			ldbmsg = ldb_msg_new(ac);
			if (!ldbmsg) {
				ldb_oom(ldb);
				ret = LDB_ERR_OPERATIONS_ERROR;
				break;
			}

			dn = ldap_get_dn(lldb->ldap, msg);
			if (!dn) {
				ldb_oom(ldb);
				talloc_free(ldbmsg);
				ret = LDB_ERR_OPERATIONS_ERROR;
				break;
			}
			ldbmsg->dn = ldb_dn_new(ldbmsg, ldb, dn);
			if ( ! ldb_dn_validate(ldbmsg->dn)) {
				ldb_asprintf_errstring(ldb, "Invalid DN '%s' in reply", dn);
				talloc_free(ldbmsg);
				ret = LDB_ERR_OPERATIONS_ERROR;
				ldap_memfree(dn);
				break;
			}
			ldap_memfree(dn);

			ldbmsg->num_elements = 0;
			ldbmsg->elements = NULL;

			/* loop over all attributes */
			for (attr=ldap_first_attribute(lldb->ldap, msg, &berptr);
			     attr;
			     attr=ldap_next_attribute(lldb->ldap, msg, berptr)) {
				struct berval **bval;
				bval = ldap_get_values_len(lldb->ldap, msg, attr);

				if (bval) {
					lldb_add_msg_attr(ldb, ldbmsg, attr, bval);
					ldap_value_free_len(bval);
				}
			}
			if (berptr) ber_free(berptr, 0);

			ret = ldb_module_send_entry(ac->req, ldbmsg, NULL /* controls not yet supported */);
			if (ret != LDB_SUCCESS) {
				ldb_asprintf_errstring(ldb, "entry send failed: %s",
						       ldb_errstring(ldb));
				callback_failed = true;
			}
		} else {
			ret = LDB_ERR_OPERATIONS_ERROR;
		}
		break;

	case LDAP_RES_SEARCH_REFERENCE:

		ret = ldap_parse_reference(lldb->ldap, result,
					   &referralsp, &serverctrlsp, 0);
		if (ret != LDAP_SUCCESS) {
			ldb_asprintf_errstring(ldb, "ldap reference parse error: %s : %s",
					       ldap_err2string(ret), errmsgp);
			ret = LDB_ERR_OPERATIONS_ERROR;
			break;
		}
		if (referralsp == NULL) {
			ldb_asprintf_errstring(ldb, "empty ldap referrals list");
			ret = LDB_ERR_PROTOCOL_ERROR;
			break;
		}

		for (i = 0; referralsp[i]; i++) {
			referral = talloc_strdup(ac, referralsp[i]);

			ret = ldb_module_send_referral(ac->req, referral);
			if (ret != LDB_SUCCESS) {
				ldb_asprintf_errstring(ldb, "referral send failed: %s",
						       ldb_errstring(ldb));
				callback_failed = true;
				break;
			}
		}
		break;

	case LDAP_RES_SEARCH_RESULT:
	case LDAP_RES_MODIFY:
	case LDAP_RES_ADD:
	case LDAP_RES_DELETE:
	case LDAP_RES_MODDN:

		if (ldap_parse_result(lldb->ldap, result, &ret,
					&matcheddnp, &errmsgp,
					&referralsp, &serverctrlsp, 0) != LDAP_SUCCESS) {
			ret = LDB_ERR_OPERATIONS_ERROR;
		}
		if (ret != LDB_SUCCESS) {
			ldb_asprintf_errstring(ldb, "ldap parse error for type %d: %s : %s",
					       type, ldap_err2string(ret), errmsgp);
			break;
		}

		if (serverctrlsp != NULL) {
			/* FIXME: transform the LDAPControl list into an ldb_control one */
			ac->controls = NULL;
		}

		request_done = true;
		break;

	default:
		ldb_asprintf_errstring(ldb, "unknown ldap return type: %d", type);
		ret = LDB_ERR_PROTOCOL_ERROR;
		break;
	}

	if (ret != LDB_SUCCESS) {

		/* if the callback failed the caller will have freed the
		 * request. Just return and don't try to use it */
		if (callback_failed) {

			/* tell lldb_wait to remove the request from the
			 *  queue */
			lret = true;
			goto free_and_return;
		}

		request_done = true;
	}

	if (request_done) {
		lldb_request_done(ac, ac->controls, ret);
		lret = true;
		goto free_and_return;
	}

	lret = false;

free_and_return:

	if (matcheddnp) ldap_memfree(matcheddnp);
	if (errmsgp && *errmsgp) {
		ldb_set_errstring(ldb, errmsgp);
	}
	if (errmsgp) {
		ldap_memfree(errmsgp);
	}
	if (referralsp) ldap_value_free(referralsp);
	if (serverctrlsp) ldap_controls_free(serverctrlsp);

	ldap_msgfree(result);

	return lret;
}