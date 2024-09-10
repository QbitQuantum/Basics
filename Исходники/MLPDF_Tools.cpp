void fillFiberSetContainerFromPositionsAndConnections(FiberSetContainer& outFiberSetContainer, const XMarkerList& inLinePositions, const IndexPairList& inLineConnections)
{
  outFiberSetContainer.deleteAllFiberSets();

  std::set<int> typeIDsSet;
  std::map<int, int> numPositionsPerType;
  std::map<int, std::string> typeLabels;

  // Step 1: Scan all positions and get all type ID from them
  for (XMarkerList::const_iterator it = inLinePositions.cbegin(); it != inLinePositions.cend(); ++it)
  {
    XMarker thisMarker = *it;
    typeIDsSet.insert(thisMarker.type);
    numPositionsPerType[thisMarker.type]++;
    typeLabels[thisMarker.type] = thisMarker.name();
  }

  // Step 2: Now create fibers
  for (std::set<int>::const_iterator typeIdIterator = typeIDsSet.cbegin(); typeIdIterator != typeIDsSet.cend(); ++typeIdIterator)
  {
    int thisTypeID = *typeIdIterator;

    FiberSetContainer::FiberSet* newFiberSet = outFiberSetContainer.createFiberSet();
    newFiberSet->setColor(Vector3(1, 0, 0));
    newFiberSet->setLabel(typeLabels[thisTypeID]);

    // Add all connections to the temporary connections list if type ID matches
    XMarkerList  workPositions;
    for (XMarkerList::const_iterator outPositionsIterator = inLinePositions.cbegin(); outPositionsIterator != inLinePositions.cend(); ++outPositionsIterator)
    {
      XMarker thisMarker = *outPositionsIterator;

      if (thisMarker.type == thisTypeID)
      {
        workPositions.push_back(thisMarker);
      }
    }
    MLint workPositionsSize = (MLint)workPositions.size();

    // Add all connections to the temporary connections list if type ID matches
    IndexPairList workConnections;
    for (IndexPairList::const_iterator outConnectionsIterator = inLineConnections.cbegin(); outConnectionsIterator != inLineConnections.cend(); ++outConnectionsIterator)
    {
      IndexPair thisPair = *outConnectionsIterator;

      if (thisPair.type == thisTypeID)
      {
        workConnections.push_back(thisPair);
      }
    }

    // If temporary connections list is still empty at this point: create default list
    if (workConnections.size() == 0)
    {
      int numPositionsOfThisType = numPositionsPerType[thisTypeID];

      for (int p = 0; p < numPositionsOfThisType - 1; p++)
      {
        IndexPair thisPair(p, p + 1);
        workConnections.push_back(thisPair);
      }
    }

    // Now finally create fibers from connections
    for (IndexPairList::const_iterator workListIterator = workConnections.cbegin(); workListIterator != workConnections.cend(); ++workListIterator)
    {
      IndexPair thisWorkPair = *workListIterator;

      MLint startIndex = thisWorkPair.index1;
      MLint endIndex = thisWorkPair.index2;

      if ((startIndex < workPositionsSize) && (endIndex < workPositionsSize))
      {
        XMarker startMarker = workPositions[startIndex];
        XMarker endMarker = workPositions[endIndex];

        FiberSetContainer::FiberSet::Fiber* newFiber = newFiberSet->createFiber();

        FiberSetContainer::FiberSet::Fiber::FiberPoint startPoint;
        startPoint.setCoordinates(startMarker.x(), startMarker.y(), startMarker.z());
        FiberSetContainer::FiberSet::Fiber::FiberPoint endPoint;
        endPoint.setCoordinates(endMarker.x(), endMarker.y(), endMarker.z());

        newFiber->appendPoint(startPoint);
        newFiber->appendPoint(endPoint);
        newFiber->setLabel(1.0);
      }
    }

    workPositions.clearList();
    workConnections.clearList();
  }

}