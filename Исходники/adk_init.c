int main (int argc, char *argv[])
{
	init();
	if(open_accesory_dev() < 0)
		return 0;
	fprintf(stdout, "Start setting up accessory\n");
	if(chAccessoryMode(
				"bols",
				"Demo",
				"Description",
				"1.0",
				//"market://search?jp.co.topgate.android.game.gree.sengoku",
				"http://market.android.com/search?q=jp.co.topgate.android.game.gree.sengoku",
				//"http://neuxs-computing.ch",
				"2hhh254711SerialNhho.") < 0){
		fprintf(stdout, "Error setting up accessory\n");
		closeHandle();
		return -1;
	};
	fprintf(stdout, "end setup\n");

	closeHandle();
	fprintf(stdout, "Done, no errors\n");
	return 0;
}