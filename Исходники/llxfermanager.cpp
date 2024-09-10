void LLXferManager::retransmitUnackedPackets ()
{
	LLXfer *xferp;
	LLXfer *delp;
	xferp = mReceiveList;
	while(xferp)
	{
		if (xferp->mStatus == e_LL_XFER_IN_PROGRESS)
		{
			// if the circuit dies, abort
			if (! gMessageSystem->mCircuitInfo.isCircuitAlive( xferp->mRemoteHost ))
			{
				llinfos << "Xfer found in progress on dead circuit, aborting" << llendl;
				xferp->mCallbackResult = LL_ERR_CIRCUIT_GONE;
				xferp->processEOF();
				delp = xferp;
				xferp = xferp->mNext;
				removeXfer(delp,&mReceiveList);
				continue;
 			}
				
		}
		xferp = xferp->mNext;
	}

	xferp = mSendList; 
	updateHostStatus();
	F32 et;
	while (xferp)
	{
		if (xferp->mWaitingForACK && ( (et = xferp->ACKTimer.getElapsedTimeF32()) > LL_PACKET_TIMEOUT))
		{
			if (xferp->mRetries > LL_PACKET_RETRY_LIMIT)
			{
				llinfos << "dropping xfer " << xferp->mRemoteHost << ":" << xferp->getFileName() << " packet retransmit limit exceeded, xfer dropped" << llendl;
				xferp->abort(LL_ERR_TCP_TIMEOUT);
				delp = xferp;
				xferp = xferp->mNext;
				removeXfer(delp,&mSendList);
			}
			else
			{
				llinfos << "resending xfer " << xferp->mRemoteHost << ":" << xferp->getFileName() << " packet unconfirmed after: "<< et << " sec, packet " << xferp->mPacketNum << llendl;
				xferp->resendLastPacket();
				xferp = xferp->mNext;
			}
		}
		else if ((xferp->mStatus == e_LL_XFER_REGISTERED) && ( (et = xferp->ACKTimer.getElapsedTimeF32()) > LL_XFER_REGISTRATION_TIMEOUT))
		{
			llinfos << "registered xfer never requested, xfer dropped" << llendl;
			xferp->abort(LL_ERR_TCP_TIMEOUT);
			delp = xferp;
			xferp = xferp->mNext;
			removeXfer(delp,&mSendList);
		}
		else if (xferp->mStatus == e_LL_XFER_ABORTED)
		{
			llwarns << "Removing aborted xfer " << xferp->mRemoteHost << ":" << xferp->getFileName() << llendl;
			delp = xferp;
			xferp = xferp->mNext;
			removeXfer(delp,&mSendList);
		}
		else if (xferp->mStatus == e_LL_XFER_PENDING)
		{
//			llinfos << "*** numActiveXfers = " << numActiveXfers(xferp->mRemoteHost) << "        mMaxOutgoingXfersPerCircuit = " << mMaxOutgoingXfersPerCircuit << llendl;   
			if (numActiveXfers(xferp->mRemoteHost) < mMaxOutgoingXfersPerCircuit)
			{
//			    llinfos << "bumping pending xfer to active" << llendl;
				xferp->sendNextPacket();
				changeNumActiveXfers(xferp->mRemoteHost,1);
			}			
			xferp = xferp->mNext;
		}
		else
		{
			xferp = xferp->mNext;
		}
	}

	//
	// HACK - if we're using xfer confirm throttling, throttle our xfer confirms here
	// so we don't blow through bandwidth.
	//

	while (mXferAckQueue.getLength())
	{
		if (mAckThrottle.checkOverflow(1000.0f*8.0f))
		{
			break;
		}
		//llinfos << "Confirm packet queue length:" << mXferAckQueue.getLength() << llendl;
		LLXferAckInfo ack_info;
		mXferAckQueue.pop(ack_info);
		//llinfos << "Sending confirm packet" << llendl;
		sendConfirmPacket(gMessageSystem, ack_info.mID, ack_info.mPacketNum, ack_info.mRemoteHost);
		mAckThrottle.throttleOverflow(1000.f*8.f); // Assume 1000 bytes/packet
	}
}