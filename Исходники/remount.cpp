void RemountCommand::cloneMountpoint(Cmdline const & cl)
{
	Key existingParent (Backends::getBasePath(existingName), KEY_END);
	Key newParent (Backends::getBasePath(mp), KEY_END);

	KeySet existingBackend = mountConf.cut(existingParent);
	mountConf.append(existingBackend);
	KeySet newBackend(existingBackend.size(), KS_END);
	string configPath = newParent.getName() + "/config/path";
	string mpPath = newParent.getName() + "/mountpoint";
	existingBackend.rewind();
	while (Key current = existingBackend.next())
	{
		Key newKey = rebaseKey (current, existingParent, newParent);
		newBackend.append(newKey);

		if (newKey.getName() == mpPath)
		{
			newKey.setString(mp);
		}

		if (newKey.getName() == configPath)
		{
			newKey.setString(cl.arguments[0]);
		}
	}

	mountConf.append(newBackend);
}