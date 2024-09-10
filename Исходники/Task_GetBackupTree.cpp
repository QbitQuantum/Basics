PRL_RESULT Task_GetBackupTreeSource::prepareTask()
{
	PRL_RESULT ret = PRL_ERR_SUCCESS;
	try {
		if ((m_nFlags & (PBT_BACKUP_ID | PBT_CHAIN)) && m_sUuid.isEmpty()) {
			WRITE_TRACE(DBG_FATAL, "A backup UUID must be specified to get information "
								   "on a single backup or backup chain.");
			throw PRL_ERR_INVALID_PARAM;
		}
		if ((m_nFlags & PBT_BACKUP_ID) && (m_nFlags & PBT_CHAIN)) {
			WRITE_TRACE(DBG_FATAL, "The PBT_BACKUP_ID and PBT_CHAIN flags are mutually exclusive.");
			throw PRL_ERR_INVALID_PARAM;
		}
	} catch (PRL_RESULT code) {
		getLastError()->setEventCode(code);
		ret = code;
		WRITE_TRACE(DBG_FATAL, "An error occurred while preparing to get the backup tree [%#x][%s]",
			code, PRL_RESULT_TO_STRING(code));
	}

	return ret;
}