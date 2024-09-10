void GBindingPool::glueDataAdded(const GAccessibleGlueDataPointer & glueData)
{
	const AccessibleKey key = AccessibleKey(objectAddressFromVariant(glueData->getInstance()), glueData->getAccessible());
	this->accessibleMap[key] = GWeakAccessibleGlueDataPointer(glueData);
}