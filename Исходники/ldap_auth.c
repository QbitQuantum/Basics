/*******************************************************************************
 函数名称  : dot1x_ldap_search_dn_timeout
 功能描述  : LDAP_SEARCH_DN状态查询用户DN
 输入参数  : user_data   ---   定时器参数，sm状态机
 输出参数  : 无
 返 回 值     : 无
------------------------------------------------------------
 最近一次修改记录 :
 修改作者   : 王群
 修改目的   : 新增函数
 修改日期   : 2011年6月2日
*******************************************************************************/
void dot1x_ldap_search_dn_timeout(void *user_data)
{
	s8 filter[1024];
	s32 retcode;
	s8 *userdn = NULL;
	LDAPMessage *res = NULL;
	LDAPMessage *msg = NULL;
	struct eapol_state_machine *sm = (struct eapol_state_machine *)user_data;

	snprintf(filter, sizeof(filter), "(%s=%s)", g_dot1x_var.ldap_conf.ldap_filter, sm->identity);
	/*执行查询操作*/
	retcode = ldap_search_s(sm->ldap_sm->ldap, g_dot1x_var.ldap_conf.ldap_basedn, LDAP_SCOPE_SUBTREE, filter, g_ldap_attrs, 0, &res);
	(sm->ldap_sm->req_count)++;
	if (LDAP_SUCCESS == retcode)
	{
		msg = ldap_first_entry(sm->ldap_sm->ldap, res);
		if (NULL == msg)
		{
			ldap_msgfree(res);
			return;
		}

		/*获得用户的dn*/
		userdn = ldap_get_dn(sm->ldap_sm->ldap, msg);
		if (NULL == userdn)
		{
			ldap_msgfree(res);
			return;
		}
		sm->ldap_sm->userdn = userdn;
		/*查询成功，进入LDAP_BIND_DN状态*/
		dot1x_ldap_bind_dn_entry(sm);
	}
	else if (LDAP_TIMEOUT == retcode &&
			sm->ldap_sm->req_count < g_dot1x_var.conf.retransmit_times)
	{
		/*重载定时器*/
		dloop_register_timeout(0, 0, dot1x_ldap_search_dn_timeout, sm);
	}
	else
	{
		/*关闭连接*/
		ldap_unbind(sm->ldap_sm->ldap);
		/*查询失败，进入LDAP_FAILURE状态*/
		dot1x_ldap_failure_entry(sm);
	}

	ldap_msgfree(res);
	return;
}