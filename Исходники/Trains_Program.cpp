int _tmain(int argc, _TCHAR* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Rus");

	Train *trains = nullptr;
	int count = 0;

	cout << "¬ведите количество поездов: ";
	cin >> count;

	trains = new Train[count];

	cout << "=========================================================================\n";

	for (int i = 0; i < count; ++i) {
		trains[i].Show();
		cout << "=========================================================================\n";
	}

	Train *maxTrain = GetMaxTrain(trains, count);
	cout << "Ќаибольшее количество пассажиров в поезде номер " << maxTrain->GetTrainNumber() << endl;
	cout << " оличество пассажиров: " << maxTrain->GetPassengersCount() << endl;

	Train *minTrain = GetMinTrain(trains, count);
	cout << "Ќаименьшее количество пассажиров в поезде номер " << minTrain->GetTrainNumber() << endl;
	cout << " оличество пассажиров: " << minTrain->GetPassengersCount() << endl;


	delete[] trains;
	system("pause");
	return 0;
}