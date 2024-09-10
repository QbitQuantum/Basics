CIMInstance UNIX_CompositeExtentProvider::constructInstance(
	const CIMName &className,
	const CIMNamespaceName &nameSpace,
	const UNIX_CompositeExtent &_p)
{
	CIMProperty p;

	CIMInstance inst(className);

	// Set path
	inst.setPath(CIMObjectPath(String(""), // hostname
			nameSpace,
			CIMName("UNIX_CompositeExtent"),
			constructKeyBindings(_p)));

	//CIM_ManagedElement Properties
	if (_p.getInstanceID(p)) inst.addProperty(p);
	if (_p.getCaption(p)) inst.addProperty(p);
	if (_p.getDescription(p)) inst.addProperty(p);
	if (_p.getElementName(p)) inst.addProperty(p);

	//CIM_ManagedSystemElement Properties
	if (_p.getInstallDate(p)) inst.addProperty(p);
	if (_p.getName(p)) inst.addProperty(p);
	if (_p.getOperationalStatus(p)) inst.addProperty(p);
	if (_p.getStatusDescriptions(p)) inst.addProperty(p);
	if (_p.getStatus(p)) inst.addProperty(p);
	if (_p.getHealthState(p)) inst.addProperty(p);
	if (_p.getCommunicationStatus(p)) inst.addProperty(p);
	if (_p.getDetailedStatus(p)) inst.addProperty(p);
	if (_p.getOperatingStatus(p)) inst.addProperty(p);
	if (_p.getPrimaryStatus(p)) inst.addProperty(p);

	//CIM_LogicalElement Properties

	//CIM_EnabledLogicalElement Properties
	if (_p.getEnabledState(p)) inst.addProperty(p);
	if (_p.getOtherEnabledState(p)) inst.addProperty(p);
	if (_p.getRequestedState(p)) inst.addProperty(p);
	if (_p.getEnabledDefault(p)) inst.addProperty(p);
	if (_p.getTimeOfLastStateChange(p)) inst.addProperty(p);
	if (_p.getAvailableRequestedStates(p)) inst.addProperty(p);
	if (_p.getTransitioningToState(p)) inst.addProperty(p);

	//CIM_LogicalDevice Properties
	if (_p.getSystemCreationClassName(p)) inst.addProperty(p);
	if (_p.getSystemName(p)) inst.addProperty(p);
	if (_p.getCreationClassName(p)) inst.addProperty(p);
	if (_p.getDeviceID(p)) inst.addProperty(p);
	if (_p.getPowerManagementSupported(p)) inst.addProperty(p);
	if (_p.getPowerManagementCapabilities(p)) inst.addProperty(p);
	if (_p.getAvailability(p)) inst.addProperty(p);
	if (_p.getStatusInfo(p)) inst.addProperty(p);
	if (_p.getLastErrorCode(p)) inst.addProperty(p);
	if (_p.getErrorDescription(p)) inst.addProperty(p);
	if (_p.getErrorCleared(p)) inst.addProperty(p);
	if (_p.getOtherIdentifyingInfo(p)) inst.addProperty(p);
	if (_p.getPowerOnHours(p)) inst.addProperty(p);
	if (_p.getTotalPowerOnHours(p)) inst.addProperty(p);
	if (_p.getIdentifyingDescriptions(p)) inst.addProperty(p);
	if (_p.getAdditionalAvailability(p)) inst.addProperty(p);
	if (_p.getMaxQuiesceTime(p)) inst.addProperty(p);

	//CIM_StorageExtent Properties
	if (_p.getDataOrganization(p)) inst.addProperty(p);
	if (_p.getPurpose(p)) inst.addProperty(p);
	if (_p.getAccess(p)) inst.addProperty(p);
	if (_p.getErrorMethodology(p)) inst.addProperty(p);
	if (_p.getBlockSize(p)) inst.addProperty(p);
	if (_p.getNumberOfBlocks(p)) inst.addProperty(p);
	if (_p.getConsumableBlocks(p)) inst.addProperty(p);
	if (_p.getIsBasedOnUnderlyingRedundancy(p)) inst.addProperty(p);
	if (_p.getSequentialAccess(p)) inst.addProperty(p);
	if (_p.getExtentStatus(p)) inst.addProperty(p);
	if (_p.getNoSinglePointOfFailure(p)) inst.addProperty(p);
	if (_p.getDataRedundancy(p)) inst.addProperty(p);
	if (_p.getPackageRedundancy(p)) inst.addProperty(p);
	if (_p.getDeltaReservation(p)) inst.addProperty(p);
	if (_p.getPrimordial(p)) inst.addProperty(p);
	if (_p.getNameFormat(p)) inst.addProperty(p);
	if (_p.getNameNamespace(p)) inst.addProperty(p);
	if (_p.getOtherNameNamespace(p)) inst.addProperty(p);
	if (_p.getOtherNameFormat(p)) inst.addProperty(p);

	//CIM_CompositeExtent Properties
	if (_p.getExtentStripeLength(p)) inst.addProperty(p);
	if (_p.getExtentInterleaveDepth(p)) inst.addProperty(p);
	if (_p.getIsConcatenated(p)) inst.addProperty(p);


	return inst;
}