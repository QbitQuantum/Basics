unsigned khlist_set(struct khlist *hl, const char *str, void *ud){
	unsigned hash = _hash_string(str, HASH_OFFSET);
	unsigned hasha = _hash_string(str, HASH_A);
	unsigned hashb = _hash_string(str, HASH_B);
	unsigned hash_start = hash % hl->size;

	unsigned npos = hash_start;

	while (hl->hash_t[npos].exist == 1){
		if (hl->hash_t[npos].hasha == hasha && hl->hash_t[npos].hashb == hashb)
			return -1;
		npos = (npos + 1) % hl->size;
		if (npos == hash_start){
			if (_expand(hl) == NULL) return -1;
			return khlist_set(hl, str, ud);
		}
	}
	hl->hash_t[npos].exist = 1;
	hl->hash_t[npos].hasha = hasha;
	hl->hash_t[npos].hashb = hashb;
	hl->hash_t[npos].ud = ud;
	return npos;
}