void CSerialModem::handleUpperEvent(Bit16u type) {
	switch (type) {
	case SERIAL_RX_EVENT: {
		// check for bytes to be sent to port
		if(CSerial::CanReceiveByte())
			if(rqueue->inuse() && (CSerial::getRTS()||(flowcontrol!=3))) {
				Bit8u rbyte = rqueue->getb();
				//LOG_MSG("Modem: sending byte %2x back to UART3",rbyte);
				CSerial::receiveByte(rbyte);
			}
		if(CSerial::CanReceiveByte()) setEvent(SERIAL_RX_EVENT, bytetime*0.98f);
		break;
	}
	case MODEM_TX_EVENT: {
		if (tqueue->left()) {
			tqueue->addb(waiting_tx_character);
			if (tqueue->left() < 2) {
				CSerial::setCTS(false);
			}
		} else {
			static Bits lcount=0;
			if (lcount<1000) {
				lcount++;
				LOG_MSG("MODEM: TX Buffer overflow!");
			}
		}
		ByteTransmitted();
		break;
	}
	case SERIAL_POLLING_EVENT: {
		if (rqueue->inuse()) {
			removeEvent(SERIAL_RX_EVENT);
			setEvent(SERIAL_RX_EVENT, (float)0.01);
		}
		Timer2();
		setEvent(SERIAL_POLLING_EVENT,1);
		break;
	}

	case MODEM_RING_EVENT: {
		break;
	}
	}
}