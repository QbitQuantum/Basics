SerialDevice::SerialDevice(std::string id, Poco::URI uri, bool *debug) : IODevice(id)
{
	this->uri = uri;
	this->debug = debug;

	this->baudRate = 9600;
	this->protocol = "8N1";
	this->serialPort = new ctb::SerialPort();

	// deserialize information
	if (uri.getScheme() != "opdi_com")
		throw Poco::InvalidArgumentException("Can't deserialize; schema is incorrect, expected 'opdi_com'");

	// split user information into name:password
	// assumption: ':' character does not appear in either part
	std::vector<std::string> parts;
	RegularExpression re("(.+):(.+)");
	re.split(uri.getUserInfo(), parts, 0);
	if ((parts.size() > 1) && (parts[1] != ""))
		setUser(parts[1]);
	if ((parts.size() > 2) && (parts[2] != ""))
		setPassword(parts[2]);

	if (uri.getHost() != "")
		comport = uri.getHost() + (uri.getPath() != "" ? "/" + uri.getPath() : "");
	else
		comport = uri.getPath();

	if (comport == "")
		throw Poco::InvalidArgumentException("Serial port must be specified");

	// TODO parse parameters, especially for name and PSK
	// name = uri.getHost();
}