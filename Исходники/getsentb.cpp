/* *********************************************************************** */
int NPSL_GetServByPortBasic(int serv_port, const char *serv_proto,
	NPSL_SERVENT *serv_ent_ptr, void *serv_ent_buffer_ptr,
	unsigned int serv_ent_buffer_length, unsigned int *required_length,
	char *error_text)
{
	int           return_code = NPSL_SUCCESS;
	NPSL_SERVENT *tmp_ent_ptr;

	if (required_length != NULL)
		*required_length = 0;

	if ((serv_proto != NULL) && (!(*serv_proto))) {
		if (error_text != NULL)
			strcpy(error_text,
		"The 'serv_proto' parameter is not 'NULL', but is an empty string.");
		return_code = NPSL_FAILURE;
	}
	else if ((return_code = NPSL_CheckServEntParams(serv_ent_ptr,
		serv_ent_buffer_ptr, serv_ent_buffer_length, error_text)) !=
		NPSL_SUCCESS)
		;
	else {
		int tmp_port = COMPAT_CAST_static(int,
			ntohs(COMPAT_CAST_static(unsigned short, serv_port)));
#if NPSL_HAS_GETSERVBYPORT_R
		if ((tmp_ent_ptr = getservbyport_r(tmp_port, serv_proto,
			serv_ent_ptr, serv_ent_buffer_ptr,
			((int) serv_ent_buffer_length))) == NULL) {
			if (error_text != NULL) {
				sprintf(error_text,
					"%s '%s()' for service port '%d', protocol '%-.127s': ",
					"Unable to get service entry with", "getservbyport_r",
					serv_port, (serv_proto != NULL) ? serv_proto : "*NULL*");
				NPSL_AppendLastErrorString(0, NPSL_MAX_ERROR_TEXT, error_text);
			}
			return_code = NPSL_SUPP_MapLastError();
		}
#else
		if ((tmp_ent_ptr = getservbyport(tmp_port, serv_proto)) == NULL) {
			if (error_text != NULL) {
				sprintf(error_text,
					"%s '%s()' for service port '%d', protocol '%-.127s': ",
					"Unable to get service entry with", "getservbyport",
					serv_port, (serv_proto != NULL) ? serv_proto : "*NULL*");
				NPSL_AppendLastErrorString(0, NPSL_MAX_ERROR_TEXT, error_text);
			}
			return_code = NPSL_SUPP_MapLastError();
		}
		else
			return_code = NPSL_CopyServEntFlatBasic(tmp_ent_ptr, serv_ent_ptr,
				serv_ent_buffer_ptr, serv_ent_buffer_length, required_length,
				error_text);
#endif // #if NPSL_HAS_GETSERVBYPORT_R
	}

	return(return_code);
}