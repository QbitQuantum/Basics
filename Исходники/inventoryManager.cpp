//a method used to clean up any memory, may be unnecessary as vectors should deallocate its memory once it runs out of scope
//might be moved to a different location in the future
int endProgram() {
	
	//create a temporary, empty vector that can be swapped with the actual vector so to 'free' its memory
	vector<concessionItem> temp1;
	vector<starLightEvent> temp2;

	itemContainer.swap(temp1);
	eventContainer.swap(temp2);

	exit(0);
}