int main(void) {
	unsigned seed;

	//cout << "Enter seed: ";
	//cin >> seed;
	seed = time(0);
	srand(seed);

	for (int counter = 1; counter <= 20; counter++) {
		cout << setw(10) << (1 + rand() % 6);

		if (counter % 5 == 0)
			cout << endl;
	}

	return 0;
}