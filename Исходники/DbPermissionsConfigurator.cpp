MojErr DbPermissionsConfigurator::ProcessConfig(const string& filePath, MojObject& permissions)
{
	LOG_TRACE("Entering function %s", __FUNCTION__);

	std::string owner;
	MojObject perms;

	owner = ParentId(filePath);
    MojErr err = perms.put("permissions", permissions);
    MojErrCheck(err);

	// for third-party packages, we set the appid on the service request
	// so that mojodb does things correctly.  root config files aren't split up
	// in a per-service/app directory way (though they should be like activitymanager)
	MojRefCountedPtr<MojServiceRequest> request;
	if (!owner.empty())
		request = m_busClient.CreateRequest(owner.c_str());
	else
		request = m_busClient.CreateRequest();
	return request->send(CreateCallback(filePath)->m_slot, ServiceName(), MOJODB_PUTPERMISSIONS_METHOD, perms);
}