List linklistAdd2(List l1, List l2)
{
	// construct two lists so that they have the same length
	int len1 = l1.length();
	int len2 = l2.length();
	if (len1 > len2)
	{
		zeroPadding(l2,(len1-len2));	
	}
	else if(len1 < len2)
	{
		zeroPadding(l1,(len2-len1));
	}

	// add the two list by rescur
	int carray = 0;
	LNode* res = addHelper(l1.getHead()->next,l2.getHead()->next,carray);

	// construct the last result list
	List result;
	result.setHead(res);
	
	LNode *ta = res;
	while(ta->next != NULL)
	{
		ta = ta->next;
	}
	result.setTail(ta);
	if (carray != 0)
	{
		result.insertToHead(carray);
	}
	return result;
}