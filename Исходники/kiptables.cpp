/** Initialize Main View
 */
void Kiptables::initView(){
	KIptablesHost *host;
	KIptablesNetwork *network;
	KIptablesTCP *tcp;
	KIptablesUDP *udp;
	mainView=new KIptablesMain(this,"MainView");
	connect(mainView,SIGNAL(clickedFWObject(QListViewItem *)),this,SLOT(itemClicked(QListViewItem *)));
	connect(mainView,SIGNAL(FWObjectsSelChanged(QListViewItem *)),this,SLOT(FWObjectsSelChanged(QListViewItem *)));
	connect(mainView,SIGNAL(rightMouseClicked(QListViewItem *,const QPoint &,int)),this,SLOT(slotRightMouseButtonClicked(QListViewItem *,const QPoint &,int)));
	// Add Hosts
	if (iptablesConfig->getHostList()->count()>0) {
		for (host=iptablesConfig->getHostList()->first();host!=0;host=iptablesConfig->getHostList()->next()) {
			mainView->addHostObject(host->getHostName());
		}
	}
	// Add Network
	if (iptablesConfig->getNetworkList()->count()>0) {
		for (network=iptablesConfig->getNetworkList()->first();network!=0;network=iptablesConfig->getNetworkList()->next()) {
			mainView->addNetworkObject(network->getNetworkName());
		}
	}
	// Add TCP
	if (iptablesConfig->getTCPList()->count()>0) {
		for (tcp=iptablesConfig->getTCPList()->first();tcp!=0;tcp=iptablesConfig->getTCPList()->next()) {
			mainView->addTCP(tcp->getPortName());
		}
	}
	// Add UDP
	if (iptablesConfig->getUDPList()->count()>0) {
		for(udp=iptablesConfig->getUDPList()->first();udp!=0;udp=iptablesConfig->getUDPList()->next()) {
			mainView->addUDP(udp->getPortName());
		}
	}		
	
	setView(mainView);
	statusBar()->insertItem("",1,0);
}