wxmailto_status PasswordManager::GetSudoPassword(SafeString& password)
{
	wxmailto_status status;

	SafeString salt;
	if (ID_OK!=(status=salt.StrDup(SUDO_SALT)))
		return status;
	
	return GenericDecrypt(m_encrypted_sudo_password_hex, salt, password);
}