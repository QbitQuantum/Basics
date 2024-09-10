void
StatsD::mapDaemonIPs(ClassAdList &daemon_ads,CollectorList &collectors) {
	// The map of machines to IPs is used when directing ganglia to
	// associate specific metrics with specific hosts (host spoofing)

	m_daemon_ips.clear();

	daemon_ads.Open();
	ClassAd *daemon;
	while( (daemon=daemon_ads.Next()) ) {
		std::string machine,name,my_address;
		daemon->EvaluateAttrString(ATTR_MACHINE,machine);
		daemon->EvaluateAttrString(ATTR_MACHINE,name);
		daemon->EvaluateAttrString(ATTR_MY_ADDRESS,my_address);
		Sinful s(my_address.c_str());
		if( !s.getHost() ) {
			continue;
		}
		std::string ip = s.getHost();
		if( !machine.empty() ) {
			m_daemon_ips.insert( std::map< std::string,std::string >::value_type(machine,ip) );
		}
		if( !name.empty() ) {
			m_daemon_ips.insert( std::map< std::string,std::string >::value_type(name,ip) );
		}
	}
	daemon_ads.Close();

	// Also add a mapping of collector hosts to IPs, and determine the
	// collector host to use as the default machine name for aggregate
	// metrics.

	m_default_aggregate_host = "";

	DCCollector *collector=NULL;
	collectors.rewind();
	while( (collectors.next(collector)) ) {
		char const *collector_host = collector->fullHostname();
		char const *collector_addr = collector->addr();
		if( collector_host && m_default_aggregate_host.empty() ) {
			m_default_aggregate_host = collector_host;
		}
		if( collector_host && collector_addr ) {
			Sinful s(collector_addr);
			if( s.getHost() ) {
				char const *ip = s.getHost();
				m_daemon_ips.insert( std::map< std::string,std::string >::value_type(collector_host,ip) );
			}
		}
	}
}