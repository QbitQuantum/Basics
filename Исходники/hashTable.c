/*
 * Check functions: it checks the presence of a chunk in the
 * hash table pointed by *as.
 *
 * It returns:	1 if the chunk exists
 * 				0 if not
 * */
int check(hashtable *as, uint32_t hash){
	char tmp[CHUNK];
	return as_leer(as, NORMALIZE(hash), &tmp);
}