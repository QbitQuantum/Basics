int uwsgi_proto_zeromq_accept(struct wsgi_request *wsgi_req, int fd) {

	zmq_msg_t message;
	char *req_uuid = NULL;
	size_t req_uuid_len = 0;
	char *req_id = NULL;
	size_t req_id_len = 0;
	char *req_path = NULL;
	size_t req_path_len = 0;
#ifdef UWSGI_JSON
	json_t *root;
	json_error_t error;
#endif
	char *mongrel2_req = NULL;
	size_t mongrel2_req_size = 0;
	int resp_id_len;
	uint32_t events = 0;
	char *message_ptr;
	size_t message_size = 0;
	char *post_data;


#ifdef ZMQ_EVENTS
	size_t events_len = sizeof(uint32_t);
	if (uwsgi.edge_triggered == 0) {
		if (zmq_getsockopt(pthread_getspecific(uwsgi.zmq_pull), ZMQ_EVENTS, &events, &events_len) < 0) {
			uwsgi_error("zmq_getsockopt()");
			uwsgi.edge_triggered = 0;
			return -1;
		}
	}
#endif

	if (events & ZMQ_POLLIN || uwsgi.edge_triggered) {
		wsgi_req->do_not_add_to_async_queue = 1;
		wsgi_req->proto_parser_status = 0;
		zmq_msg_init(&message);
		if (zmq_recv(pthread_getspecific(uwsgi.zmq_pull), &message, uwsgi.zeromq_recv_flag) < 0) {
			if (errno == EAGAIN) {
				uwsgi.edge_triggered = 0;
			}
			else {
				uwsgi_error("zmq_recv()");
			}
			zmq_msg_close(&message);
			return -1;
		}
		uwsgi.edge_triggered = 1;
		message_size = zmq_msg_size(&message);
		//uwsgi_log("%.*s\n", (int) wsgi_req->proto_parser_pos, zmq_msg_data(&message));
		if (message_size > 0xffff) {
			uwsgi_log("too much big message %d\n", message_size);
			zmq_msg_close(&message);
			wsgi_req->do_not_log = 1;
			return -1;
		}

		message_ptr = zmq_msg_data(&message);

		// warning mongrel2_req_size will contains a bad value, but this is not a problem...
		post_data = uwsgi_split4(message_ptr, message_size, ' ', &req_uuid, &req_uuid_len, &req_id, &req_id_len, &req_path, &req_path_len, &mongrel2_req, &mongrel2_req_size);
		if (post_data == NULL) {
			uwsgi_log("cannot parse message (split4 phase)\n");
			zmq_msg_close(&message);
			wsgi_req->do_not_log = 1;
			return -1;
		}

		// fix post_data, mongrel2_req and mongrel2_req_size
		post_data = uwsgi_netstring(mongrel2_req, message_size - (mongrel2_req - message_ptr), &mongrel2_req, &mongrel2_req_size);
		if (post_data == NULL) {
			uwsgi_log("cannot parse message (body netstring phase)\n");
			zmq_msg_close(&message);
			wsgi_req->do_not_log = 1;
			return -1;
		}

		// ok ready to parse tnetstring/json data and build uwsgi request
		if (mongrel2_req[mongrel2_req_size] == '}') {
			if (uwsgi_mongrel2_tnetstring_parse(wsgi_req, mongrel2_req, mongrel2_req_size)) {
				zmq_msg_close(&message);
				wsgi_req->do_not_log = 1;
				return -1;
			}
		}
		else {
#ifdef UWSGI_JSON
#ifdef UWSGI_DEBUG
			uwsgi_log("JSON %d: %.*s\n", mongrel2_req_size, mongrel2_req_size, mongrel2_req);
#endif
			// add a zero to the end of buf
			mongrel2_req[mongrel2_req_size] = 0;
			root = json_loads(mongrel2_req, 0, &error);
			if (!root) {
				uwsgi_log("error parsing JSON data: line %d %s\n", error.line, error.text);
				zmq_msg_close(&message);
				wsgi_req->do_not_log = 1;
				return -1;
			}

			if (uwsgi_mongrel2_json_parse(root, wsgi_req)) {
				json_decref(root);
				zmq_msg_close(&message);
				wsgi_req->do_not_log = 1;
				return -1;
			}

			json_decref(root);
#else
			uwsgi_log("JSON support not enabled (recompile uWSGI with libjansson support, or re-configure mongrel2 with \"protocol='tnetstring'\". skip request\n");
#endif
		}

		// pre-build the mongrel2 response_header
		wsgi_req->proto_parser_buf = uwsgi_malloc(req_uuid_len + 1 + 11 + 1 + req_id_len + 1 + 1);
		memcpy(wsgi_req->proto_parser_buf, req_uuid, req_uuid_len);
		((char *) wsgi_req->proto_parser_buf)[req_uuid_len] = ' ';
		resp_id_len = uwsgi_num2str2(req_id_len, wsgi_req->proto_parser_buf + req_uuid_len + 1);
		((char *) wsgi_req->proto_parser_buf)[req_uuid_len + 1 + resp_id_len] = ':';

		memcpy((char *) wsgi_req->proto_parser_buf + req_uuid_len + 1 + resp_id_len + 1, req_id, req_id_len);

		memcpy((char *) wsgi_req->proto_parser_buf + req_uuid_len + 1 + resp_id_len + 1 + req_id_len, ", ", 2);
		wsgi_req->proto_parser_pos = (uint64_t) req_uuid_len + 1 + resp_id_len + 1 + req_id_len + 1 + 1;

		// handle post data
		if (wsgi_req->post_cl > 0 && !wsgi_req->async_post) {
			if (uwsgi_netstring(post_data, message_size - (post_data - message_ptr), &message_ptr, &wsgi_req->post_cl)) {
#ifdef UWSGI_DEBUG
				uwsgi_log("post_size: %d\n", wsgi_req->post_cl);
#endif
				wsgi_req->async_post = tmpfile();
				if (fwrite(message_ptr, wsgi_req->post_cl, 1, wsgi_req->async_post) != 1) {
					uwsgi_error("fwrite()");
					zmq_msg_close(&message);
					return -1;
				}
				rewind(wsgi_req->async_post);
				wsgi_req->body_as_file = 1;
			}
		}


		zmq_msg_close(&message);

		return 0;
	}

	return -1;
}