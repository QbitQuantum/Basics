struct uwsgi_buffer *uwsgi_routing_translate(struct wsgi_request *wsgi_req, struct uwsgi_route *ur, char *subject, uint16_t subject_len, char *data, size_t data_len) {

	// cannot fail
	char *pass1 = uwsgi_regexp_apply_ovec(subject, subject_len, data, data_len, ur->ovector, ur->ovn);
	size_t pass1_len = strlen(pass1);

	struct uwsgi_buffer *ub = uwsgi_buffer_new(pass1_len);
	size_t i;
	int status = 0;
	char *key = NULL;
	size_t keylen = 0;
	for(i=0;i<pass1_len;i++) {
		switch(status) {
			case 0:
				if (pass1[i] == '$') {
					status = 1;
					break;
				}
				if (uwsgi_buffer_append(ub, pass1 + i, 1)) goto error;
				break;
			case 1:
				if (pass1[i] == '{') {
					status = 2;
					key = pass1+i+1;
					keylen = 0;
					break;
				}
				status = 0;
				key = NULL;
				keylen = 0;
				if (uwsgi_buffer_append(ub, "$", 1)) goto error;
				if (uwsgi_buffer_append(ub, pass1 + i, 1)) goto error;
				break;
			case 2:
				if (pass1[i] == '}') {
					uint16_t vallen = 0;
					char *value = uwsgi_get_var(wsgi_req, key, keylen, &vallen);
					if (value) {
						if (uwsgi_buffer_append(ub, value, vallen)) goto error;
					}
                                        status = 0;
					key = NULL;
					keylen = 0;
                                        break;
                                }
				keylen++;
				break;
			default:
				break;
		}
	}

	// fix the buffer
	if (status == 1) {
		if (uwsgi_buffer_append(ub, "$", 1)) goto error;
	}
	else if (status == 2) {
		if (uwsgi_buffer_append(ub, "${", 2)) goto error;
		if (keylen > 0) {
			if (uwsgi_buffer_append(ub, key, keylen)) goto error;
		}
	}

	free(pass1);
	return ub;

error:
	uwsgi_buffer_destroy(ub);
	return NULL;
}