/**
    When the "PropagateError" method is invoked, this function
    will read a CIM_Error embedded instance from the inParameters and use
    that instance to create an InstMethodIndication populating the Error[]
    property with the CIM_Error parameter and errorInstance stored in this
    class (if it's been created already). The output parameter of this method
    will contain the embedded instance received as input, and the newly
    created InstMethodIndication will be sent by the provider to any
    registered listeners.
*/
void EmbeddedInstanceProvider::invokeMethod(
        const OperationContext& context,
        const CIMObjectPath& objectReference,
        const CIMName& methodName,
        const Array<CIMParamValue>& inParameters,
        MethodResultResponseHandler& handler)
{
    // This should start sending indications with the stored Job instance
    // embedded in the InstMethodIndication
    handler.processing();
    if (!methodName.equal(CIMName("PropagateError")))
        throw CIMException(CIM_ERR_METHOD_NOT_AVAILABLE);

    if (inParameters.size() != 1)
    {
        throw CIMException(
            CIM_ERR_INVALID_PARAMETER, "Did not receive exactly 1 parameter");
    }

    CIMParamValue errorParam = inParameters[0];
    if (!String::equal(errorParam.getParameterName(), String("error")))
    {
        throw CIMException(
            CIM_ERR_INVALID_PARAMETER, "Did not find \"error\" parameter");
    }

    CIMInstance errorParamInst;
    errorParam.getValue().get(errorParamInst);
    if (errorParamInst.getPath().getClassName() != "PG_EmbeddedError")
    {
        throw CIMException(CIM_ERR_INVALID_PARAMETER);
    }
    errorParamInst.setPath(errorInstance->getPath());
    Array<CIMName> propList;
    for (unsigned int i = 0, n = errorParamInst.getPropertyCount(); i < n; i++)
    {
        propList.append(errorParamInst.getProperty(i).getName());
    }
    CIMInstance tmpErrorInstance(errorInstance->clone());
    if (!tmpErrorInstance.identical(errorParamInst))
    {
        throw Exception("Did not receive expected ErrorInstance");
    }

    // Build new indication instance
    CIMObjectPath indicationPath(System::getHostName(),
        CIMNamespaceName("test/EmbeddedInstance/Dynamic"),
        CIMName("PG_InstMethodIndication"));
    indicationInstance.reset(new CIMInstance("PG_InstMethodIndication"));
    indicationInstance->setPath(indicationPath);
    indicationInstance->addProperty(CIMProperty("MethodName",
        CIMValue(String("PropagateError"))));
    indicationInstance->addProperty(CIMProperty("PreCall",
        CIMValue(Boolean(false))));
    indicationInstance->addProperty(CIMProperty("SourceInstance",
        CIMValue(CIMObject(*errorInstance))));
    Array<CIMInstance> errorInstances;
    errorInstances.append(*errorInstance);
    errorInstances.append(*errorInstance);
    indicationInstance->addProperty(CIMProperty("Error",
        CIMValue(errorInstances)));

    handler.deliverParamValue(CIMParamValue(String("sameError"),
        CIMValue(errorParamInst)));
    handler.deliver(CIMValue(Uint32(1)));
    handler.complete();

    indicationHandler->deliver(*indicationInstance);
}