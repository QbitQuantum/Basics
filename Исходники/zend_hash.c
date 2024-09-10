/* 对哈希表进行重新哈希操作 */
ZEND_API int zend_hash_rehash(HashTable *ht)
{
	Bucket *p;
	uint nIndex;

	IS_CONSISTENT(ht);
	if (UNEXPECTED(ht->nNumOfElements == 0)) {
		return SUCCESS;
	}
	/* 先将arBuckets重新初始化为0 */
	memset(ht->arBuckets, 0, ht->nTableSize * sizeof(Bucket *));
	/* p指向pListHead，pListHead指向数组的第一个元素，保存这个指针在重新哈希的时候也非常有用
	 */
	p = ht->pListHead;
	while (p != NULL) {
		/* 逐个计算下标然后添加到相同哈希值的bucket中 */
		nIndex = p->h & ht->nTableMask;
		CONNECT_TO_BUCKET_DLLIST(p, ht->arBuckets[nIndex]);
		ht->arBuckets[nIndex] = p;
		p = p->pListNext;
	}
	return SUCCESS;
}