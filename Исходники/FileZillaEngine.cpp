int CFileZillaEngine::Execute(const CCommand &command)
{
	if (command.GetId() != Command::cancel && IsBusy())
		return FZ_REPLY_BUSY;

	m_bIsInCommand = true;

	int res = FZ_REPLY_INTERNALERROR;
	switch (command.GetId())
	{
	case Command::connect:
		res = Connect(reinterpret_cast<const CConnectCommand &>(command));
		break;
	case Command::disconnect:
		res = Disconnect(reinterpret_cast<const CDisconnectCommand &>(command));
		break;
	case Command::cancel:
		res = Cancel(reinterpret_cast<const CCancelCommand &>(command));
		break;
	case Command::list:
		res = List(reinterpret_cast<const CListCommand &>(command));
		break;
	case Command::transfer:
		res = FileTransfer(reinterpret_cast<const CFileTransferCommand &>(command));
		break;
	case Command::raw:
		res = RawCommand(reinterpret_cast<const CRawCommand&>(command));
		break;
	case Command::del:
		res = Delete(reinterpret_cast<const CDeleteCommand&>(command));
		break;
	case Command::removedir:
		res = RemoveDir(reinterpret_cast<const CRemoveDirCommand&>(command));
		break;
	case Command::mkdir:
		res = Mkdir(reinterpret_cast<const CMkdirCommand&>(command));
		break;
	case Command::rename:
		res = Rename(reinterpret_cast<const CRenameCommand&>(command));
		break;
	case Command::chmod:
		res = Chmod(reinterpret_cast<const CChmodCommand&>(command));
		break;
	default:
		return FZ_REPLY_SYNTAXERROR;
	}

	if (res != FZ_REPLY_WOULDBLOCK)
		ResetOperation(res);

	m_bIsInCommand = false;

	if (command.GetId() != Command::disconnect)
		res |= m_nControlSocketError;
	else if (res & FZ_REPLY_DISCONNECTED)
		res = FZ_REPLY_OK;
	m_nControlSocketError = 0;

	return res;
}