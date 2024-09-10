bool SharePtrGraphOp::traverse(Node *root)
{
    if(!_includeSet.empty() && !_excludeSet.empty())
    {
        FFATAL(("SharePtrGraphOp : Setting both the includes and excludes"
                "is not allowed!\n"));
        return false;
    }

    _typeMap   .clear();
    _shareCount.clear();

    _totalTime   = 0.0f;
    _compareTime = 0.0f;

    Time startTime = getSystemTime();

    shareFC(root);

    _totalTime = getSystemTime() - startTime;

    // DEBUG
    SINFO << "SharePtrGraphOp::traverse: _totalTime: " << _totalTime
          << " _compareTime: " << _compareTime << "\n";
    SINFO << "SharePtrGraphOp::traverse: Unique containers by type:\n";

    FCTypeMapIt tmIt  = _typeMap.begin();
    FCTypeMapIt tmEnd = _typeMap.end  ();

    for(; tmIt != tmEnd; ++tmIt)
    {
        UInt32              typeId = tmIt->first;
        FieldContainerType *fcType = FieldContainerFactory::the()->findType(typeId);

        SINFO << "TypeId [" << typeId << "] [" << (fcType != NULL ? fcType->getCName() : "")
              << "] -- [" << tmIt->second.size() << "]\n";
    }

    SINFO << "SharePtrGraphOp::traverse: Shared containers by type:\n";

    ShareCountIt scIt  = _shareCount.begin();
    ShareCountIt scEnd = _shareCount.end  ();

    for(; scIt != scEnd; ++scIt)
    {
        UInt32              typeId = scIt->first;
        FieldContainerType *fcType = FieldContainerFactory::the()->findType(typeId);

        SINFO << "TypeId [" << typeId << "] [" << (fcType != NULL ? fcType->getCName() : "")
              << "] -- [" << scIt->second << "]\n";
    }

    SINFO << std::flush;

    _typeMap   .clear();
    _shareCount.clear();

    return true;
}