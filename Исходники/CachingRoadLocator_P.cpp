void OsmAnd::CachingRoadLocator_P::clearCacheNotInBBox(const AreaI bbox31, const bool checkAlsoIntersection)
{
    clearCacheConditional(
        [bbox31, checkAlsoIntersection]
        (const std::shared_ptr<const ObfRoutingSectionReader::DataBlock>& dataBlock) -> bool
        {
            if (bbox31.contains(dataBlock->area31) || dataBlock->area31.contains(bbox31))
                return false;
            if (checkAlsoIntersection && bbox31.intersects(dataBlock->area31))
                return false;
            return true;
        });
}