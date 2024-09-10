int32 evt_listener_pack_json(json_t *result, evt_listener_t *listener)
{
	int8 evt_type[128] = {};
	int32 i = 0;
	json_t *evt_type_item = NULL;

	if (strnlen_s(listener->url, sizeof(listener->url)-1) == 0) {
		HTTPD_ERR("invalid subscribe destination\n");
		return -1;
	}

	json_object_add(result, RMM_JSON_ODATA_CONTEXT, json_string(listener->odata_context));
	json_object_add(result, RMM_JSON_ODATA_ID, json_string(listener->odata_id));
	json_object_add(result, RMM_JSON_ODATA_TYPE, json_string(listener->odata_type));
	json_object_add(result, RMM_JSON_RF_ID, json_string(listener->id));
	json_object_add(result, RMM_JSON_RF_NAME, json_string(listener->name));
	json_object_add(result, RMM_JSON_RF_DESC, json_string(listener->description));
	json_object_add(result, RMM_JSON_RF_DEST_URL, json_string(listener->url));

	evt_type_item = json_array();
	if (evt_type_item == NULL) {
		HTTPD_ERR("json array request fail\n");
		return -1;
	}

	for (i = 0; i < listener->evt_index; i++) {
		memset(evt_type, 0, sizeof(evt_type));
		get_event_type_by_node_type(listener->event_types[i], evt_type, sizeof(evt_type));
		if (strnlen_s(evt_type, sizeof(evt_type)-1) != 0)
			json_array_add(evt_type_item, json_string(evt_type));
	}
	json_object_add(result, RMM_JSON_RF_EVT_TYPES, evt_type_item);

	json_object_add(result, RMM_JSON_RF_CONTEXT, json_string(listener->context));
	json_object_add(result, RMM_JSON_RF_PROTOCOL, json_string(listener->protocol));

	return 0;
}