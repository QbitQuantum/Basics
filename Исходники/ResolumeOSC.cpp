void ResolumeOSC::clearLayer(int layerID) {
	string address = "/layerX/clear";
	address[6] = intToChar(layerID);

	send(address, 1);
}