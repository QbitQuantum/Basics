void SLBus::addClip( std::shared_ptr<SLClip> clip )
{
	stk::FileWvIn f( clip->getURI() );
	float duration = f.getSize() / f.getFileRate();
	
	if ( lo_send( sl_target_, "/loop_add", "if", f.channelsOut(), duration ) == -1 ) {
		spdlog::get( "main" )->error(
			"OSC error {}: {}", lo_address_errno(sl_target_), lo_address_errstr(sl_target_)
		);
	}
	else {
		clip->setParent( this );
		clip->setSLid( clipset_.size() );
		clip->SLget( "state" );
		sleep(1);
		clip->SLget( "state" );
		clip->SLload();
		clipset_.push_back( clip );
		Waiter::getInstance()->selectClip( clip );
	}
}