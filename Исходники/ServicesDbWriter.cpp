void ServicesDbWriter::writePartial(const shared_ptr<const Node>& n)
{
  bool countChange = true;

  //LOG_DEBUG("Inside writePartial for Node");

  Tags t = n->getTags();
  // Only add tags for servicesDB, not good for OSM API
  if ( _sdb.getDatabaseType() == ServicesDb::DBTYPE_SERVICES)
  {
    _addElementTags(n, t);
  }

  //LOG_DEBUG("Incoming node ID: " << n->getId());


  if (_remapIds)
  {
    bool alreadyThere = _nodeRemap.count(n->getId()) != 0;
    LOG_VARD(alreadyThere);
    long nodeId = _getRemappedElementId(n->getElementId());
    if (alreadyThere)
    {
      _sdb.updateNode(nodeId, n->getY(), n->getX(), n->getVersion() + 1, t);
    }
    else
    {
      _sdb.insertNode(nodeId, n->getY(), n->getX(), t);
    }
  }
  else
  {
    if ( n->getId() < 1 )
    {
      throw HootException("Writing non-positive IDs without remap is not supported by "
                          "ServicesDbWriter.");
    }

    //LOG_DEBUG("Inserted node " << QString::number(n->getId()) << ", no remapping" );
    _sdb.insertNode(n->getId(), n->getY(), n->getX(), t);
  }

  if (countChange)
  {
    _countChange();
    _nodesWritten++;
  }
}