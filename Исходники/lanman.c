uint16 _api_DosNetServerGetInfo(PCONN_HND phnd, io_struct * ps,
				uint16 sLevel,
				RCVBUF pbBuffer,
				RCVBUFLEN cbBuffer, uint16 *pcTotalAvail)
{
	SERVER_INFO_1 sv1;

	DEBUG(10,("DosNetServerGetInfo: %d buf %d\n",
				sLevel, cbBuffer));
	StrnCpy(sv1.sv1_name, local_machine, 16);
	strupper(sv1.sv1_name);
	sv1.sv1_version_major = 4;
	sv1.sv1_version_minor = 1;
	sv1.sv1_type = SV_TYPE_NT;

	sv1.sv1_comment_or_master_browser = string_truncate(lp_serverstring(),
					MAX_SERVER_STRING_LENGTH);

	switch (sLevel)
	{
		case 1:
		{
			if (!io_SERVER_INFO_1("sv1", ps, 0, &sv1,
						PARSE_SCALARS))
				return NERR_BufTooSmall;

			if (!io_SERVER_INFO_1("sv1", ps, 0, &sv1,
						PARSE_OFFSETS))
				return NERR_BufTooSmall;
			return ERRsuccess;
		}
	}
	return ERRunknownlevel;
}