int CVxParamMatrix::InitializeIO(vx_context context, vx_graph graph, vx_reference ref, const char * io_params)
{
	// save reference object and get object attributes
	m_vxObjRef = ref;
	m_matrix = (vx_matrix)m_vxObjRef;
	ERROR_CHECK(vxQueryMatrix(m_matrix, VX_MATRIX_ATTRIBUTE_TYPE, &m_data_type, sizeof(m_data_type)));
	ERROR_CHECK(vxQueryMatrix(m_matrix, VX_MATRIX_ATTRIBUTE_COLUMNS, &m_columns, sizeof(m_columns)));
	ERROR_CHECK(vxQueryMatrix(m_matrix, VX_MATRIX_ATTRIBUTE_ROWS, &m_rows, sizeof(m_rows)));
	ERROR_CHECK(vxQueryMatrix(m_matrix, VX_MATRIX_ATTRIBUTE_SIZE, &m_size, sizeof(m_size)));

	// process I/O parameters
	if (*io_params == ':') io_params++;
	while (*io_params) {
		char ioType[64], fileName[256];
		io_params = ScanParameters(io_params, "<io-operation>,<parameter>", "s,S", ioType, fileName);
		if (!_stricmp(ioType, "read"))
		{ // read request syntax: read,<fileName>[,ascii|binary]
			m_fileNameRead.assign(RootDirUpdated(fileName));
			m_fileNameForReadHasIndex = (m_fileNameRead.find("%") != m_fileNameRead.npos) ? true : false;
			m_readFileIsBinary = (m_fileNameRead.find(".txt") != m_fileNameRead.npos) ? false : true;
			while (*io_params == ',') {
				char option[64];
				io_params = ScanParameters(io_params, ",ascii|binary", ",s", option);
				if (!_stricmp(option, "ascii")) {
					m_readFileIsBinary = false;
				}
				else if (!_stricmp(option, "binary")) {
					m_readFileIsBinary = true;
				}
				else ReportError("ERROR: invalid matrix read option: %s\n", option);
			}
		}
		else if (!_stricmp(ioType, "write"))
		{ // write request syntax: write,<fileName>[,ascii|binary]
			m_fileNameWrite.assign(RootDirUpdated(fileName));
			m_writeFileIsBinary = (m_fileNameWrite.find(".txt") != m_fileNameWrite.npos) ? false : true;
			while (*io_params == ',') {
				char option[64];
				io_params = ScanParameters(io_params, ",ascii|binary", ",s", option);
				if (!_stricmp(option, "ascii")) {
					m_writeFileIsBinary = false;
				}
				else if (!_stricmp(option, "binary")) {
					m_writeFileIsBinary = true;
				}
				else ReportError("ERROR: invalid matrix write option: %s\n", option);
			}
		}
		else if (!_stricmp(ioType, "compare"))
		{ // compare request syntax: compare,<fileName>[,ascii|binary][,err{<tolerance>}]
			m_fileNameCompare.assign(RootDirUpdated(fileName));
			m_compareFileIsBinary = (m_fileNameCompare.find(".txt") != m_fileNameCompare.npos) ? false : true;
			while (*io_params == ',') {
				char option[64];
				io_params = ScanParameters(io_params, ",ascii|binary|err{<tolerance>}", ",s", option);
				if (!_stricmp(option, "ascii")) {
					m_compareFileIsBinary = false;
				}
				else if (!_stricmp(option, "binary")) {
					m_compareFileIsBinary = true;
				}
				else if (!_strnicmp(option, "err{", 4)) {
					ScanParameters(&option[3], "{<tolerance>}", "{f}", &m_errTolerance);
				}
				else ReportError("ERROR: invalid matrix compare option: %s\n", option);
			}
		}
		else if (!_stricmp(ioType, "init"))
		{ // write request syntax: init,{<value1>;<value2>;...<valueN>}
			NULLPTR_CHECK(m_bufForAccess = new vx_uint8[m_size]);
			vx_size index = 0; char fmt[3] = { '{', (m_data_type == VX_TYPE_FLOAT32) ? 'f' : 'd', 0 };
			for (const char * s = fileName; *s && index < (m_columns * m_rows); fmt[0] = ';', index++) {
				if (m_data_type == VX_TYPE_INT32 || m_data_type == VX_TYPE_UINT8) {
					vx_uint32 value;
					s = ScanParameters(s, "<value>", fmt, &value);
					if (m_data_type == VX_TYPE_UINT8) ((vx_uint8 *)m_bufForAccess)[index] = (vx_uint8)value;
					else ((vx_int32 *)m_bufForAccess)[index] = value;
				}
				else if (m_data_type == VX_TYPE_FLOAT32) {
					s = ScanParameters(s, "<value>", fmt, &((vx_float32 *)m_bufForAccess)[index]);
				}
				else ReportError("ERROR: matrix init option not support for data_type of %s\n", GetVxObjectName());
			}
			if (index < (m_columns * m_rows)) ReportError("ERROR: matrix init have too few values: %s\n", fileName);
			ERROR_CHECK(vxWriteMatrix(m_matrix, m_bufForAccess));
		}
		else if (!_stricmp(ioType, "directive") && !_stricmp(fileName, "readonly")) {
			ERROR_CHECK(vxDirective((vx_reference)m_matrix, VX_DIRECTIVE_AMD_READ_ONLY));
		}
		else if (!_stricmp(ioType, "ui") && !_strnicmp(fileName, "f", 1) && m_data_type == VX_TYPE_FLOAT32 && m_columns == 3 && m_rows == 3) {
			int id = 0;
			float valueR = 200.0f, valueInc = 0.5f;
			if (sscanf(&fileName[1], "%d,%g,%g", &id, &valueR, &valueInc) != 3) {
				printf("ERROR: invalid matrix UI configuration '%s'\n", fileName);
				return -1;
			}
			id--;
			GuiTrackBarInitializeMatrix((vx_reference)m_matrix, id, valueR, valueInc);
			GuiTrackBarProcessKey(0); // just initialize the matrix
		}
		else ReportError("ERROR: invalid matrix operation: %s\n", ioType);
		if (*io_params == ':') io_params++;
		else if (*io_params) ReportError("ERROR: unexpected character sequence in parameter specification: %s\n", io_params);
	}

	return 0;
}