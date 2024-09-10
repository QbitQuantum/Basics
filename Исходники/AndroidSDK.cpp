Vector<AndroidVirtualDevice> AndroidSDK::FindVirtualDevices() const
{
	Vector<AndroidVirtualDevice> avdes;
	
	String out;
	if(Sys(NormalizeExePath(AndroidPath()) + " list avd", out) == 0) {
		Vector<String> lines = Split(out, "\n");
		
		AndroidVirtualDevice avd;
		for(int i = 0; i < lines.GetCount(); i++) {
			Vector<String> line = Split(lines[i], ":");
			if(line.GetCount() == 2) {
				String tag  = line[0];
				String data = line[1];
				if(data.StartsWith(" "))
					data.Remove(0);
				if(tag.Find("Name") > -1) {
					if(!avd.GetName().IsEmpty() && avd.GetName() != data)
						avdes.Add(avd);
					avd.SetName(data);
				}
				else
				if(tag.Find("Device") > -1)
					avd.SetDeviceType(data);
				else
				if(tag.Find("Path") > -1)
					avd.SetPath(data);
				else
				if(tag.Find("Target") > -1)
					avd.SetTarget(data);
				else
				if(tag.Find("Tag/ABI") > -1)
					avd.SetAbi(data);
				
				// TODO: implement all possible tags
			}
		}
		
		if(!avd.GetName().IsEmpty())
			avdes.Add(avd);
	}
	
	return avdes;
}