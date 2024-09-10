/*
 * Because there are times when it's useful to have a nice
 * human-readable form of the contents of this instance. Most of the
 * time this means that it's used for debugging, but it could be used
 * for just about anything. In these cases, it's nice not to have to
 * worry about the ownership of the representation, so this returns
 * a CKString.
 */
CKString CKIRCProtocol::toString() const
{
	CKString	retval = "< IRC Host=";
	retval += getHostname();
	retval += ", ";
	retval += " IRC Port=";
	retval += getPort();
	retval += ", ";
	retval += " CommPort=";
	retval += mCommPort.toString();
	retval += ", ";
	retval += " isLoggedIn? ";
	retval += (isLoggedIn() ? "Yes" : "No");
	retval += ", ";
	retval += " Password="******" Nickname=";
	retval += getNickname();
	retval += " UserHost=";
	retval += getUserHost();
	retval += " UserServer=";
	retval += getUserServer();
	retval += " RealName=";
	retval += getRealName();
	retval += " ChannelList: [";
	CKStringNode		*i = NULL;
	for (i = mChannelList.getHead(); i != NULL; i = i->getNext()) {
		if (i->getPrev() != NULL) {
			retval += ", ";
		}
		retval += (*i);
	}
	retval += "]>\n";

	return retval;
}