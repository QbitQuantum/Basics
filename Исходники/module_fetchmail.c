/*
 * Fetch the body given PR_MSG_EDITOR_FORMAT property value
 */
static enum MAPISTATUS fetchmail_get_body(TALLOC_CTX *mem_ctx,
					  mapi_object_t *obj_message,
					  struct SRow *aRow,
					  DATA_BLOB *body)
{
	enum MAPISTATUS			retval;
	const struct SBinary_short	*bin;
	mapi_object_t			obj_stream;
	char				*data;
	uint8_t				format;

	/* Sanity checks */
	MAPI_RETVAL_IF(!obj_message, MAPI_E_INVALID_PARAMETER, NULL);

	/* initialize body DATA_BLOB */
	body->data = NULL;
	body->length = 0;

	retval = GetBestBody(obj_message, &format);
	MAPI_RETVAL_IF(retval, retval, NULL);

	switch (format) {
	case olEditorText:
		data = fetchmail_get_propval(aRow, PR_BODY_UNICODE);
		if (data) {
			body->data = talloc_memdup(mem_ctx, data, strlen(data));
			body->length = strlen(data);
		} else {
			mapi_object_init(&obj_stream);
			retval = OpenStream(obj_message, PR_BODY_UNICODE, 0, &obj_stream);
			MAPI_RETVAL_IF(retval, GetLastError(), NULL);
			
			retval = fetchmail_get_stream(mem_ctx, &obj_stream, body);
			MAPI_RETVAL_IF(retval, GetLastError(), NULL);
			
			mapi_object_release(&obj_stream);
		}
		break;
	case olEditorHTML:
		bin = (const struct SBinary_short *) fetchmail_get_propval(aRow, PR_HTML);
		if (bin) {
			body->data = talloc_memdup(mem_ctx, bin->lpb, bin->cb);
			body->length = bin->cb;
		} else {
			mapi_object_init(&obj_stream);
			retval = OpenStream(obj_message, PR_HTML, 0, &obj_stream);
			MAPI_RETVAL_IF(retval, GetLastError(), NULL);

			retval = fetchmail_get_stream(mem_ctx, &obj_stream, body);
			MAPI_RETVAL_IF(retval, GetLastError(), NULL);

			mapi_object_release(&obj_stream);
		}			
		break;
	case olEditorRTF:
		mapi_object_init(&obj_stream);

		retval = OpenStream(obj_message, PR_RTF_COMPRESSED, 0, &obj_stream);
		MAPI_RETVAL_IF(retval, GetLastError(), NULL);

		retval = WrapCompressedRTFStream(&obj_stream, body);
		MAPI_RETVAL_IF(retval, GetLastError(), NULL);

		mapi_object_release(&obj_stream);
		break;
	default:
		DEBUG(0, ("Undefined Body\n"));
		break;
	}

	return MAPI_E_SUCCESS;
}