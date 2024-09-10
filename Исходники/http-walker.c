static void process_alternates_response(void *callback_data)
{
	struct alternates_request *alt_req =
		(struct alternates_request *)callback_data;
	struct walker *walker = alt_req->walker;
	struct walker_data *cdata = walker->data;
	struct active_request_slot *slot = alt_req->slot;
	struct alt_base *tail = cdata->alt;
	const char *base = alt_req->base;
	const char null_byte = '\0';
	char *data;
	int i = 0;

	if (alt_req->http_specific) {
		if (slot->curl_result != CURLE_OK ||
		    !alt_req->buffer->len) {

			/* Try reusing the slot to get non-http alternates */
			alt_req->http_specific = 0;
			sprintf(alt_req->url, "%s/objects/info/alternates",
				base);
			curl_easy_setopt(slot->curl, CURLOPT_URL,
					 alt_req->url);
			active_requests++;
			slot->in_use = 1;
			if (slot->finished != NULL)
				(*slot->finished) = 0;
			if (!start_active_slot(slot)) {
				cdata->got_alternates = -1;
				slot->in_use = 0;
				if (slot->finished != NULL)
					(*slot->finished) = 1;
			}
			return;
		}
	} else if (slot->curl_result != CURLE_OK) {
		if (!missing_target(slot)) {
			cdata->got_alternates = -1;
			return;
		}
	}

	fwrite_buffer((char *)&null_byte, 1, 1, alt_req->buffer);
	alt_req->buffer->len--;
	data = alt_req->buffer->buf;

	while (i < alt_req->buffer->len) {
		int posn = i;
		while (posn < alt_req->buffer->len && data[posn] != '\n')
			posn++;
		if (data[posn] == '\n') {
			int okay = 0;
			int serverlen = 0;
			struct alt_base *newalt;
			char *target = NULL;
			if (data[i] == '/') {
				/*
				 * This counts
				 * http://git.host/pub/scm/linux.git/
				 * -----------here^
				 * so memcpy(dst, base, serverlen) will
				 * copy up to "...git.host".
				 */
				const char *colon_ss = strstr(base,"://");
				if (colon_ss) {
					serverlen = (strchr(colon_ss + 3, '/')
						     - base);
					okay = 1;
				}
			} else if (!memcmp(data + i, "../", 3)) {
				/*
				 * Relative URL; chop the corresponding
				 * number of subpath from base (and ../
				 * from data), and concatenate the result.
				 *
				 * The code first drops ../ from data, and
				 * then drops one ../ from data and one path
				 * from base.  IOW, one extra ../ is dropped
				 * from data than path is dropped from base.
				 *
				 * This is not wrong.  The alternate in
				 *     http://git.host/pub/scm/linux.git/
				 * to borrow from
				 *     http://git.host/pub/scm/linus.git/
				 * is ../../linus.git/objects/.  You need
				 * two ../../ to borrow from your direct
				 * neighbour.
				 */
				i += 3;
				serverlen = strlen(base);
				while (i + 2 < posn &&
				       !memcmp(data + i, "../", 3)) {
					do {
						serverlen--;
					} while (serverlen &&
						 base[serverlen - 1] != '/');
					i += 3;
				}
				/* If the server got removed, give up. */
				okay = strchr(base, ':') - base + 3 <
				       serverlen;
			} else if (alt_req->http_specific) {
				char *colon = strchr(data + i, ':');
				char *slash = strchr(data + i, '/');
				if (colon && slash && colon < data + posn &&
				    slash < data + posn && colon < slash) {
					okay = 1;
				}
			}
			/* skip "objects\n" at end */
			if (okay) {
				target = xmalloc(serverlen + posn - i - 6);
				memcpy(target, base, serverlen);
				memcpy(target + serverlen, data + i,
				       posn - i - 7);
				target[serverlen + posn - i - 7] = 0;
				if (walker->get_verbosely)
					fprintf(stderr,
						"Also look at %s\n", target);
				newalt = xmalloc(sizeof(*newalt));
				newalt->next = NULL;
				newalt->base = target;
				newalt->got_indices = 0;
				newalt->packs = NULL;

				while (tail->next != NULL)
					tail = tail->next;
				tail->next = newalt;
			}
		}
		i = posn + 1;
	}

	cdata->got_alternates = 1;
}