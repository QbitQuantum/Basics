void exitApplication(int s){

	killed=true;

	if (interface1 != NULL)
		delete interface1;

	ic->shutdown();
	exit(0);
}