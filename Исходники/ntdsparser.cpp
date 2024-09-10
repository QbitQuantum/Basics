/*
 * Parse NTDS.dit file and its "datatable" table
 * Lokk for PEK, SAM account name & type, hashes, SID and hashes history if asked
 */
BOOL NTDS_NTLM_ParseDatabase(s_parser *parser,ll_ldapAccountInfo *ldapAccountInfo,s_NTLM_pek_ciphered *pek_ciphered,BOOL with_history){
	s_ldapAccountInfo ldapAccountEntry;
	JET_TABLEID tableid;
	JET_ERR jet_err;
	int success = NTDS_SUCCESS;
	int retCode;

	jet_err = JetOpenTable(parser->sesid,parser->dbid,NTDS_TBL_OBJ,NULL,0,JET_bitTableReadOnly | JET_bitTableSequential,&tableid);
	if(jet_err!=JET_errSuccess) {
		NTDS_ErrorPrint(parser,"JetOpenTable",jet_err);
		return NTDS_API_ERROR;
	}

	/* Get attributes identifiers */
	jet_err = JetGetTableColumnInfo(parser->sesid,tableid,ATT_SAM_ACCOUNT_NAME,&parser->columndef[ID_SAM_ACCOUNT_NAME],sizeof(JET_COLUMNDEF),JET_ColInfo);
	jet_err |= JetGetTableColumnInfo(parser->sesid,tableid,ATT_OBJECT_SID,&parser->columndef[ID_OBJECT_SID],sizeof(JET_COLUMNDEF),JET_ColInfo);
	jet_err |= JetGetTableColumnInfo(parser->sesid,tableid,ATT_LM_HASH,&parser->columndef[ID_LM_HASH],sizeof(JET_COLUMNDEF),JET_ColInfo);
	jet_err |= JetGetTableColumnInfo(parser->sesid,tableid,ATT_NT_HASH,&parser->columndef[ID_NT_HASH],sizeof(JET_COLUMNDEF),JET_ColInfo);
	jet_err |= JetGetTableColumnInfo(parser->sesid,tableid,ATT_PEK,&parser->columndef[ID_PEK],sizeof(JET_COLUMNDEF),JET_ColInfo);
	jet_err |= JetGetTableColumnInfo(parser->sesid,tableid,ATT_SAM_ACCOUNT_TYPE,&parser->columndef[ID_SAM_ACCOUNT_TYPE],sizeof(JET_COLUMNDEF),JET_ColInfo);

	if(with_history) {
		jet_err |= JetGetTableColumnInfo(parser->sesid,tableid,ATT_LM_HASH_HISTORY,&parser->columndef[ID_LM_HASH_HISTORY],sizeof(JET_COLUMNDEF),JET_ColInfo);
		jet_err |= JetGetTableColumnInfo(parser->sesid,tableid,ATT_NT_HASH_HISTORY,&parser->columndef[ID_NT_HASH_HISTORY],sizeof(JET_COLUMNDEF),JET_ColInfo);
	}

	if(jet_err!=JET_errSuccess) {
		NTDS_ErrorPrint(parser,"JetGetTableColumnInfo ",jet_err);
		JetCloseTable(parser->sesid,tableid);
		return NTDS_API_ERROR;
	}

	/* Parse datatable for SAM accounts */
	jet_err = JetMove(parser->sesid,tableid,JET_MoveFirst,0);
	do{
		retCode = NTDS_NTLM_ParseSAMRecord(parser,tableid,&ldapAccountEntry,with_history);
		if(retCode==NTDS_SUCCESS) {
			if(!ldapAccountInfoNew(ldapAccountInfo,&ldapAccountEntry)) {
				puts("Fatal error: not enough memory!");
				return NTDS_MEM_ERROR;
			}
		}
		else if(retCode==NTDS_MEM_ERROR) {
			puts("Fatal error: not enough memory!");
			return retCode;
		}

	}while(JetMove(parser->sesid,tableid,JET_MoveNext,0) == JET_errSuccess);
	
	if(!*ldapAccountInfo)
		success = NTDS_EMPTY_ERROR;

	/* Parse datatable for ciphered PEK */
	jet_err = JetMove(parser->sesid,tableid,JET_MoveFirst,0);
	do{
		if(NTDS_NTLM_ParsePEKRecord(parser,tableid,pek_ciphered)==NTDS_SUCCESS) {
			success = NTDS_SUCCESS;
			break;
		}
	}while(JetMove(parser->sesid,tableid,JET_MoveNext,0) == JET_errSuccess);

	jet_err = JetCloseTable(parser->sesid,tableid);
	if(jet_err!=JET_errSuccess) {
		NTDS_ErrorPrint(parser,"JetCloseTable",jet_err);
		return NTDS_API_ERROR;
	}

	return success;
}