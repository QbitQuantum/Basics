int  
receive_data (int fd)
{
	char buf[MSG_BUF_SIZE];
	int ret = 0;
	while (1) {
		ret = recv(fd, buf, MSG_BUF_SIZE, 0);
		if ((-1 == ret) && (errno == EWOULDBLOCK || errno == EAGAIN)) {
				continue;
		} 
		else if(-1 == ret) {
			syslog(LOG_ERR, "recv error is failed ! : %s\n" , strerror(errno));
			goto err_exit;
		}
		break;
	}

	command_t *recv_data;
	recv_data = (command_t *)buf;
	printf("CMD : %c \n", recv_data->cmd );
	if (recv_data->cmd == M_CMD_L) {
		
		response_t *login_rsp;
		login_rsp = constr_send_rsp(recv_data);
		if (login_rsp == NULL) {
			syslog(LOG_ERR, "constr_send_rsp() is failed !\n");
			return -1;
		}
		
		ret = send(fd, login_rsp, LOG_RSP_LEN, 0);
		if (ret == -1) {
			syslog(LOG_ERR, "send() login_rsp  is failed !\n");
			return -1;
		}
		free(login_rsp);
	} 
	else if (recv_data->cmd == M_CMD_S) {
		//parser cfg data ,call funtion
		sim_trader_t *sim_data;
		trad_sim_cfg_t *cfg;
		cfg = (trad_sim_cfg_t *)recv_data->data;
		
		sim_data = sim_trader_init(cfg);
		if (sim_data == NULL) {
			syslog(LOG_ERR,"sim_trader_init() IS failed \n");
			return -1;
		}
		int size = sim_trader_size(sim_data);
		ret = sim_trader_start(sim_data, fd);
		if (ret == -1) {
			syslog(LOG_ERR,"sim_trader_start() IS failed \n");
			return -1;
		}
		sim_trader_destroy(sim_data);
	} 
	else {
		syslog(LOG_ERR , "unexpected cmd %c  , ID : %d , len : %d \n", 
				recv_data->cmd,
				recv_data->id,
				recv_data->len);
		return -1;
	}

err_exit:
	if (fd > 0) {
		close(fd);
		syslog(LOG_ERR, " recv_data()  fd  is close ! \n");
	}
	return -1;	
}