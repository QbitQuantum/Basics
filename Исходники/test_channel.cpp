int ChannelClientApp::handleTimeout( Mercury::TimerID id, void * arg )
{
	ServerInterface::msg1Args & args =
		ServerInterface::msg1Args::start( pChannel_->bundle() );

	args.traits = pChannel_->traits();
	args.seq = outSeq_++;
	args.data = 0;

	if (outSeq_ == numToSend_)
	{
		ServerInterface::disconnectArgs & args =
			ServerInterface::disconnectArgs::start( pChannel_->bundle() );

		args.seq = outSeq_;
		this->stopTimer();
		pChannel_->isIrregular( true );
	}

	pChannel_->send();

	return 0;
}