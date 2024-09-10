/*
*	Gets handle from queue for request
*/
static MCONTACT amGetCurrentChain()
{
	mir_cslock lck(amCS);
	if (amItems.getCount() == 0)
		return NULL;

	MCONTACT res = (MCONTACT)amItems[0];
	amItems.remove(0);
	return res;
}