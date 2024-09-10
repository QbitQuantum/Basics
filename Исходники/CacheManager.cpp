void XMLObjectCache::foreignCacheStatus(GStringList *pDest)
{
	gthread_mutex_lock(&m_csForeign);

	GHashIterator iter(m_cacheForeign);
	
	GString strCacheEntry;
	while (iter())
	{
		DynamicXMLObject* pObject = (DynamicXMLObject*)iter++;
		if (pObject)
		{
			strCacheEntry += pObject->GetObjectType();
			strCacheEntry += "  ";
			strCacheEntry += pObject->GetObjectTag();
			strCacheEntry += "\n";
		}
		pDest->AddLast((const char *)strCacheEntry);
	}
	gthread_mutex_unlock(&m_csForeign);
}