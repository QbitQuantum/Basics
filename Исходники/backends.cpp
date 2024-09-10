/**
 * @brief give info about current mounted backends
 *
 * @param mountConf a keyset that contains everything below
 * Backends::mountpointsPath
 *
 * @return an vector of information about mounted backends
 */
Backends::BackendInfoVector Backends::getBackendInfo (KeySet mountConf)
{
	std::vector<BackendInfo> ret;
	Key rootKey (Backends::mountpointsPath, KEY_END);
	Key cur;

	mountConf.rewind ();
	while ((cur = mountConf.next ()))
	{
		if (cur.isDirectBelow (rootKey))
		{
			BackendInfo bi;

			Key path = mountConf.lookup (cur.getName () + "/config/path");
			if (path)
			{
				bi.path = path.getString ();
			}
			Key mp = mountConf.lookup (cur.getName () + "/mountpoint");
			if (mp)
			{
				bi.mountpoint = mp.getString ();
			}
			bi.name = cur.getBaseName ();

			ret.push_back (bi);
		}
	}
	return ret;
}