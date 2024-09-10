int main(int argc, char** argv) {
	list<int> list1;
	list<int> list2;
	clock_t startTime;

	init(list1);
	init(list2);

	// print(list1);
	// print(list2);
	startTime = clock();
	list<int> list3 = nSquaredUnion(list1, list2);
	// print(list3);
	cout << "Time for n^2 Union: " << clock() - startTime << "\n";

	startTime = clock();
	list<int> list4 = nLogNUnion(list1, list2);
	// print(list4);
	cout << "Time for nlogn Union: " << clock() - startTime << "\n";

	startTime = clock();
	list<int> list5 = nSquaredIntersection(list1, list2);
	// print(list5);
	cout << "Time for n^2 Intersection: " << clock() - startTime << "\n";

	startTime = clock();
	list<int> list6 = nLogNIntersection(list1, list2);
	// print(list6);
	cout << "Time for nlogn Intersection: " << clock() - startTime << "\n";

	cout << "\n";

	cout << list1.size() << "\n";
	cout << list2.size() << "\n";
	cout << list3.size() << "\n";
	cout << list4.size() << "\n";
	cout << list5.size() << "\n";
	cout << list6.size() << "\n";
	// cout << list1.size() << "\n";
	// cout << list2.size() << "\n";

}