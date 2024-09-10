void CHuiFxEffectCache::Remove(RArray<IDNode> &aMap, MHuiFxEffectCacheNode *aNode)
    {
    TInt size = aMap.Count();
    for(TInt i=0;i<size;i++)
        {
        const IDNode &n = aMap[i];
        if (n.iNode == aNode)
            {
            aMap.Remove(i);
            return;
            }
        }
    }