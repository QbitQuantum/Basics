// delete contact from the list of secureIM users
void delContact(HANDLE hContact)
{
	pUinKey p = arClist.find((pUinKey)&hContact);
	if (p) {
		arClist.remove(p);

		cpp_delete_context(p->cntx); p->cntx = 0;
		mir_free(p->tmp);
		mir_free(p->msgSplitted);
		mir_free(p);
	}
}