void RACHL1Decoder::writeLowSide(const RxBurst& burst)
{
	// The L1 FEC for the RACH is defined in GSM 05.03 4.6.

	// Decode the burst.
	const SoftVector e(burst.segment(49,36));
	e.decode(mVCoder,mU);

	// To check validity, we have 4 tail bits and 6 parity bits.
	// False alarm rate for random inputs is 1/1024.

	// Check the tail bits -- should all the zero.
	if (mU.peekField(14,4)) {
		countBadFrame();
		return;
	}

	// Check the parity.
	// The parity word is XOR'd with the BSIC. (GSM 05.03 4.6.)
	unsigned sentParity = ~mU.peekField(8,6);
	unsigned checkParity = mD.parity(mParity);
	unsigned encodedBSIC = (sentParity ^ checkParity) & 0x03f;
	if (encodedBSIC != gBTS.BSIC()) {
		countBadFrame();
		return;
	}

	// We got a valid RACH burst.
	// The "payload" is an 8-bit field, "RA", defined in GSM 04.08 9.1.8.
	// The channel assignment procedure is in GSM 04.08 3.3.1.1.3.
	// It requires knowledge of the RA value and the burst receive time.
	// The RACH L2 is so thin that we don't even need code for it.
	// Just pass the required information directly to the control layer.

	countGoodFrame();
	mD.LSB8MSB();
	unsigned RA = mD.peekField(0,8);
	OBJLOG(INFO) <<"RACHL1Decoder received RA=" << RA << " at time " << burst.time()
		<< " with RSSI=" << burst.RSSI() << " timingError=" << burst.timingError();
	Control::AccessGrantResponder(RA,burst.time(),burst.RSSI(),burst.timingError());
}