// port      - serial device name
// speed     - eg 9600 
// data_bits - typically 8 
// parity    - 'n', 'o', 'e', 'm', 's' 
// stop_bits -  1 or 2);
int SerialClass::OpenPort(const char* port, unsigned long speed, unsigned int data_bits, char parity, unsigned int stop_bits)
{
    strncpy(m_port, port, MAX_PORTNAME_LENGTH);
    m_speed     = speed;
    m_data_bits = data_bits;
    m_parity    = parity;
    m_stop_bits = stop_bits;  
    
	// open the port
    return OpenPort();
}