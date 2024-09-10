status_t MSNConnection::HandleCHL( Command * command ) {
	LOG(kProtocolName, liDebug, "C %lX: Processing CHL", this);

	const char *challenge = command->Param(0);
	int i = 0;
	unsigned char buf[256];
	char chlString[128];
	long long high = 0;
	long long low = 0;
	long long temp = 0;
	long long key = 0;
	long long bskey = 0;
	int *chlStringArray = (int *)chlString;
	int *md5hash = (int *)buf;
	char hash1a[17];
	char hash2a[17];

	sprintf((char *)buf + 16, "%s%s", challenge, kClientCode);
	MD5(buf + 16, strlen((char *)buf + 16), buf);
	for (i = 0; i < 16; i++) {
		sprintf((char *)buf + 16 + i * 2,"%02x", buf[i]);
	};
	
	for (i = 0; i < 4; i++) {
	   md5hash[i] = md5hash[i] & 0x7FFFFFFF;
	};
	
	i = (strlen(challenge) + strlen(kClientID) + 7) & 0xF8;
	sprintf(chlString,"%s%s00000000", challenge, kClientID);
	chlString[i] = 0;
	
	for (i = 0; i < (int)strlen(chlString) / 4; i += 2) {
		temp = chlStringArray[i];
		
		temp = (0x0E79A9C1 * temp) % 0x7FFFFFFF;
		temp += high;
		temp = md5hash[0] * temp + md5hash[1];
		temp = temp % 0x7FFFFFFF;
		
		high = chlStringArray[i + 1];
		high = (high + temp) % 0x7FFFFFFF;
		high = md5hash[2] * high + md5hash[3];
		high = high % 0x7FFFFFFF;
		
		low = low + high + temp;
	};
	
	high = (high + md5hash[1]) % 0x7FFFFFFF;
	low = (low + md5hash[3]) % 0x7FFFFFFF;
	
	key = (low << 32) + high;
	for (i= 0; i < 8; i++) {
		bskey <<= 8;
		bskey += key & 255;
		key >>=8;
	};
	
	strncpy((char *)hash1a, (char *)buf + 16, 16);
	strncpy((char *)hash2a, (char *)buf + 32, 16);
	hash1a[16] = '\0';
	hash2a[16] = '\0';
	
	sprintf((char *)buf, "%llx%llx", strtoull(hash1a,NULL,16) ^ bskey,
		strtoull(hash2a,NULL,16) ^ bskey);

	Command *reply = new Command("QRY");
	reply->AddParam(kClientID);
	reply->AddPayload((char *)buf, 32);
	
	Send(reply);
	reply->Debug();
	
	return B_OK;
};