// WARNING: This func runs in a separate thread.
void PDCHL1Uplink::writeLowSideRx(const RxBurst &inBurst)
{
	float low, avg = inBurst.getEnergy(&low);
	//if (avg > 0.7) { OBJLOG(DEBUG) << "PDCHL1Uplink " << inBurst; }

	//ScopedLock lock(testlock);
	int burstfn = inBurst.time().FN();
	int mfn = (burstfn / 13);			// how many 13-multiframes
	int rem = (burstfn - (mfn*13));	// how many blocks within the last multiframe.
	int B = rem % 4;

	if (avg > 0.5) { GPRSLOG(256) << "FEC:"<<LOGVAR(B)<<" "<<inBurst<<LOGVAR(avg); }

	ChannelCodingType cc;
	BitVector *result = decodeLowSide(inBurst,B,mchCS14Dec,&cc);

	if (B == 3) {
		int burst_fn=burstfn-3;	// First fn in rlc block.
		RLCBSN_t bsn = FrameNumber2BSN(burst_fn);

		if (GPRSDebug) {
			PDCHL1FEC *pdch = parent();
			short *qbits = mchCS14Dec.qbits;
			BitVector cshead(mchCS14Dec.mC.head(12).sliced());

			RLCBlockReservation *res = mchParent->getReservation(bsn);
			int thisUsf = pdch->getUsf(bsn-2);
			// If we miss a reservation or usf, print it:
			int missedRes = avg>0.4 && !result && (res||thisUsf);
			if (missedRes || (GPRSDebug & (result?4:256))) {
				std::ostringstream ss;
				char buf[30];
			 	ss <<"writeLowSideRx "<<parent()
					<<(result?" === good" : "=== bad")
					<< (res?" res:" : "") <<(res ? res->str() : "")
					//<<LOGVAR(cshead)
					//<<LOGVAR2("cs",(int)mchCS14Dec.getCS())
					<<LOGVAR(cc)
					<<LOGVAR2("revusf",decodeUSF(mchCS14Dec.mC))
					<<LOGVAR(burst_fn)<<LOGVAR(bsn) 
					<<LOGVAR2("RSSI",inBurst.RSSI()) <<LOGVAR2("TE",inBurst.timingError())
					// But lets print out the USFs bracketing this on either side.
					<<getAnsweringUsfText(buf,bsn)
					//<<" AnsweringUsf="<<pdch->getUsf(bsn-2)<<" "<<pdch->getUsf(bsn-1)
					//<<" ["<<pdch->getUsf(bsn)<<"] "<<pdch->getUsf(bsn+1)<<" "<<pdch->getUsf(bsn+2)
					<<" qbits="<<qbits[0]<<qbits[1]<<qbits[2]<<qbits[3]
							   <<qbits[4]<<qbits[5]<<qbits[6]<<qbits[7]
					<<LOGVAR(low)<<LOGVAR(avg)
					;
				if (missedRes) {
					for (int i = 0; i < 4; i++) {
						// There was an unanswered reservation or usf.
						avg = mchCS14Dec.mI[i].getEnergy(&low);
						GPRSLOG(1) << "energy["<<i<<"]:"<<LOGVAR(avg)<<LOGVAR(low)<<" "
							<<mchCS14Dec.mI[i];
					}
				}
				GLOG(DEBUG)<<ss.str();
				// Make sure we see a decoder failure if it reoccurs.
				if (missedRes) std::cout <<ss.str() <<"\n";
			}
		} // if GPRSDebug

		if (result) {
			// Check clock skew for debugging purposes.
			static int cnt = 0;
			if (bsn >= gBSNNext-1) {
				if (cnt++ % 32 == 0) {
					GLOG(ERR) << "Incoming burst at frame:"<<burst_fn
						<<" is not sufficiently ahead of clock:"<<gBSNNext.FN();
					if (GPRSDebug) {
					std::cout << "Incoming burst at frame:"<<burst_fn
						<<" is not sufficiently ahead of clock:"<<gBSNNext.FN()<<"\n";
					}
				}
			}

			countGoodFrame();

			// The four frame radio block has been decoded and is in mD.
			if (gConfig.getBool("Control.GSMTAP.GPRS")) {
				// Send to GSMTAP.  Untested.
				gWriteGSMTAP(ARFCN(),TN(),gBSNNext.FN(), //GSM::TDMA_PACCH,
						frame2GsmTapType(*result),
						false,	// not SACCH
						true,	// this is an uplink.
						*result);	// The data.
			}

			mchUplinkData.write(new RLCRawBlock(bsn,*result,inBurst.RSSI(),inBurst.timingError(),cc));
		} else {
			countBadFrame();
		}
	} else {
		// We dont have a full 4 bursts yet, and we rarely care about these
		// intermediate results, but here is a way to see them:
		GPRSLOG(64) <<"writeLowSideRx "<<parent()<<LOGVAR(burstfn)<<LOGVAR(B) 
			<<" RSSI=" <<inBurst.RSSI() << " timing=" << inBurst.timingError();
	}
}