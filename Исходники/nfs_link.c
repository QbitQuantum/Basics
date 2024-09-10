int main(int argc, char *argv[])
{
	struct addrinfo *srv_addr, hints;
	int err;
	enum clnt_stat stat;
	nfs_ctx *ctx = NULL;

	LOOKUP3args largs;
	LINK3args lnk;

	if(argc < 5) {
		fprintf(stderr, "Not enough arguments\nThis tests the asynchronous "
				"libnfsclient NFS LINK call interface and "
				" callback\n"
				"USAGE: nfs_link <server> <remote_file_dir> "
				"<linkname> <target>\n");
		return 0;
	}

	/* First resolve server name */
	hints.ai_family = AF_INET;
	hints.ai_protocol = 0;
	hints.ai_socktype = 0;
	hints.ai_flags = 0;

	fprintf(stdout, "Resolving name %s\n", argv[1]);
	if((err = getaddrinfo(argv[1], NULL, &hints, &srv_addr)) != 0) {
		fprintf(stderr, "%s: Cannot resolve name: %s: %s\n",
				argv[0], argv[1], gai_strerror(err));
		return -1;
	}
	
	fprintf(stdout, "Creating nfs client context..\n");
	ctx = nfs_init((struct sockaddr_in *)srv_addr->ai_addr, IPPROTO_TCP, 0);
	if(ctx == NULL) {
		fprintf(stderr, "%s: Cant init nfs context\n", argv[0]);
		return 0;
	}

	freeaddrinfo(srv_addr);
	mntfh.fhandle3_len = 0;
	fprintf(stdout, "Sending mount call\n");
	stat = mount3_mnt(&argv[2], ctx, nfs_mnt_cb, NULL);
	if(stat == RPC_SUCCESS)
		fprintf(stderr, "NFS MOUNT Call sent successfully\n");
	else {
		fprintf(stderr, "Could not send NFS MOUNT call\n");
		return 0;
	}

	largs.what.dir.data.data_len = mntfh.fhandle3_len;
	largs.what.dir.data.data_val = mntfh.fhandle3_val;
	largs.what.name = argv[4];

	lfh.fhandle3_len = 0;
	fprintf(stdout, "Sending lookup call..\n");
	stat = nfs3_lookup(&largs, ctx, nfs_lookup_cb, NULL);
	if(stat == RPC_SUCCESS)
		fprintf(stderr, "NFS LOOKUP Call sent successfully\n");
	else {
		fprintf(stderr, "Could not send NFS LOOKUP call\n");
		return 0;
	}

	fprintf(stdout, "Waiting for lookup reply..\n");
	nfs_complete(ctx, RPC_BLOCKING_WAIT);

	fprintf(stdout, "Lookup reply received..\n");
	lnk.file.data.data_len = lfh.fhandle3_len;
	lnk.file.data.data_val = lfh.fhandle3_val;
	lnk.link.dir.data.data_len = mntfh.fhandle3_len;
	lnk.link.dir.data.data_val = mntfh.fhandle3_val;
	lnk.link.name = argv[3];
	fprintf(stdout, "Sending link call..\n");
	stat = nfs3_link(&lnk, ctx, nfs_link_cb, NULL);
	if(stat == RPC_SUCCESS)
		fprintf(stderr, "NFS LINK Call sent successfully\n");
	else {
		fprintf(stderr, "Could not send NFS LINK call\n");
		return 0;
	}

	fprintf(stdout, "Waiting for link reply..\n");
	nfs_complete(ctx, RPC_BLOCKING_WAIT);

	fprintf(stdout, "Received link reply..\n");
	free_LOOKUP3res(lookupres);
	
	return 0;
}