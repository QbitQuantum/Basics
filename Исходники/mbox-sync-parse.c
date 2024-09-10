int mbox_sync_parse_next_mail(struct istream *input,
			      struct mbox_sync_mail_context *ctx)
{
	struct mbox_sync_context *sync_ctx = ctx->sync_ctx;
	struct message_header_parser_ctx *hdr_ctx;
	struct message_header_line *hdr;
	struct mbox_sync_header_func *func;
	struct mbox_md5_context *mbox_md5_ctx;
	size_t line_start_pos;
	int i, ret;

	ctx->hdr_offset = ctx->mail.offset;
	ctx->mail.flags = MAIL_RECENT; /* default to having recent flag */

        ctx->header_first_change = (size_t)-1;
	ctx->header_last_change = 0;

	for (i = 0; i < MBOX_HDR_COUNT; i++)
		ctx->hdr_pos[i] = (size_t)-1;

	ctx->content_length = (uoff_t)-1;
	str_truncate(ctx->header, 0);

        mbox_md5_ctx = ctx->sync_ctx->mbox->md5_v.init();

        line_start_pos = 0;
	hdr_ctx = message_parse_header_init(input, NULL, 0);
	while ((ret = message_parse_header_next(hdr_ctx, &hdr)) > 0) {
		if (hdr->eoh) {
			ctx->have_eoh = TRUE;
			break;
		}

		if (!hdr->continued) {
			line_start_pos = str_len(ctx->header);
			str_append(ctx->header, hdr->name);
			str_append_data(ctx->header, hdr->middle, hdr->middle_len);
		}

		func = bsearch(hdr->name, header_funcs,
			       N_ELEMENTS(header_funcs), sizeof(*header_funcs),
			       mbox_sync_bsearch_header_func_cmp);

		if (func != NULL) {
			if (hdr->continues) {
				hdr->use_full_value = TRUE;
				continue;
			}

			if (!func->func(ctx, hdr)) {
				/* this header is broken, remove it */
				ctx->need_rewrite = TRUE;
				str_truncate(ctx->header, line_start_pos);
				if (ctx->header_first_change == (size_t)-1) {
					ctx->header_first_change =
						line_start_pos;
				}
				continue;
			}
			buffer_append(ctx->header, hdr->full_value,
				      hdr->full_value_len);
		} else {
			ctx->sync_ctx->mbox->md5_v.more(mbox_md5_ctx, hdr);
			buffer_append(ctx->header, hdr->value,
				      hdr->value_len);
		}
		if (!hdr->no_newline) {
			if (hdr->crlf_newline)
				str_append_c(ctx->header, '\r');
			str_append_c(ctx->header, '\n');
		}
	}
	i_assert(ret != 0);
	message_parse_header_deinit(&hdr_ctx);

	ctx->sync_ctx->mbox->md5_v.finish(mbox_md5_ctx, ctx->hdr_md5_sum);

	if ((ctx->seq == 1 && !ctx->seen_imapbase) ||
	    (ctx->seq > 1 && sync_ctx->dest_first_mail)) {
		/* missing X-IMAPbase */
		ctx->need_rewrite = TRUE;
		if (sync_ctx->base_uid_validity == 0) {
			/* figure out a new UIDVALIDITY for us. */
			sync_ctx->base_uid_validity =
				sync_ctx->hdr->uid_validity != 0 &&
				!sync_ctx->renumber_uids ?
				sync_ctx->hdr->uid_validity :
				I_MAX((uint32_t)ioloop_time, 1);
		}
	}

	ctx->body_offset = input->v_offset;
	if (input->stream_errno != 0) {
		mbox_sync_set_critical(ctx->sync_ctx, "read(%s) failed: %s",
			i_stream_get_name(input), i_stream_get_error(input));
		return -1;
	}
	return 0;
}