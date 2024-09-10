int main(int argc, char *argv[])
{
	//testing Maps
	//map object
	Map<string, string> newMap;

	cout << "Size of an empty map should be: " << newMap.size() << endl; //answer = 0

	try{
		newMap.remove("Aaron"); //should do nothing
	}catch(exception &e){
		cout << e.what() << endl;
	}

	//now adding things to the map
	string people[] = {"Aaron", "Afsin", "Alana", "David", "Johnathan", "Nikhil", "Joseph", "Matthew", "Douglass", "Ruyan", "Ian", "Connor", "Stephen", "Ellen", "Erika"};
	for(int i = 0; i < 15; i++){
		newMap.add(people[i], people[i] + "@usc.edu");
	}
	cout << "Now the size of the map should be 15! Actual size: " << newMap.size() << endl;

	bool success = false;
	cout << "Alana's email is: " << newMap.get("Alana", success) << endl; //should be [email protected]
	if(success == false){
		cout << "There is something wrong with your get function!" << endl;
	}

	//add a different value for alana, see if the add function is working properly
	try{
		newMap.add("Alana", "*****@*****.**");
	}catch(exception &e){
		cout << e.what() << endl;
	}
	success = false;
	cout << "Alana's email should still be [email protected]. My output: " << newMap.get("Alana", success) << endl;
	//if Alana's email wasn't [email protected], then something is wrong with the add function

	//remove every third person from the map
	for(int i = 0; i < 15; i+=3){
		newMap.remove(people[i]);
	}
	cout << "Now size of the map should be 10! Actual size: " << newMap.size() << endl;

	//now testing merge
	Map<string, string> mapOther;
	for(int i = 0; i < 15; i++){
		mapOther.add(people[i], people[i] + "@usc.edu");
	}
	//now mapOther has 15 items and newMap has 10. The five items previously deleted from newMap should be added back in
	newMap.merge(mapOther);

	cout << "Now size of map should be 15. Actual size: " << newMap.size() << endl;

	//print out newMap using get to make sure all emails have been added back in
	int newMapSize = newMap.size();
	bool test;
	for(int i = 0; i < newMapSize; i++){
		test = false;
		cout << newMap.get(people[i], test) << endl;
		if(!test){
			cout << "There's something wrong with the get function, recheck your code!" << endl;
			break;
		}
	}

	return 0;
}