int ld_cmd_exec(db_res_t* res, db_cmd_t* cmd)
{
	db_con_t* con;
	struct ld_res* lres;
	struct ld_cmd* lcmd;
	struct ld_con* lcon;
	char* filter, *err_desc;
	int ret, err;
	LDAPMessage *msg, *resmsg;
	int reconn_cnt;
	int msgid;
	char *oid;
	struct berval *data;
	struct timeval restimeout;

	filter = NULL;
	err_desc = NULL;
	resmsg = NULL;

	/* First things first: retrieve connection info from the currently active
	 * connection and also mysql payload from the database command
	 */
	con = cmd->ctx->con[db_payload_idx];
	lcmd = DB_GET_PAYLOAD(cmd);
	lcon = DB_GET_PAYLOAD(con);
	
	reconn_cnt = ld_reconnect_attempt;

	if (ld_prepare_ldap_filter(&filter, cmd, &lcmd->filter) < 0) {
		ERR("ldap: Error while building LDAP search filter\n");
		goto error;
	}

	DBG("ldap: ldap_search(base:'%s', filter:'%s')\n", lcmd->base, filter);
	do {
		if (lcon->flags & LD_CONNECTED) {
			ldap_set_option(lcon->con, LDAP_OPT_DEREF, ((void *)&lcmd->chase_references));
			/* there is alternative method using LDAP_CONTROL_REFERRALS per request but is not well documented */
			ldap_set_option(lcon->con, LDAP_OPT_REFERRALS, lcmd->chase_referrals?LDAP_OPT_ON:LDAP_OPT_OFF);
		
			ret = ldap_search_ext(lcon->con, lcmd->base, lcmd->scope, filter,
								  lcmd->result, 0, NULL, NULL,
								  lcmd->timelimit.tv_sec ? &lcmd->timelimit : NULL,
								  lcmd->sizelimit,
								  &msgid);
			if (ret != LDAP_SUCCESS) {
				ERR("ldap: Error while searching: %s\n", ldap_err2string(ret));
				goto error;
			}

			/*
			 openldap v2.3 library workaround for unsolicited messages:
			 if only unsolicited messages are available then ldap_result of
			 v2.3 library waits forever
			*/
			memset(&restimeout, 0, sizeof(restimeout));
			restimeout.tv_sec = 5;
			ret = ldap_result(lcon->con,
							  LDAP_RES_ANY,
							  LDAP_MSG_ALL,
							  &restimeout,
							  &resmsg);
		} else {
			/* force it to reconnect */
			ret = -1;
		}

		if (ret <= 0) {
			ERR("ldap: Error in ldap_search: %s\n", ret < 0 ? ldap_err2string(ret) : "timeout");
			if (ret == LDAP_SERVER_DOWN) {
				lcon->flags &= ~LD_CONNECTED;
				do {
					if (!reconn_cnt) {
						ERR("ldap: maximum reconnection attempt reached! giving up\n");
						goto error;
					}
					reconn_cnt--;
					err = ld_con_connect(con);
				} while (err != 0);
			} else {
				goto error;
			}
		}
	} while (ret <= 0);

	/* looking for unsolicited messages */
	for (msg = ldap_first_message(lcon->con, resmsg);
		 msg != NULL;
		 msg = ldap_next_message(lcon->con, msg)) {
		if (ldap_msgtype(msg) == LDAP_RES_EXTENDED) {
			if (ldap_parse_extended_result(lcon->con,
										   msg,
										   &oid,
										   &data,
										   0) != LDAP_SUCCESS) {
				ERR("ldap: Error while parsing extended result\n");
 				goto error;
			}
			if (oid != NULL) {
				if (strcmp(oid, LDAP_NOTICE_OF_DISCONNECTION) == 0) {
					WARN("ldap: Notice of Disconnection (OID: %s)\n", oid);
				} else {
					WARN("ldap: Unsolicited message received. OID: %s\n", oid);
				}
				ldap_memfree(oid);
			}
			if (data != NULL) {
				WARN("ldap: Unsolicited message data: %.*s\n",
					 (int)data->bv_len, data->bv_val);
				ber_bvfree(data);
			}
		}
	}

	ret = ldap_parse_result(lcon->con, resmsg, &err, NULL, &err_desc, NULL, NULL, 0);
	if (ret != LDAP_SUCCESS) {
		ERR("ldap: Error while reading result status: %s\n",
			ldap_err2string(ret));
		goto error;
	}

	if (err != LDAP_SUCCESS) {
		ERR("ldap: LDAP server reports error: %s\n", ldap_err2string(err));
		goto error;
	}

	if (res) {
		lres = DB_GET_PAYLOAD(res);
		lres->msg = resmsg;
	} else if (resmsg) {
		ldap_msgfree(resmsg);
	}

	if (filter) pkg_free(filter);
	if (err_desc) ldap_memfree(err_desc);
	return 0;

 error:
	if (filter) pkg_free(filter);
	if (resmsg) ldap_msgfree(resmsg);
	if (err_desc) ldap_memfree(err_desc);
	return -1;
}