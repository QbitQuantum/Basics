int YARPOutputSocketDgram::Prepare (const YARPUniqueNameID& name)
{
	OSDataDgram& d = OSDATA(system_resources);

	/// local_port might not be needed by the socket layer.
	char buf[YARP_STRING_LEN];
	getHostname (buf, YARP_STRING_LEN);
	d._local_addr.set ((u_short)0, buf);
	d._remote_addr = ((YARPUniqueNameSock&)name).getAddressRef();

	int r = d._connector_socket.open (d._local_addr, ACE_PROTOCOL_FAMILY_INET, 0, 1);
	if (r < 0)
	{
		identifier = ACE_INVALID_HANDLE;
		return YARP_FAIL;
	}

	r = YARPNetworkObject::setSocketBufSize (d._connector_socket, MAX_PACKET);
	if (r < 0)
	{
		d._connector_socket.close();
		ACE_DEBUG ((LM_DEBUG, "cannot set buffer size to %d\n", MAX_PACKET));
		return YARP_FAIL;
	}

	identifier = d._connector_socket.get_handle();

	return YARP_OK;
}