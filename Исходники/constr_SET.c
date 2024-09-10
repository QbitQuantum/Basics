/*
 * The decoder of the SET type.
 */
asn_dec_rval_t
SET_decode_ber(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
	void **struct_ptr, const void *ptr, size_t size, int tag_mode) {
	/*
	 * Bring closer parts of structure description.
	 */
	asn_SET_specifics_t *specs = (asn_SET_specifics_t *)td->specifics;
	asn_TYPE_member_t *elements = td->elements;

	/*
	 * Parts of the structure being constructed.
	 */
	void *st = *struct_ptr;	/* Target structure. */
	asn_struct_ctx_t *ctx;	/* Decoder context */

	ber_tlv_tag_t tlv_tag;	/* T from TLV */
	asn_dec_rval_t rval;	/* Return code from subparsers */

	ssize_t consumed_myself = 0;	/* Consumed bytes from ptr */
	int edx;			/* SET element's index */

	ASN_DEBUG("Decoding %s as SET", td->name);

	if(_ASN_STACK_OVERFLOW_CHECK(opt_codec_ctx))
		_ASN_DECODE_FAILED;

	/*
	 * Create the target structure if it is not present already.
	 */
	if(st == 0) {
		st = *struct_ptr = CALLOC(1, specs->struct_size);
		if(st == 0) {
			RETURN(RC_FAIL);
		}
	}

	/*
	 * Restore parsing context.
	 */
	ctx = (asn_struct_ctx_t *)((char *)st + specs->ctx_offset);
	
	/*
	 * Start to parse where left previously
	 */
	switch(ctx->phase) {
	case 0:
		/*
		 * PHASE 0.
		 * Check that the set of tags associated with given structure
		 * perfectly fits our expectations.
		 */

		rval = ber_check_tags(opt_codec_ctx, td, ctx, ptr, size,
			tag_mode, 1, &ctx->left, 0);
		if(rval.code != RC_OK) {
			ASN_DEBUG("%s tagging check failed: %d",
				td->name, rval.code);
			return rval;
		}

		if(ctx->left >= 0)
			ctx->left += rval.consumed; /* ?Substracted below! */
		ADVANCE(rval.consumed);

		NEXT_PHASE(ctx);

		ASN_DEBUG("Structure advertised %ld bytes, "
			"buffer contains %ld", (long)ctx->left, (long)size);

		/* Fall through */
	case 1:
		/*
		 * PHASE 1.
		 * From the place where we've left it previously,
		 * try to decode the next member from the list of
		 * this structure's elements.
		 * Note that elements in BER may arrive out of
		 * order, yet DER mandates that they shall arive in the
		 * canonical order of their tags. So, there is a room
		 * for optimization.
		 */
	  for(;; ctx->step = 0) {
		asn_TYPE_tag2member_t *t2m;
		asn_TYPE_tag2member_t key;
		void *memb_ptr;		/* Pointer to the member */
		void **memb_ptr2;	/* Pointer to that pointer */
		ssize_t tag_len;	/* Length of TLV's T */

		if(ctx->step & 1) {
			edx = ctx->step >> 1;
			goto microphase2;
		}

		/*
		 * MICROPHASE 1: Synchronize decoding.
		 */

		if(ctx->left == 0)
			/*
			 * No more things to decode.
			 * Exit out of here and check whether all mandatory
			 * elements have been received (in the next phase).
			 */
			break;

		/*
		 * Fetch the T from TLV.
		 */
		tag_len = ber_fetch_tag(ptr, LEFT, &tlv_tag);
		switch(tag_len) {
		case 0: if(!SIZE_VIOLATION) RETURN(RC_WMORE);
			/* Fall through */
		case -1: RETURN(RC_FAIL);
		}

		if(ctx->left < 0 && ((const uint8_t *)ptr)[0] == 0) {
			if(LEFT < 2) {
				if(SIZE_VIOLATION)
					RETURN(RC_FAIL);
				else
					RETURN(RC_WMORE);
			} else if(((const uint8_t *)ptr)[1] == 0) {
				/*
				 * Found the terminator of the
				 * indefinite length structure.
				 * Invoke the generic finalization function.
				 */
				goto phase3;
			}
		}

		key.el_tag = tlv_tag;
		t2m = (asn_TYPE_tag2member_t *)bsearch(&key,
				specs->tag2el, specs->tag2el_count,
				sizeof(specs->tag2el[0]), _t2e_cmp);
		if(t2m) {
			/*
			 * Found the element corresponding to the tag.
			 */
			edx = t2m->el_no;
			ctx->step = (edx << 1) + 1;
			ASN_DEBUG("Got tag %s (%s), edx %d",
				ber_tlv_tag_string(tlv_tag), td->name, edx);
		} else if(specs->extensible == 0) {
			ASN_DEBUG("Unexpected tag %s "
				"in non-extensible SET %s",
				ber_tlv_tag_string(tlv_tag), td->name);
			RETURN(RC_FAIL);
		} else {
			/* Skip this tag */
			ssize_t skip;

			ASN_DEBUG("Skipping unknown tag %s",
				ber_tlv_tag_string(tlv_tag));

			skip = ber_skip_length(opt_codec_ctx,
				BER_TLV_CONSTRUCTED(ptr),
				(const char *)ptr + tag_len, LEFT - tag_len);

			switch(skip) {
			case 0: if(!SIZE_VIOLATION) RETURN(RC_WMORE);
				/* Fall through */
			case -1: RETURN(RC_FAIL);
			}

			ADVANCE(skip + tag_len);
			continue;  /* Try again with the next tag */
		}

		/*
		 * MICROPHASE 2: Invoke the member-specific decoder.
		 */
	microphase2:

		/*
		 * Check for duplications: must not overwrite
		 * already decoded elements.
		 */
		if(ASN_SET_ISPRESENT2((char *)st + specs->pres_offset, edx)) {
			ASN_DEBUG("SET %s: Duplicate element %s (%d)",
				td->name, elements[edx].name, edx);
			RETURN(RC_FAIL);
		}
		
		/*
		 * Compute the position of the member inside a structure,
		 * and also a type of containment (it may be contained
		 * as pointer or using inline inclusion).
		 */
		if(elements[edx].flags & ATF_POINTER) {
			/* Member is a pointer to another structure */
			memb_ptr2 = (void **)((char *)st + elements[edx].memb_offset);
		} else {
			/*
			 * A pointer to a pointer
			 * holding the start of the structure
			 */
			memb_ptr = (char *)st + elements[edx].memb_offset;
			memb_ptr2 = &memb_ptr;
		}
		/*
		 * Invoke the member fetch routine according to member's type
		 */
		rval = elements[edx].type->ber_decoder(opt_codec_ctx,
				elements[edx].type,
				memb_ptr2, ptr, LEFT,
				elements[edx].tag_mode);
		switch(rval.code) {
		case RC_OK:
			ASN_SET_MKPRESENT((char *)st + specs->pres_offset, edx);
			break;
		case RC_WMORE: /* More data expected */
			if(!SIZE_VIOLATION) {
				ADVANCE(rval.consumed);
				RETURN(RC_WMORE);
			}
			/* Fail through */
		case RC_FAIL: /* Fatal error */
			RETURN(RC_FAIL);
		} /* switch(rval) */
		
		ADVANCE(rval.consumed);
	  }	/* for(all structure members) */

	phase3:
		ctx->phase = 3;
		/* Fall through */
	case 3:
	case 4:	/* Only 00 is expected */
		ASN_DEBUG("SET %s Leftover: %ld, size = %ld",
			td->name, (long)ctx->left, (long)size);

		/*
		 * Skip everything until the end of the SET.
		 */
		while(ctx->left) {
			ssize_t tl, ll;

			tl = ber_fetch_tag(ptr, LEFT, &tlv_tag);
			switch(tl) {
			case 0: if(!SIZE_VIOLATION) RETURN(RC_WMORE);
				/* Fall through */
			case -1: RETURN(RC_FAIL);
			}

			/*
			 * If expected <0><0>...
			 */
			if(ctx->left < 0
				&& ((const uint8_t *)ptr)[0] == 0) {
				if(LEFT < 2) {
					if(SIZE_VIOLATION)
						RETURN(RC_FAIL);
					else
						RETURN(RC_WMORE);
				} else if(((const uint8_t *)ptr)[1] == 0) {
					/*
					 * Correctly finished with <0><0>.
					 */
					ADVANCE(2);
					ctx->left++;
					ctx->phase = 4;
					continue;
				}
			}

			if(specs->extensible == 0 || ctx->phase == 4) {
				ASN_DEBUG("Unexpected continuation "
					"of a non-extensible type %s "
					"(ptr=%02x)",
					td->name, *(const uint8_t *)ptr);
				RETURN(RC_FAIL);
			}

			ll = ber_skip_length(opt_codec_ctx,
				BER_TLV_CONSTRUCTED(ptr),
				(const char *)ptr + tl, LEFT - tl);
			switch(ll) {
			case 0: if(!SIZE_VIOLATION) RETURN(RC_WMORE);
				/* Fall through */
			case -1: RETURN(RC_FAIL);
			}

			ADVANCE(tl + ll);
		}

		ctx->phase = 5;
	case 5:
		/* Check that all mandatory elements are present. */
		if(!_SET_is_populated(td, st))
			RETURN(RC_FAIL);

		NEXT_PHASE(ctx);
	}