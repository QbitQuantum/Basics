	uid_t YChatDB::addUser(const string& username, const string& password) {
		Storage* uind_store = get_user_index_table();
		Storage* user_store = get_user_table();
		if (uind_store == NULL || user_store == NULL) return 0;
		Transaction txn;
		uid_t uid = 0;
		try {
			if (!inc_and_get_curr_max_uid(uind_store, txn, uid)) {
				txn.abort();
				return 0;
			}
			OctetsStream key, value; 
			key << username, value << password << uid;
			uind_store->insert(key, value, txn);
			
			User user(uid, username);
			OctetsStream key2, value2;
			key2 << uid, value2 << user.toString();
			user_store->insert(key2, value2, txn);
		} catch (...) {
			txn.abort();
			return 0;
		}

		return uid;
	}