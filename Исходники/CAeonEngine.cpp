void CAeonEngine::MsgCreateTable (const SArchonMessage &Msg, const CHexeSecurityCtx *pSecurityCtx)

//	MsgCreateTable
//
//	Aeon.createTable {tableDesc}
//
//	{tableDesc} = { name:MyTable1 type:standard x:{keyType:utf8} y:{keyType:int32} z:{keyType:dateTime} }

	{
	CString sError;

	//	Get the table desc and table name

	CDatum dTableDesc = Msg.dPayload.GetElement(0);
	const CString &sTable = dTableDesc.GetElement(FIELD_NAME);

	//	Make sure we are allowed access to this table

	if (!ValidateTableAccess(Msg, pSecurityCtx, sTable))
		return;

	//	See if the table descriptor specifies storage volumes; if so, then we
	//	make sure that the calling service has admin rights.

	if (!dTableDesc.GetElement(FIELD_PRIMARY_VOLUME).IsNil()
			|| !dTableDesc.GetElement(FIELD_BACKUP_VOLUMES).IsNil())
		{
		if (!ValidateAdminAccess(Msg, pSecurityCtx))
			return;
		}

	//	Create

	bool bExists;
	if (!CreateTable(dTableDesc, NULL, &bExists, &sError))
		{
		if (bExists)
			SendMessageReplyError(MSG_ERROR_ALREADY_EXISTS, sError, Msg);
		else
			SendMessageReplyError(MSG_ERROR_UNABLE_TO_COMPLY, sError, Msg);
		return;
		}

	//	Done

	SendMessageReply(MSG_OK, CDatum(), Msg);
	}