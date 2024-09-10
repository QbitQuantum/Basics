void MdQextSerialCom::togglePort()
{
    if ( port ) {
        if ( port->isOpen() )
            closePort();
        else {
            openPort();
        }
    } else {
        setupPort();
    }
}