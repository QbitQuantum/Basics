static int do_notify_leader_changed(ConnectionInfo *pTrackerServer, \
		ConnectionInfo *pLeader, const char cmd, bool *bConnectFail)
{
	char out_buff[sizeof(TrackerHeader) + FDFS_PROTO_IP_PORT_SIZE];
	char in_buff[1];
	ConnectionInfo *conn;
	TrackerHeader *pHeader;
	char *pInBuff;
	int64_t in_bytes;
	int result;

	pTrackerServer->sock = -1;
	if ((conn=tracker_connect_server(pTrackerServer, &result)) == NULL)
	{
		*bConnectFail = true;
		return result;
	}
	*bConnectFail = false;

	do
	{
	memset(out_buff, 0, sizeof(out_buff));
	pHeader = (TrackerHeader *)out_buff;
	pHeader->cmd = cmd;
	sprintf(out_buff + sizeof(TrackerHeader), "%s:%d", \
			pLeader->ip_addr, pLeader->port);
	long2buff(FDFS_PROTO_IP_PORT_SIZE, pHeader->pkg_len);
	if ((result=tcpsenddata_nb(conn->sock, out_buff, \
			sizeof(out_buff), g_fdfs_network_timeout)) != 0)
	{
		logError("file: "__FILE__", line: %d, " \
			"send data to tracker server %s:%d fail, " \
			"errno: %d, error info: %s", __LINE__, \
			pTrackerServer->ip_addr, \
			pTrackerServer->port, \
			result, STRERROR(result));

		result = (result == ENOENT ? EACCES : result);
		break;
	}

	pInBuff = in_buff;
	result = fdfs_recv_response(conn, &pInBuff, \
				0, &in_bytes);
	if (result != 0)
	{
		break;
	}

	if (in_bytes != 0)
	{
		logError("file: "__FILE__", line: %d, " \
			"tracker server %s:%d response data " \
			"length: %"PRId64" is invalid, " \
			"expect length: %d.", __LINE__, \
			pTrackerServer->ip_addr, pTrackerServer->port, \
			in_bytes, 0);
		result = EINVAL;
		break;
	}
	} while (0);

	if (pTrackerServer->port == g_server_port && \
		is_local_host_ip(pTrackerServer->ip_addr))
	{
		tracker_disconnect_server_ex(conn, true);
	}
	else
	{
		tracker_disconnect_server_ex(conn, result != 0);
	}

	return result;
}