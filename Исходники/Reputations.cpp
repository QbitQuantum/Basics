void ReputationsInit() {
	int count;
	if(count=GetPrivateProfileIntA("Misc", "CityRepsCount", 0, ini)) {
		repList=new CityRep[count];
		char buf[512];
		GetPrivateProfileStringA("Misc", "CityRepsList", "", buf, 512, ini);
		char* end;
		char* start=buf;
		for(int i=0;i<count;i++) {
			end=strchr(start,':');
			*end='\0';
			repList[i].cityID=atoi(start);
			start=end+1;
			if(i==count-1) {
				repList[i].globalID=atoi(start);
			} else {
				end=strchr(start,',');
				*end='\0';
				repList[i].globalID=atoi(start);
				start=end+1;
			}
		}

		SafeWrite32(0x43BEA5, (DWORD)&repList[0].cityID);
		SafeWrite32(0x43BF3C, (DWORD)&repList[0].cityID);
		SafeWrite32(0x43BF4C, (DWORD)&repList[0].globalID);
		SafeWrite32(0x43C03E, count*8);
	}
}