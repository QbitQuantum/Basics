	bool GetProcessIntegrityLevel(ProcessHandle process, IntegrityLevel *level) {
		if (!level)
			return false;

		if (win::GetVersion() < base::win::VERSION_VISTA)
			return false;

		HANDLE process_token;
		if (!OpenProcessToken(process, TOKEN_QUERY | TOKEN_QUERY_SOURCE,
			&process_token))
			return false;

		win::ScopedHandle scoped_process_token(process_token);

		DWORD token_info_length = 0;
		if (GetTokenInformation(process_token, TokenIntegrityLevel, NULL, 0,
			&token_info_length) ||
			GetLastError() != ERROR_INSUFFICIENT_BUFFER)
			return false;

		scoped_ptr<char[]> token_label_bytes(new char[token_info_length]);
		if (!token_label_bytes.get())
			return false;

		TOKEN_MANDATORY_LABEL* token_label =
			reinterpret_cast<TOKEN_MANDATORY_LABEL*>(token_label_bytes.get());
		if (!token_label)
			return false;

		if (!GetTokenInformation(process_token, TokenIntegrityLevel, token_label,
			token_info_length, &token_info_length))
			return false;

		DWORD integrity_level = *GetSidSubAuthority(token_label->Label.Sid,
			(DWORD)(UCHAR)(*GetSidSubAuthorityCount(token_label->Label.Sid) - 1));

		if (integrity_level < SECURITY_MANDATORY_MEDIUM_RID) {
			*level = LOW_INTEGRITY;
		}
		else if (integrity_level >= SECURITY_MANDATORY_MEDIUM_RID &&
			integrity_level < SECURITY_MANDATORY_HIGH_RID) {
			*level = MEDIUM_INTEGRITY;
		}
		else if (integrity_level >= SECURITY_MANDATORY_HIGH_RID) {
			*level = HIGH_INTEGRITY;
		}
		else {
			NOTREACHED();
			return false;
		}

		return true;
	}