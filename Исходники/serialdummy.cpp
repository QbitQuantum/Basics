void CSerialDummy::transmitByte(Bit8u val, bool first) {

	if(first) setEvent(SERIAL_THR_EVENT, bytetime/10); 
	else setEvent(SERIAL_TX_EVENT, bytetime);

#ifdef CHECKIT_TESTPLUG
	loopbackdata=val;
#endif
}