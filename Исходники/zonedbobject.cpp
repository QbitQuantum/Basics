Dictionary::Ptr ZoneDbObject::GetStatusFields() const
{
	Zone::Ptr zone = static_pointer_cast<Zone>(GetObject());

	Log(LogDebug, "ZoneDbObject")
		<< "update status for zone '" << zone->GetName() << "'";

	return new Dictionary({
		{ "parent_zone_object_id", zone->GetParent() }
	});
}