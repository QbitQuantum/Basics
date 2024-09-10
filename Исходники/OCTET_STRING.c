/*
 * Decode OCTET STRING type.
 */
asn_dec_rval_t
OCTET_STRING_decode_ber(asn_codec_ctx_t *opt_codec_ctx,
	asn_TYPE_descriptor_t *td,
	void **sptr, const void *buf_ptr, size_t size, int tag_mode) {
	asn_OCTET_STRING_specifics_t *specs = td->specifics
				? (asn_OCTET_STRING_specifics_t *)td->specifics
				: &asn_DEF_OCTET_STRING_specs;
	BIT_STRING_t *st = (BIT_STRING_t *)*sptr;
	asn_dec_rval_t rval;
	asn_struct_ctx_t *ctx;
	ssize_t consumed_myself = 0;
	struct _stack *stck;		/* Expectations stack structure */
	struct _stack_el *sel = 0;	/* Stack element */
	int tlv_constr;
	enum asn_OS_Subvariant type_variant = specs->subvariant;

	ASN_DEBUG("Decoding %s as %s (frame %ld)",
		td->name,
		(type_variant == ASN_OSUBV_STR) ?
			"OCTET STRING" : "OS-SpecialCase",
		(long)size);

	/*
	 * Create the string if does not exist.
	 */
	if(st == NULL) {
		st = (BIT_STRING_t *)(*sptr = CALLOC(1, specs->struct_size));
		if(st == NULL) RETURN(RC_FAIL);
	}

	/* Restore parsing context */
	ctx = (asn_struct_ctx_t *)((char *)st + specs->ctx_offset);

	switch(ctx->phase) {
	case 0:
		/*
		 * Check tags.
		 */
		rval = ber_check_tags(opt_codec_ctx, td, ctx,
			buf_ptr, size, tag_mode, -1,
			&ctx->left, &tlv_constr);
		if(rval.code != RC_OK)
			return rval;

		if(tlv_constr) {
			/*
			 * Complex operation, requires stack of expectations.
			 */
			ctx->ptr = _new_stack();
			if(ctx->ptr) {
				stck = (struct _stack *)ctx->ptr;
			} else {
				RETURN(RC_FAIL);
			}
		} else {
			/*
			 * Jump into stackless primitive decoding.
			 */
			_CH_PHASE(ctx, 3);
			if(type_variant == ASN_OSUBV_ANY && tag_mode != 1)
				APPEND(buf_ptr, rval.consumed);
			ADVANCE(rval.consumed);
			goto phase3;
		}

		NEXT_PHASE(ctx);
		/* Fall through */
	case 1:
	phase1:
		/*
		 * Fill the stack with expectations.
		 */
		stck = (struct _stack *)ctx->ptr;
		sel = stck->cur_ptr;
	  do {
		ber_tlv_tag_t tlv_tag;
		ber_tlv_len_t tlv_len;
		ber_tlv_tag_t expected_tag;
		ssize_t tl, ll, tlvl;
				/* This one works even if (sel->left == -1) */
		size_t Left = ((!sel||(size_t)sel->left >= size)
					?size:(size_t)sel->left);


		ASN_DEBUG("%p, s->l=%ld, s->wn=%ld, s->g=%ld\n", sel,
			(long)(sel?sel->left:0),
			(long)(sel?sel->want_nulls:0),
			(long)(sel?sel->got:0)
		);
		if(sel && sel->left <= 0 && sel->want_nulls == 0) {
			if(sel->prev) {
				struct _stack_el *prev = sel->prev;
				if(prev->left != -1) {
					if(prev->left < sel->got)
						RETURN(RC_FAIL);
					prev->left -= sel->got;
				}
				prev->got += sel->got;
				sel = stck->cur_ptr = prev;
				if(!sel) break;
				tlv_constr = 1;
				continue;
			} else {
				sel = stck->cur_ptr = 0;
				break;	/* Nothing to wait */
			}
		}

		tl = ber_fetch_tag(buf_ptr, Left, &tlv_tag);
		ASN_DEBUG("fetch tag(size=%ld,L=%ld), %sstack, left=%ld, wn=%ld, tl=%ld",
			(long)size, (long)Left, sel?"":"!",
			(long)(sel?sel->left:0),
			(long)(sel?sel->want_nulls:0),
			(long)tl);
		switch(tl) {
		case -1: RETURN(RC_FAIL);
		case 0: RETURN(RC_WMORE);
		}

		tlv_constr = BER_TLV_CONSTRUCTED(buf_ptr);

		ll = ber_fetch_length(tlv_constr,
				(const char *)buf_ptr + tl,Left - tl,&tlv_len);
		ASN_DEBUG("Got tag=%s, tc=%d, left=%ld, tl=%ld, len=%ld, ll=%ld",
			ber_tlv_tag_string(tlv_tag), tlv_constr,
				(long)Left, (long)tl, (long)tlv_len, (long)ll);
		switch(ll) {
		case -1: RETURN(RC_FAIL);
		case 0: RETURN(RC_WMORE);
		}

		if(sel && sel->want_nulls
			&& ((const uint8_t *)buf_ptr)[0] == 0
			&& ((const uint8_t *)buf_ptr)[1] == 0)
		{

			ASN_DEBUG("Eat EOC; wn=%d--", sel->want_nulls);

			if(type_variant == ASN_OSUBV_ANY
			&& (tag_mode != 1 || sel->cont_level))
				APPEND("\0\0", 2);

			ADVANCE(2);
			sel->got += 2;
			if(sel->left != -1) {
				sel->left -= 2;	/* assert(sel->left >= 2) */
			}

			sel->want_nulls--;
			if(sel->want_nulls == 0) {
				/* Move to the next expectation */
				sel->left = 0;
				tlv_constr = 1;
			}

			continue;
		}

		/*
		 * Set up expected tags,
		 * depending on ASN.1 type being decoded.
		 */
		switch(type_variant) {
		case ASN_OSUBV_BIT:
			/* X.690: 8.6.4.1, NOTE 2 */
			/* Fall through */
		case ASN_OSUBV_STR:
		default:
			if(sel) {
				int level = sel->cont_level;
				if(level < td->all_tags_count) {
					expected_tag = td->all_tags[level];
					break;
				} else if(td->all_tags_count) {
					expected_tag = td->all_tags
						[td->all_tags_count - 1];
					break;
				}
				/* else, Fall through */
			}
			/* Fall through */
		case ASN_OSUBV_ANY:
			expected_tag = tlv_tag;
			break;
		}


		if(tlv_tag != expected_tag) {
			char buf[2][32];
			ber_tlv_tag_snprint(tlv_tag,
				buf[0], sizeof(buf[0]));
			ber_tlv_tag_snprint(td->tags[td->tags_count-1],
				buf[1], sizeof(buf[1]));
			ASN_DEBUG("Tag does not match expectation: %s != %s",
				buf[0], buf[1]);
			RETURN(RC_FAIL);
		}

		tlvl = tl + ll;	/* Combined length of T and L encoding */
		if((tlv_len + tlvl) < 0) {
			/* tlv_len value is too big */
			ASN_DEBUG("TLV encoding + length (%ld) is too big",
				(long)tlv_len);
			RETURN(RC_FAIL);
		}

		/*
		 * Append a new expectation.
		 */
		sel = OS__add_stack_el(stck);
		if(!sel) RETURN(RC_FAIL);

		sel->tag = tlv_tag;

		sel->want_nulls = (tlv_len==-1);
		if(sel->prev && sel->prev->left != -1) {
			/* Check that the parent frame is big enough */
			if(sel->prev->left < tlvl + (tlv_len==-1?0:tlv_len))
				RETURN(RC_FAIL);
			if(tlv_len == -1)
				sel->left = sel->prev->left - tlvl;
			else
				sel->left = tlv_len;
		} else {
			sel->left = tlv_len;
		}
		if(type_variant == ASN_OSUBV_ANY
		&& (tag_mode != 1 || sel->cont_level))
			APPEND(buf_ptr, tlvl);
		sel->got += tlvl;
		ADVANCE(tlvl);

		ASN_DEBUG("+EXPECT2 got=%ld left=%ld, wn=%d, clvl=%d",
			(long)sel->got, (long)sel->left,
			sel->want_nulls, sel->cont_level);

	  } while(tlv_constr);
		if(sel == NULL) {
			/* Finished operation, "phase out" */
			ASN_DEBUG("Phase out");
			_CH_PHASE(ctx, +3);
			break;
		}

		NEXT_PHASE(ctx);
		/* Fall through */
	case 2:
		stck = (struct _stack *)ctx->ptr;
		sel = stck->cur_ptr;
		ASN_DEBUG("Phase 2: Need %ld bytes, size=%ld, alrg=%ld, wn=%d",
			(long)sel->left, (long)size, (long)sel->got,
				sel->want_nulls);
	    {
		ber_tlv_len_t len;

		assert(sel->left >= 0);

		len = ((ber_tlv_len_t)size < sel->left)
				? (ber_tlv_len_t)size : sel->left;
		if(len > 0) {
			if(type_variant == ASN_OSUBV_BIT
			&& sel->bits_chopped == 0) {
				/* Put the unused-bits-octet away */
				st->bits_unused = *(const uint8_t *)buf_ptr;
				APPEND(((const char *)buf_ptr+1), (len - 1));
				sel->bits_chopped = 1;
			} else {
				APPEND(buf_ptr, len);
			}
			ADVANCE(len);
			sel->left -= len;
			sel->got += len;
		}

		if(sel->left) {
			ASN_DEBUG("OS left %ld, size = %ld, wn=%d\n",
				(long)sel->left, (long)size, sel->want_nulls);
			RETURN(RC_WMORE);
		}

		PREV_PHASE(ctx);
		goto phase1;
	    }
		break;
	case 3:
	phase3:
		/*
		 * Primitive form, no stack required.
		 */
		assert(ctx->left >= 0);

		if(size < (size_t)ctx->left) {
			if(!size) RETURN(RC_WMORE);
			if(type_variant == ASN_OSUBV_BIT && !ctx->context) {
				st->bits_unused = *(const uint8_t *)buf_ptr;
				ctx->left--;
				ADVANCE(1);
			}
			APPEND(buf_ptr, size);
			assert(ctx->context > 0);
			ctx->left -= size;
			ADVANCE(size);
			RETURN(RC_WMORE);
		} else {
			if(type_variant == ASN_OSUBV_BIT
			&& !ctx->context && ctx->left) {
				st->bits_unused = *(const uint8_t *)buf_ptr;
				ctx->left--;
				ADVANCE(1);
			}
			APPEND(buf_ptr, ctx->left);
			ADVANCE(ctx->left);
			ctx->left = 0;

			NEXT_PHASE(ctx);
		}
		break;
	}

	/*
	 * BIT STRING-specific processing.
	 */
	if(type_variant == ASN_OSUBV_BIT && st->size) {
		/* Finalize BIT STRING: zero out unused bits. */
		st->buf[st->size-1] &= 0xff << st->bits_unused;
	}

	ASN_DEBUG("Took %ld bytes to encode %s: [%s]:%ld",
		(long)consumed_myself, td->name,
		(type_variant == ASN_OSUBV_STR) ? (char *)st->buf : "<data>",
		(long)st->size);


	RETURN(RC_OK);
}