CIMInstance UNIX_BatteryProvider::constructInstance(
	const CIMName &className,
	const CIMNamespaceName &nameSpace,
	const UNIX_Battery &_p)
{
	CIMProperty p;

	CIMInstance inst(className);

	// Set path
	inst.setPath(CIMObjectPath(String(""), // hostname
			nameSpace,
			CIMName("UNIX_Battery"),
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

	//CIM_Battery Properties
	if (_p.getBatteryStatus(p)) inst.addProperty(p);
	if (_p.getTimeOnBattery(p)) inst.addProperty(p);
	if (_p.getEstimatedRunTime(p)) inst.addProperty(p);
	if (_p.getEstimatedChargeRemaining(p)) inst.addProperty(p);
	if (_p.getChemistry(p)) inst.addProperty(p);
	if (_p.getDesignCapacity(p)) inst.addProperty(p);
	if (_p.getFullChargeCapacity(p)) inst.addProperty(p);
	if (_p.getDesignVoltage(p)) inst.addProperty(p);
	if (_p.getSmartBatteryVersion(p)) inst.addProperty(p);
	if (_p.getTimeToFullCharge(p)) inst.addProperty(p);
	if (_p.getExpectedLife(p)) inst.addProperty(p);
	if (_p.getMaxRechargeTime(p)) inst.addProperty(p);
	if (_p.getRechargeCount(p)) inst.addProperty(p);
	if (_p.getMaxRechargeCount(p)) inst.addProperty(p);
	if (_p.getRemainingCapacity(p)) inst.addProperty(p);
	if (_p.getRemainingCapacityMaxError(p)) inst.addProperty(p);
	if (_p.getOtherChemistryDescription(p)) inst.addProperty(p);
	if (_p.getChargingStatus(p)) inst.addProperty(p);
	if (_p.getHealthPercent(p)) inst.addProperty(p);


	return inst;
}