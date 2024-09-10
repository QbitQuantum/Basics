int handle_download(connection *con, uint32_t size, void* data) {
	downloadfilemsg_req *msg = (downloadfilemsg_req *)data;
	
	//cat & validate filename
	char realpath[MAX_STORAGED_PATH_LEN+1];
	assert(NULL != concatpath(realpath, msg->data, msg->filename_len));

	char *err;
        bool r = isvalidfile(&realpath[scontent_len],&err);
	if(!r){
		L_DEBUG("refuse invalid filename");
		return false;
	}

	L_DEBUG("recv download file req %s\n", realpath);
	//get file length
	lockfile(realpath, scontent_len + msg->filename_len);
	int fd = open(realpath ,O_RDONLY);
	int rpdata_len = lseek(fd, 0, SEEK_END);
	//TODO
	assert(rpdata_len >= 0);

	//send res packet
	int rp_size =rpdata_len + downloadfilemsg_res_packetsize;
	packet_header *head = generatebuffer(rp_size, CLIENT_PROTO_RES_DOWNLOAD_FILE);
	//TODO
        assert(NULL != head);
	uploadfilemsg_res *rp = (downloadfilemsg_res *)head->data;
	rp->filename_len = msg->filename_len;
	memcpy(rp->data, msg->data, msg->filename_len);

	int r_len = read(fd, (void *)&rp->data[msg->filename_len], rpdata_len);	
	//TODO
	assert(r_len >= 0);
	close(fd);

	//TODO deal with send result
        sendpacket(con, head);

	unlockfile(realpath, scontent_len + msg->filename_len);
}