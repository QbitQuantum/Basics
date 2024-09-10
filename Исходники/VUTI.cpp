bool VUTI::IsChild(VUTI * inUTI)
{
	if(!testAssert(inUTI != NULL))
		return false;
	
	bool isChild = false;
	std::map< VString, VUTI * >::iterator childUTIsIterator = fChildrenUTIsMap.begin();
	while(childUTIsIterator != fChildrenUTIsMap.end()){
		VUTI * childUTI = childUTIsIterator->second;
		//Exclude temporary values from the process
		if(!childUTI->IsTemporary()){
			isChild |= VUTIManager::GetUTIManager()->UTTypeEqual(inUTI->GetIdentifier(), childUTI->GetIdentifier());
			if(isChild)
				break;
			isChild |= childUTI->IsChild(inUTI);
			if(isChild)
				break;
		}
		++childUTIsIterator;
	}
	return isChild;
}