/**
 *	makewordlistfromkey - Takes a public key and splits it into a set of 
 *                     unique words.
 *	@wordlist: The current word list.
 *	@key: The key to return the words from.
 *
 *	We take words and split it on non alpha numeric characters. These get
 *	added to the word list if they're not already present. If the wordlist
 *	is NULL then we start a new list, otherwise it's search for already
 *	added words. Note that words is modified in the process of scanning.
 *
 *	Returns the new word list.
 */
struct ll *makewordlistfromkey(struct ll *wordlist,
			       struct openpgp_publickey *key)
{
	char      **uids;
	int         i;
	struct ll  *words = NULL;
	struct ll  *wl = NULL;

	uids = keyuids(key, NULL);
	for (i = 0; uids != NULL && uids[i] != NULL; ++i) {
		words = makewordlist(NULL, uids[i]);
		for (wl = words; wl != NULL; wl = wl->next) {
			if (llfind(wordlist, wl->object, 
				(int (*)(const void *, const void *)) strcmp
						) == NULL) {
				wordlist = lladd(wordlist, strdup(wl->object));
			}
		}
		free(uids[i]);
		uids[i] = NULL;
	}
	free(uids);

	return wordlist;
}