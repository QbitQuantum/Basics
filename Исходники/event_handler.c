static json_t *rf_listeners_post(struct rest_uri_param *param)
{
	json_t *req = NULL;
	json_t *obj = NULL;
	int32 mask = 0;
	listener_dest_t listener;
	int32 listener_idx = 0;
	uint32 ary_size = sizeof(sub_listener_attrs)/sizeof(input_attr_t);

	req = json_parse(param->json_data);
	if (req == NULL) {
		update_response_info(param, HTTP_BAD_REQUEST);
		HTTPD_ERR("json parse error\n");
		return NULL;
	}

	if (libwrap_check_input_attrs(sub_listener_attrs, ary_size, req, NULL) != RESULT_OK) {
		update_response_info(param, HTTP_BAD_REQUEST);
		goto out;
	}

	obj = libwrap_get_attr_json(sub_listener_attrs, ary_size, "Protocol");
	if (obj) {
		int8 *input = NULL;
		input = json_string_value(obj);
		if (input && check_str_len(input, REST_EVENT_PROTOCOL)) {
			if (strncmp("Redfish", input, strnlen_s("Redfish", RSIZE_MAX_STR)) !=0 ) {
				update_response_info(param, HTTP_BAD_REQUEST);
				goto out;
			}
		} else {
			update_response_info(param, HTTP_BAD_REQUEST);
			goto out;
		}
	}

	mask |= RF_EVENT_MASK_ALL;

	if (process_listener(req, &listener, mask) != 0) {
		update_response_info(param, HTTP_BAD_REQUEST);
		HTTPD_ERR("process listener error\n");
		goto out;
	}

	listener_idx = libwrap_get_evt_listener_idx(mask, listener.dest);
	snprintf_s_si(param->rsp, HREF_URL_LEN, "http://%s/redfish/v1/EventService/Subscriptions/%d", param->host, listener_idx);
	update_response_info(param, HTTP_CREATED);

out:
	if (req)
		json_free(req);
	return NULL;
}