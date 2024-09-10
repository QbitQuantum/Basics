void NetService::onEvent(const omicronConnector::EventData& ed)
{
	Event* evt = mysInstance->writeHead();
	// NOTE: original event service id is substituted by NetService own service id.
	// This is made because in the local context, original service ids have no meaning, so all events are marked
	// as being originated from NetService.
	evt->reset((Event::Type)ed.type, (Service::ServiceType)ed.serviceType, ed.sourceId, mysInstance->getServiceId());
	evt->setPosition(ed.posx, ed.posy, ed.posz);
	evt->setOrientation(ed.orw, ed.orx, ed.ory, ed.orz);
	evt->setFlags(ed.flags);
	evt->setExtraData((Event::ExtraDataType)ed.extraDataType, ed.extraDataItems, ed.extraDataMask, (void*)ed.extraData);
}