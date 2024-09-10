Vector<String> ResourceSpawnImplementation::getSpawnZones(int minpool, int maxpool,
		const String& zonerestriction, Vector<String>& activeZones) {

	/**
	 * Here we are using defined rules to set the number
	 * of zones and specific zones of this specific spawn
	 */
	Vector<String> zonenames;
	int zonecount = 0;

	if(minpool == maxpool)
		zonecount = maxpool;
	else
		zonecount = System::random(maxpool - minpool) + minpool;

	if(zonecount > activeZones.size())
		zonecount = activeZones.size();

	/// If resource is zone restricted, add only the restricted zone
	if (zonerestriction != "") {
		zonenames.add(zonerestriction);
		return zonenames;
	}

	/// Randomly remove entries until the Vector contains
	/// a number of elements equal to zonecount
	while (activeZones.size() > zonecount)
		activeZones.remove(System::random(activeZones.size() - 1));

	return activeZones;
}