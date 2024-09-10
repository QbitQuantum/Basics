void HitProtein::loadProteinInfo(string proteinLocation) {
	//open protein db file, read and store protein infomation
	string proteinFile(proteinLocation);
	proteinFile += proteinName;
	proteinFile += ".db";
	FILE* fptr = fopen((char*) proteinFile.c_str(), "r");
	if (fptr == NULL) {
		cout << "input file: " << proteinFile << " can't open" << endl;
	} else {
		int lineLength = 5000;
		char line[lineLength];
		while (fgets(line, lineLength, fptr) != NULL) {
			if ((strstr(line, ">Real Sequence Info:") != NULL)) {

				fgets(line, lineLength, fptr);

				int numberOfChars = 0;
				while (line[numberOfChars] != '\0') {

					numberOfChars++;
				}
				numberOfChars--;

				string _realSequenceInfo(line);

				setRealSequenceInfo(_realSequenceInfo);
				//cout << realSequenceInfo << endl;
				setRealSequenceLength(numberOfChars);
				//cout << realSequenceLength << endl;
			}
			if ((strstr(line, ">Ca XYZ:") != NULL)) {

				double Xs[realSequenceLength];
				double Ys[realSequenceLength];
				double Zs[realSequenceLength];

				double temp;
				for (int i = 0; i < realSequenceLength; i++) {
					fscanf(fptr, "%lf", &temp);
					Xs[i] = temp;
					//if (i % 10 == 0) {
					// cout << endl;
					// }
					// cout << Xs[i] << " ";
				}
				//cout << endl;

				for (int i = 0; i < realSequenceLength; i++) {
					fscanf(fptr, "%lf", &temp);
					Ys[i] = temp;
					//if (i % 10 == 0) {
					// cout << endl;
					// }
					// cout << Ys[i] << " ";
				}
				//cout << endl;
				for (int i = 0; i < realSequenceLength; i++) {
					fscanf(fptr, "%lf", &temp);
					Zs[i] = temp;
					//if (i % 10 == 0) {
					// cout << endl;
					// }
					// cout << Zs[i] << " ";
				}
				//cout << endl;
				CAlpha_XYZ = (Point*) malloc(
						sizeof(Point) * realSequenceLength);

				for (int i = 0; i < realSequenceLength; i++) {
					Point point(Xs[i], Ys[i], Zs[i]);
					CAlpha_XYZ[i] = point;
				}

			}
		}
	}

}