/**************************************************************************
 * Function: generateAccountHash
 * Description: returns the unique hash for the account.
 * ************************************************************************/ 
md_hash * generateAccountHash (Account * acct) {
	static md_hash ret;
	unsigned char * hashable;
	int data_length = 0, string_length = 0;
	
	MemSet(ret, sizeof(md_hash), 0);
	
	/* username, password, acct mod date, 
	 * pw mod date, and 256 bits of randomness */
	data_length = 
		StrLen(acct->username)+
		StrLen(acct->system)+
		StrLen(acct->password)+
		StrLen(acct->service)+
		StrLen(acct->comment)+
		sizeof(acct->account_mod_date)+
		sizeof(acct->password_mod_date)+
		(sizeof(Int16)*16)+1;
		
		
	if((hashable=MemPtrNew(data_length))) {
		MemSet(hashable, data_length, 0);
		StrCopy(hashable, acct->username);	
		string_length+=StrLen(acct->username);
		StrCat(hashable, acct->system);	
		string_length+=StrLen(acct->system);
		StrCat(hashable, acct->password);
		string_length+=StrLen(acct->password);	
		StrCat(hashable, acct->service);
		string_length+=StrLen(acct->service);	
		StrCat(hashable, acct->comment);
		string_length+=StrLen(acct->comment);	
		
		MemMove(hashable+string_length, 
			&acct->account_mod_date, 
			sizeof(acct->account_mod_date));
		string_length+=sizeof(acct->account_mod_date);
		
		MemMove(hashable+string_length, 
			&acct->password_mod_date, 				
			sizeof(acct->password_mod_date));
		string_length+=sizeof(acct->password_mod_date);
		
		/* move some randomness onto the end 
		 * to make dictionary attacks impossible.   */
		random_bytes(hashable+string_length, 32);
		string_length+=32;
		
		md_block(hashable, string_length, ret);	
		MemPtrFree(hashable);
	}	
	return &ret;
}