int main()
{
    int N;
    vector<int> parts(5, 0);

    initializeCache();
    cin >> N; cin.ignore();
    for (int i = 0; i < N; i++) {
        string species;
        cin >> species; cin.ignore();
        int j = 0;
        while(animals[j] != species) j++;
        animalKinds[j] = true;
        aniOrder[i] = j;
    }
    for (int i = 0; i < N; i++) {
        string thing;
        int number;
        cin >> thing >> number; cin.ignore();
        int j = 0;
        while(partsName[j] != thing) j++;
        partKinds[j] = true;
        if (j == 0)
        	parts[j] = number;
        else
        	parts[j] = number/2;
    }

    char *aniCount = solve(parts);

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    int idx = 0;
    for (int i = 0; i < 5; ++i) {
    	if (!animalKinds[i]) continue;
    	int order = aniOrder[idx++];
    	cout << animals[order] << " " << int(aniCount[order]) << endl;
    }
}