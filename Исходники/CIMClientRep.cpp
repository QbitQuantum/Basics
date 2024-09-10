void CIMClientRep::modifyInstance(
    const CIMNamespaceName& nameSpace,
    const CIMInstance& modifiedInstance,
    Boolean includeQualifiers,
    const CIMPropertyList& propertyList
)
{
    compareObjectPathtoCurrentConnection(modifiedInstance.getPath());
    AutoPtr<CIMRequestMessage> request(new CIMModifyInstanceRequestMessage(
                                           String::EMPTY,
                                           nameSpace,
                                           modifiedInstance,
                                           includeQualifiers,
                                           propertyList,
                                           QueueIdStack()));

    Message* message = _doRequest(request, CIM_MODIFY_INSTANCE_RESPONSE_MESSAGE);

    CIMModifyInstanceResponseMessage* response =
        (CIMModifyInstanceResponseMessage*)message;

    AutoPtr<CIMModifyInstanceResponseMessage> destroyer(response);
}