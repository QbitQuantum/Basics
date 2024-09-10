/* *********************************************************************** */
int NPSL_GetProtoByNumberBasic(int proto_number, NPSL_PROTOENT *proto_ent_ptr,
	void *proto_ent_buffer_ptr, unsigned int proto_ent_buffer_length,
	unsigned int *required_length, char *error_text)
{
	int            return_code = NPSL_SUCCESS;
	NPSL_PROTOENT *tmp_ent_ptr;

	if (required_length != NULL)
		*required_length = 0;

	if ((return_code = NPSL_CheckProtoEntParams(proto_ent_ptr,
		proto_ent_buffer_ptr, proto_ent_buffer_length, error_text)) !=
		NPSL_SUCCESS)
		;
	else {
#if NPSL_HAS_GETPROTOBYPORT_R
		if ((tmp_ent_ptr = getprotobynumber_r(proto_number, proto_ent_ptr,
			proto_ent_buffer_ptr, ((int) proto_ent_buffer_length))) == NULL) {
			if (error_text != NULL) {
				sprintf(error_text,
					"%s '%s()' for protocol number '%d': ",
					"Unable to get protocol entry with", "getprotobynumber_r",
					proto_number);
				NPSL_AppendLastErrorString(0, NPSL_MAX_ERROR_TEXT, error_text);
			}
			return_code = NPSL_SUPP_MapLastError();
		}
#else
		if ((tmp_ent_ptr = getprotobynumber(proto_number)) == NULL) {
			if (error_text != NULL) {
				sprintf(error_text,
					"%s '%s()' for protocol number '%d': ",
					"Unable to get protocol entry with", "getprotobynumber",
					proto_number);
				NPSL_AppendLastErrorString(0, NPSL_MAX_ERROR_TEXT, error_text);
			}
			return_code = NPSL_SUPP_MapLastError();
		}
		else
			return_code = NPSL_CopyProtoEntFlatBasic(tmp_ent_ptr, proto_ent_ptr,
				proto_ent_buffer_ptr, proto_ent_buffer_length, required_length,
				error_text);
#endif // #if NPSL_HAS_GETPROTOBYPORT_R
	}

	return(return_code);
}