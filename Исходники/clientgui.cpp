void GroupTab::consolidatePeers(map<string,string> peers, map<QString,Tab*> *tabPt, QTabWidget *tabs) {
	/*
	* TODO:
	* Cleanup this entire function
	*/
	// Create map of peers by IP
	map<string,string> peers_by_IP;
	map<string,string>::iterator it0;
	for (it0 = peers.begin(); it0 != peers.end(); it0++) {
		peers_by_IP.insert(std::pair<string,string>(it0->second,it0->first));
	}
	// Create a map of tabs open by <IP:Port,*Tab>
	map<QString,Tab*> ipMap;
	map<QString,Tab*>::iterator it1;
	for (it1 = tabPt->begin(); it1 != tabPt->end(); it1++) {
		ipMap.insert(std::pair<QString,Tab*>(it1->second->toolTip(),it1->second));
		// If peer has disconnected disable tab
		if (it1->second->tabType().compare("PEER") == 0 &&
		        peers_by_IP.find(it1->second->toolTip().toStdString()) == peers_by_IP.end()) {
			it1->second->setEnabled(false);
		}
	}

	// Iterator for peer map
	map<string,string>::iterator it;

	// Clear old peers
	online->clear();

	for (it=peers.begin(); it != peers.end(); it++) {
		// Check if tab is open by IP
		map<QString,Tab*>::iterator oldTab = ipMap.find(QString::fromStdString(it->second));
		if (oldTab != ipMap.end()) {
			// If open, enable and set nickname
			oldTab->second->setEnabled(true);
			// Change peername in tabPt
			tabPt->erase(tabs->tabText(tabs->indexOf(oldTab->second)));
			tabPt->insert(std::pair<QString,Tab*>(QString::fromStdString(it->first),oldTab->second));
			// Set tab text to new peer name
			tabs->setTabText(tabs->indexOf(oldTab->second),QString::fromStdString(it->first));
			// Change peer name in PeerTab, so it sends to the right person
			(static_cast<PeerTab *>(oldTab->second))->peer(QString::fromStdString(it->first));
		}

		QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(it->first));

		// Set tooltip as IP:Port
		item->setToolTip(QString::fromStdString(it->second));

		online->addItem(item);
		// Check if it's you
		if (client->nick().compare(it->first) == 0) {
			// Set background color to red
			item->setBackgroundColor(QColor(255,0,0,20));
		} else {
			// Assign color to peers
			// Make it look good to (use scaling hue along HSV scale)
			item->setTextColor(QColor::fromHsv(nextHue(),255,175));
		}
	}
}