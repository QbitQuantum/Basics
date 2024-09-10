asn_dec_rval_t
xer_decode_primitive(asn_codec_ctx_t *opt_codec_ctx,
	asn_TYPE_descriptor_t *td,
	void **sptr,
	size_t struct_size,
	const char *opt_mname,
	const void *buf_ptr, size_t size,
	xer_primitive_body_decoder_f *prim_body_decoder
) {
	const char *xml_tag = opt_mname ? opt_mname : td->xml_tag;
	asn_struct_ctx_t s_ctx;
	struct xdp_arg_s s_arg;
	asn_dec_rval_t rc;

	/*
	 * Create the structure if does not exist.
	 */
	if(!*sptr) {
		*sptr = CALLOC(1, struct_size);
		if(!*sptr) _ASN_DECODE_FAILED;
	}

	memset(&s_ctx, 0, sizeof(s_ctx));
	s_arg.type_descriptor = td;
	s_arg.struct_key = *sptr;
	s_arg.prim_body_decoder = prim_body_decoder;
	s_arg.decoded_something = 0;
	s_arg.want_more = 0;

	rc = xer_decode_general(opt_codec_ctx, &s_ctx, &s_arg,
		xml_tag, buf_ptr, size,
		xer_decode__unexpected_tag, xer_decode__primitive_body);
	switch(rc.code) {
	case RC_OK:
		if(!s_arg.decoded_something) {
			char ch;
			ASN_DEBUG("Primitive body is not recognized, "
				"supplying empty one");
			/*
			 * Decoding opportunity has come and gone.
			 * Where's the result?
			 * Try to feed with empty body, see if it eats it.
			 */
			if(prim_body_decoder(s_arg.type_descriptor,
				s_arg.struct_key, &ch, 0)
					!= XPBD_BODY_CONSUMED) {
				/*
				 * This decoder does not like empty stuff.
				 */
				_ASN_DECODE_FAILED;
			}
		}
		break;
	case RC_WMORE:
		/*
		 * Redo the whole thing later.
		 * We don't have a context to save intermediate parsing state.
		 */
		rc.consumed = 0;
		break;
	case RC_FAIL:
		rc.consumed = 0;
		if(s_arg.want_more)
			rc.code = RC_WMORE;
		else
			_ASN_DECODE_FAILED;
		break;
	}
	return rc;
}