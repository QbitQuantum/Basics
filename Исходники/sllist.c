void sll_destroy(sSLList *list,bool freeData) {
	if(list == NULL)
		return;
	sll_clear(list,freeData);
	heapfree(list);
}