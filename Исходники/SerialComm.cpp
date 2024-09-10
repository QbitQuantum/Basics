bool SerialComm::ReadData() {
//	printf("%d\n", sizeof(sMapIn));
	serialPrintf(fd, "r");
	delay(200);
	return ReadRAW();
}