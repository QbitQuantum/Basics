int
publish_host_table(void)
{
	List	list = hcp->hrecs;
	host_rec	*item, *hitem;
	char	cmd[RS_LINELEN];
	int		len, flag;
	int		rval;

	NETDEBUG(MRSD, NETLOG_DEBUG2, ("publish_host_table called - printflag = %d\n", hcp->printflag));

	if (!(hcp->printflag))
		return(0);

	snprintf(cmd, RS_LINELEN, "%s rsd clear", RS_CLI_CMD_STR);

//	rval = ExecuteCliCommand(cmd);
//	hcp->printflag = rval;
	rval = System(cmd);
	hcp->printflag = rval;
	NETDEBUG(MRSD, NETLOG_DEBUG2, ("executed - %s, rval =%d\n", cmd, rval));

	for (item = listGetFirstItem(list), hitem = item; item; \
		item = listGetNextItem(list, item)) {
		flag = (memcmp(&(hitem->primary), &(item->host), sizeof(IPADDRESS))==0);
		len = 0;
		//len += snprintf(cmd, RS_LINELEN, "%s rsd add ", RS_CLI_CMD_STR);
		//len += snprintf(cmd, RS_LINELEN, "%d", ntohs(item->port));
		len += snprintf(cmd+len, RS_LINELEN-len, "%s rsd add ", RS_CLI_CMD_STR);
		len += snprintf(cmd+len, RS_LINELEN-len, "%d", (atoi(rs_port)));
		len += snprintf(cmd+len, RS_LINELEN-len, " ");
		FormatIpAddress(ntohl(item->host), cmd+len);
		strcat(cmd+len, flag?" master":" slave");
	//	rval = ExecuteCliCommand(cmd);
	//	hcp->printflag = rval;
		rval = System(cmd);
		hcp->printflag = rval;
		NETDEBUG(MRSD, NETLOG_DEBUG2, ("executed - %s, rval = %d\n", cmd, rval));
	}

	/* We should check the status of all the system() and return an
	   appropriate status */
	return(0);
}