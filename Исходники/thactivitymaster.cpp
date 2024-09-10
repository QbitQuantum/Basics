void CSlavePartMapping::serializeMap(unsigned i, MemoryBuffer &mb, IGetSlaveData *extra)
{
    if (local)
        i = 0;
    if (i >= maps.ordinality())
    {
        mb.append((unsigned)0);
        return;
    }

    CSlaveMap &map = maps.item(i);
    unsigned nPos = mb.length();
    unsigned n=0;
    mb.append(n);
    UnsignedArray parts;
    ForEachItemIn(m, map)
        parts.append(map.item(m).queryPartIndex());
    MemoryBuffer extraMb;
    if (extra)
    {
        ForEachItemIn(m2, map)
        {
            unsigned xtraLen = 0;
            unsigned xtraPos = extraMb.length();
            extraMb.append(xtraLen);
            IPartDescriptor &partDesc = map.item(m2);
            if (!extra->getData(m2, partDesc.queryPartIndex(), extraMb))
            {
                parts.zap(partDesc.queryPartIndex());
                extraMb.rewrite(xtraPos);
            }
            else
            {
                xtraLen = (extraMb.length()-xtraPos)-sizeof(xtraLen);
                extraMb.writeDirect(xtraPos, sizeof(xtraLen), &xtraLen);
            }
        }
    }