void
MPTerrainEngineNode::invalidateRegion(const GeoExtent& extent,
                                      unsigned         minLevel,
                                      unsigned         maxLevel)
{
    if (_terrainOptions.incrementalUpdate() == true && _liveTiles.valid())
    {
        GeoExtent extentLocal = extent;
        if ( !extent.getSRS()->isEquivalentTo(this->getMap()->getSRS()) )
        {
            extent.transform(this->getMap()->getSRS(), extentLocal);
        }
        
        _liveTiles->setDirty(extentLocal, minLevel, maxLevel);
    }
}