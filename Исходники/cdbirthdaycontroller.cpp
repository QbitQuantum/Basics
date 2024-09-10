void
CDBirthdayController::fetchTrackerIds()
{
    // keep in sync with the enum in the header and NTrackerIds
    const QList<ResourceValue> resources = QList<ResourceValue>()
                                           << nco::birthDate::resource()
                                           << rdf::type::resource()
                                           << nco::PersonContact::resource()
                                           << nco::ContactGroup::resource();

    Select select;

    foreach (const ResourceValue &value, resources) {
        select.addProjection(Functions::trackerId.apply(value));
    }