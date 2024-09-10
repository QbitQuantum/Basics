serialCOM::~serialCOM()
{
	if (portisopen) ClosePort();
}