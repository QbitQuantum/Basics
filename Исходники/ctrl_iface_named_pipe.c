static void wpa_supplicant_ctrl_iface_rx(struct wpa_ctrl_dst *dst, size_t len)
{
	struct wpa_supplicant *wpa_s = dst->priv->wpa_s;
	char *reply = NULL, *send_buf;
	size_t reply_len = 0, send_len;
	int new_attached = 0;
	char *buf = dst->req_buf;

	dst->used = 1;
	if (len >= REQUEST_BUFSIZE)
		len = REQUEST_BUFSIZE - 1;
	buf[len] = '\0';

	if (os_strcmp(buf, "ATTACH") == 0) {
		dst->attached = 1;
		wpa_printf(MSG_DEBUG, "CTRL_IFACE monitor attached");
		new_attached = 1;
		reply_len = 2;
	} else if (os_strcmp(buf, "DETACH") == 0) {
		dst->attached = 0;
		wpa_printf(MSG_DEBUG, "CTRL_IFACE monitor detached");
		reply_len = 2;
	} else if (os_strncmp(buf, "LEVEL ", 6) == 0) {
		wpa_printf(MSG_DEBUG, "CTRL_IFACE LEVEL %s", buf + 6);
		dst->debug_level = atoi(buf + 6);
		reply_len = 2;
	} else {
		reply = wpa_supplicant_ctrl_iface_process(wpa_s, buf,
							  &reply_len);
	}

	if (reply) {
		send_buf = reply;
		send_len = reply_len;
	} else if (reply_len == 2) {
		send_buf = "OK\n";
		send_len = 3;
	} else {
		send_buf = "FAIL\n";
		send_len = 5;
	}

	os_free(dst->rsp_buf);
	dst->rsp_buf = os_malloc(send_len);
	if (dst->rsp_buf == NULL) {
		ctrl_close_pipe(dst);
		os_free(reply);
		return;
	}
	os_memcpy(dst->rsp_buf, send_buf, send_len);
	os_free(reply);

	if (!WriteFileEx(dst->pipe, dst->rsp_buf, send_len, &dst->overlap,
			 ctrl_iface_write_completed)) {
		wpa_printf(MSG_DEBUG, "CTRL: WriteFileEx failed: %d",
			   (int) GetLastError());
		ctrl_close_pipe(dst);
	} else {
		wpa_printf(MSG_DEBUG, "CTRL: Overlapped write started for %p",
			   dst);
	}

	if (new_attached)
		eapol_sm_notify_ctrl_attached(wpa_s->eapol);
}