bool LinuxTimestamperGeneric::HWTimestamper_adjclockphase( int64_t phase_adjust ) {
	struct timex tx;
	LinuxNetworkInterfaceList::iterator iface_iter;
	bool ret = true;
	LinuxTimerFactory factory;
	OSTimer *timer = factory.createTimer();
		
	/* Walk list of interfaces disabling them all */
	iface_iter = iface_list.begin();
	for
		( iface_iter = iface_list.begin(); iface_iter != iface_list.end();
		  ++iface_iter ) {
		(*iface_iter)->disable_clear_rx_queue();
	}
		
	rxTimestampList.clear();
		
	/* Wait 180 ms - This is plenty of time for any time sync frames
	   to clear the queue */
	timer->sleep(180000);
		
	++version;
		
	tx.modes = ADJ_SETOFFSET | ADJ_NANO;
	if( phase_adjust >= 0 ) {
		tx.time.tv_sec  = phase_adjust / 1000000000LL;
		tx.time.tv_usec = phase_adjust % 1000000000LL;
	} else {
		tx.time.tv_sec  = (phase_adjust / 1000000000LL)-1;
		tx.time.tv_usec = (phase_adjust % 1000000000LL)+1000000000;
	}

	if( !Adjust( &tx )) {
		ret = false;
	}
		
	// Walk list of interfaces re-enabling them
	iface_iter = iface_list.begin();
	for( iface_iter = iface_list.begin(); iface_iter != iface_list.end();
		 ++iface_iter ) {
		(*iface_iter)->reenable_rx_queue();
	}
	  
	delete timer;
	return ret;
}