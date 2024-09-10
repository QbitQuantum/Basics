int main(int argc, char* argv[])
{
	long status;
	unsigned long cardType;
	unsigned long cardSN;
	BYTE userID;

	status = OpenPort(1, 9600);
	if (!status) {
		status = LinkRW();
		if (status) {
			ClosePort();
			fprintf(stderr, "Connect Fail\n");
			return -1;
		}
		fprintf(stderr, "Connect Succeed\n");
		//beepOn();

		//card polling
		while (1) {
			status = GetCardType(&cardType);
			if (!status) {
				delayMS(5);
				if (cardType == 4) { //Mifare 1
					status = mfGetCardSnr(&cardSN);
					if (status) { 
						status = mfTransKey();
						if (status) {
							status = SelectCard(cardSN);
							if (!status) {
								fprintf(stderr, "Activate Succeed\n");
								userID = getUserID(cardSN);
								fprintf(stdout, "%x", userID);
								HaltCard();
								//delayMS(3000);
								break;
							}
						}
					}
				}
			}
		}		
	}
	else {
		fprintf(stderr, "Connect Fail\n");
		return -1;
	}

	ClosePort();
	return 0;
}