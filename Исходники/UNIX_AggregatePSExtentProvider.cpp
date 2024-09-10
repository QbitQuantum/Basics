CIMInstance UNIX_AggregatePSExtentProvider::constructInstance(
	const CIMName &className,
	const CIMNamespaceName &nameSpace,
	const UNIX_AggregatePSExtent &instanceObject) const
{
	CIMProperty p;

	CIMInstance inst(className);

	// Set path
	inst.setPath(CIMObjectPath(String(""), // hostname
			nameSpace,
			className,
			constructKeyBindings(instanceObject)));

	//CIM_ManagedElement Properties
	if (instanceObject.getInstanceID(p)) inst.addProperty(p);
	if (instanceObject.getCaption(p)) inst.addProperty(p);
	if (instanceObject.getDescription(p)) inst.addProperty(p);
	if (instanceObject.getElementName(p)) inst.addProperty(p);
	if (instanceObject.getGeneration(p)) inst.addProperty(p);
	if (className.equal("CIM_ManagedElement")) return inst;
	
	//CIM_ManagedSystemElement Properties
	if (instanceObject.getInstallDate(p)) inst.addProperty(p);
	if (instanceObject.getName(p)) inst.addProperty(p);
	if (instanceObject.getOperationalStatus(p)) inst.addProperty(p);
	if (instanceObject.getStatusDescriptions(p)) inst.addProperty(p);
	if (instanceObject.getStatus(p)) inst.addProperty(p);
	if (instanceObject.getHealthState(p)) inst.addProperty(p);
	if (instanceObject.getCommunicationStatus(p)) inst.addProperty(p);
	if (instanceObject.getDetailedStatus(p)) inst.addProperty(p);
	if (instanceObject.getOperatingStatus(p)) inst.addProperty(p);
	if (instanceObject.getPrimaryStatus(p)) inst.addProperty(p);
	if (className.equal("CIM_ManagedSystemElement")) return inst;
	
	//CIM_LogicalElement Properties
	if (className.equal("CIM_LogicalElement")) return inst;
	
	//CIM_EnabledLogicalElement Properties
	if (instanceObject.getEnabledState(p)) inst.addProperty(p);
	if (instanceObject.getOtherEnabledState(p)) inst.addProperty(p);
	if (instanceObject.getRequestedState(p)) inst.addProperty(p);
	if (instanceObject.getEnabledDefault(p)) inst.addProperty(p);
	if (instanceObject.getTimeOfLastStateChange(p)) inst.addProperty(p);
	if (instanceObject.getAvailableRequestedStates(p)) inst.addProperty(p);
	if (instanceObject.getTransitioningToState(p)) inst.addProperty(p);
	if (className.equal("CIM_EnabledLogicalElement")) return inst;
	
	//CIM_AllocatedLogicalElement Properties
	if (instanceObject.getAllocationState(p)) inst.addProperty(p);
	if (className.equal("CIM_AllocatedLogicalElement")) return inst;
	
	//CIM_LogicalDevice Properties
	if (instanceObject.getSystemCreationClassName(p)) inst.addProperty(p);
	if (instanceObject.getSystemName(p)) inst.addProperty(p);
	if (instanceObject.getCreationClassName(p)) inst.addProperty(p);
	if (instanceObject.getDeviceID(p)) inst.addProperty(p);
	if (instanceObject.getPowerManagementSupported(p)) inst.addProperty(p);
	if (instanceObject.getPowerManagementCapabilities(p)) inst.addProperty(p);
	if (instanceObject.getAvailability(p)) inst.addProperty(p);
	if (instanceObject.getStatusInfo(p)) inst.addProperty(p);
	if (instanceObject.getLastErrorCode(p)) inst.addProperty(p);
	if (instanceObject.getErrorDescription(p)) inst.addProperty(p);
	if (instanceObject.getErrorCleared(p)) inst.addProperty(p);
	if (instanceObject.getOtherIdentifyingInfo(p)) inst.addProperty(p);
	if (instanceObject.getPowerOnHours(p)) inst.addProperty(p);
	if (instanceObject.getTotalPowerOnHours(p)) inst.addProperty(p);
	if (instanceObject.getIdentifyingDescriptions(p)) inst.addProperty(p);
	if (instanceObject.getAdditionalAvailability(p)) inst.addProperty(p);
	if (instanceObject.getMaxQuiesceTime(p)) inst.addProperty(p);
	if (instanceObject.getLocationIndicator(p)) inst.addProperty(p);
	if (className.equal("CIM_LogicalDevice")) return inst;
	
	//CIM_StorageExtent Properties
	if (instanceObject.getDataOrganization(p)) inst.addProperty(p);
	if (instanceObject.getPurpose(p)) inst.addProperty(p);
	if (instanceObject.getAccess(p)) inst.addProperty(p);
	if (instanceObject.getErrorMethodology(p)) inst.addProperty(p);
	if (instanceObject.getBlockSize(p)) inst.addProperty(p);
	if (instanceObject.getNumberOfBlocks(p)) inst.addProperty(p);
	if (instanceObject.getConsumableBlocks(p)) inst.addProperty(p);
	if (instanceObject.getIsBasedOnUnderlyingRedundancy(p)) inst.addProperty(p);
	if (instanceObject.getSequentialAccess(p)) inst.addProperty(p);
	if (instanceObject.getExtentStatus(p)) inst.addProperty(p);
	if (instanceObject.getNoSinglePointOfFailure(p)) inst.addProperty(p);
	if (instanceObject.getDataRedundancy(p)) inst.addProperty(p);
	if (instanceObject.getPackageRedundancy(p)) inst.addProperty(p);
	if (instanceObject.getDeltaReservation(p)) inst.addProperty(p);
	if (instanceObject.getPrimordial(p)) inst.addProperty(p);
	if (instanceObject.getNameFormat(p)) inst.addProperty(p);
	if (instanceObject.getNameNamespace(p)) inst.addProperty(p);
	if (instanceObject.getOtherNameNamespace(p)) inst.addProperty(p);
	if (instanceObject.getOtherNameFormat(p)) inst.addProperty(p);
	if (instanceObject.getUsage(p)) inst.addProperty(p);
	if (instanceObject.getOtherUsageDescription(p)) inst.addProperty(p);
	if (instanceObject.getClientSettableUsage(p)) inst.addProperty(p);
	if (instanceObject.getExtentInterleaveDepth(p)) inst.addProperty(p);
	if (instanceObject.getExtentStripeLength(p)) inst.addProperty(p);
	if (instanceObject.getIsComposite(p)) inst.addProperty(p);
	if (instanceObject.getIsConcatenated(p)) inst.addProperty(p);
	if (instanceObject.getExtentDiscriminator(p)) inst.addProperty(p);
	if (instanceObject.getCompressionRate(p)) inst.addProperty(p);
	if (instanceObject.getCompressionState(p)) inst.addProperty(p);
	if (instanceObject.getIsCompressed(p)) inst.addProperty(p);
	if (className.equal("CIM_StorageExtent")) return inst;
	
	//CIM_AggregatePSExtent Properties
	

	return inst;
}