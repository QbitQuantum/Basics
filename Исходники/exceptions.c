void snp() {
	int back = kernel;
	kernel = 1;
	printf("Segment Not Present\n");
	kill(0, 0, getPID());
	kernel = back;
}