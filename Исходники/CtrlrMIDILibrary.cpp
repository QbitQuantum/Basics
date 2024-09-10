ValueTree CtrlrMIDILibrary::scanChildrenForMenuIndex(ValueTree item, int itemIndexToFind, int &currentIndex)
{
	_DBG("CtrlrMIDILibrary::scanChildrenForMenuIndex");
	if (isContainer (item))
	{
		_DBG("\tcontainer ["+item.getType().toString()+"]");
		ValueTree child;

		for (int topLevelIndex=0; topLevelIndex<item.getNumChildren(); topLevelIndex++)
		{
			child = scanChildrenForMenuIndex (item.getChild(topLevelIndex), itemIndexToFind, currentIndex);

			if (child.isValid())
			{
				_DBG("\t\tvalid child found ["+child.getType().toString()+"] parent:["+child.getParent().getType().toString()+"]");
				return (child);
			}

			currentIndex++;
		}
	}

	if (itemIndexToFind == currentIndex)
	{
		_DBG("\t\titemIndexToFind == currentIndex ["+item.getType().toString()+"]");
		return (item);
	}
	else
	{
		return (ValueTree());
	}
}