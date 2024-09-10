bool CDDELink::ParseLink(const tstring& link, tstring& service, tstring& topic, tstring& item)
{
	size_t serviceBegin = 0;
	size_t serviceEnd = link.find_first_of('|', serviceBegin);

	if ( (serviceEnd == tstring::npos) || (serviceEnd == serviceBegin) )
		return false;

	size_t topicBegin = serviceEnd + 1;
	size_t topicEnd = link.find_first_of('!', topicBegin);

	if ( (topicEnd == tstring::npos) || (topicEnd == topicBegin) )
		return false;

	size_t itemBegin = topicEnd + 1;
	size_t itemEnd = link.length();

	if (itemEnd == itemBegin)
		return false;

	service = link.substr(serviceBegin, serviceEnd - serviceBegin);
	topic   = link.substr(topicBegin,   topicEnd   - topicBegin);
	item    = link.substr(itemBegin,    itemEnd    - itemBegin);

	ASSERT(service.length() != 0);
	ASSERT(topic.length() != 0);
	ASSERT(item.length() != 0);

	return true;
}