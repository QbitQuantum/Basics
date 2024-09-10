int main(int argc, char* argv[]) {
	
	int liczba{0};
	if (argc == 2) {
		char* arg = argv[1];
		liczba = atoi(arg);
	} else {
		cout << "Podaj liczbę: ";
		cin >> liczba;
	}
	
	cout << endl << "dzielniki: "; 
	
	for (int dzielnik = 1; dzielnik <= liczba/2; dzielnik++) {
		if (liczba % dzielnik == 0)  {
			cout << dzielnik << " ";
		} 
	}
	cout << liczba << endl;
	
} 