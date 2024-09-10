bool cPlug::Plugin()
{
	cVHPluginMgr *pm = mOwner?mOwner->mPM:NULL;
	if (pm && !IsLoaded() && CheckMakeTime()) {
		if (IsScript()) {
			ostringstream os;
			bool result = false;

			cVHPlugin *dest = GetDestPlugin();
			if (dest) {
				if (dest->SupportsMultipleScripts())
					result = dest->AddScript(mPath, os);
				else if (dest->SupportsScripts())
					result = dest->LoadScript(mPath, os);
				else {
					mLastError = _("Plugin does not support scripts.");
					SaveMe();
					return false;
				}

				if (result)
					os << _("Script loaded.");
				else
					os << _("Error loading script.");
				mLastError = os.str();
				SaveMe();
				return result;
			}
		} else {
			if (pm->LoadPlugin(mPath)) {
				mLoadTime = cTime().Sec();
				mLastError = _("Plugin loaded.");
				SaveMe();
				return true;
			} else {
				mLastError = pm->GetError();
				SaveMe();
				return false;
			}
		}
	}
	return false;
}