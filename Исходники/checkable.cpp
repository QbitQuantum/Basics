void Checkable::OnAllConfigLoaded()
{
	ObjectImpl<Checkable>::OnAllConfigLoaded();

	Endpoint::Ptr endpoint = GetCommandEndpoint();

	if (endpoint) {
		Zone::Ptr checkableZone = static_pointer_cast<Zone>(GetZone());

		if (checkableZone) {
			Zone::Ptr cmdZone = endpoint->GetZone();

			if (cmdZone != checkableZone && cmdZone->GetParent() != checkableZone) {
				BOOST_THROW_EXCEPTION(ValidationError(this, { "command_endpoint" },
					"Command endpoint must be in zone '" + checkableZone->GetName() + "' or in a direct child zone thereof."));
			}
		} else {
			BOOST_THROW_EXCEPTION(ValidationError(this, { "command_endpoint" },
				"Command endpoint must not be set."));
		}
	}
}