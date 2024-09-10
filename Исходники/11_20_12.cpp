int main(int argc, char** argv) {
	list<int> test1 = list<int>();
	list<int> test2 = list<int>();

	init(test1);
	init(test2);

	cout << "Done initializing...\n";

	// print(test1);
	// print(test2);

	// clock_t startTime = clock();
	// list<int> list3 = nSquaredDifference(test1, test2);
	// clock_t runTime = clock() - startTime;
	// cout << "n^2 runtime: " << ((float) runTime) / CLOCKS_PER_SEC << "\n";
	
	//print(list3);

	// clock_t startTime = clock();
	// list<int> list4 = nLogNDifference(test1, test2);
	// clock_t runTime = clock() - startTime;
	// cout << "nlogn runtime: " << ((float) runTime) / CLOCKS_PER_SEC << "\n";
	
	// print(list4);

	clock_t startTime = clock();
	list<int> list5 = nDifference(test1, test2);
	clock_t runTime = clock() - startTime;
	cout << "n runtime: " << ((float) runTime) / CLOCKS_PER_SEC << "\n";
	// print(list5);
}