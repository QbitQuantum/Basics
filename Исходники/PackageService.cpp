void PackageService::compact()
{
	LOG_TIMESCOPE(0, "-- PackageService::Compact");

	PackageList packages;

	while (true)
	{
		packages.clear();

		// prepare current set of linked packages to unload for safe iteration
		for (PackageNameMap::iterator itr = _linkedPackages.begin(), end = _linkedPackages.end(); itr != end; ++itr)
		{
			Ref<Package> package = itr->second;

			if (package->getUseCount() > 0) continue;
			if (package->isStayResident()) continue;
			if (package->isStayForCurrent()) continue;
			if (package->isStayForNext()) continue;

			packages.push_back(package);
		}

		if (packages.empty()) 
			break;

		// unlink all in current set
		for (uint i=0; i<packages.size(); ++i)
		{
			Ref<Package> pack = packages[i];

			pack->unlink();
		}
	}
}