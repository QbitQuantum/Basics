void load_speaker_gmm () {
	printf("In load_speaker_gmm\n");
	memset(speaker_gmm, 0, sizeof(speaker_gmm));
	char buffer[100];
	memset(buffer, 0, sizeof(buffer));
	FILE *fin = fopen("by_speaker.txt", "r");
	fgets(buffer, sizeof(buffer), fin);

	int i = 0;
	for (i = 0; i < num_speaker; i++) {
		// get name
		memset(buffer, 0, sizeof(buffer));
		fgets(buffer, sizeof(buffer), fin);
		// printf("*%s*\n", buffer);
		// if (strcmp(buffer, "manae\n")) {
		// 	printf("equals!");
		// }
		strncpy(speaker_gmm[i].name, buffer, strlen(buffer) - 1);
		//printf("%d: %s ", i, speaker_gmm[i].name);


		// get M
		memset(buffer, 0, sizeof(buffer));
		fgets(buffer, sizeof(buffer), fin);
		if (strncmp(buffer, "M\n", 2) == 0) {
			//printf("read M!\n");
			int j = 0;
			for (j = 0; j < 108; j++) {
				fscanf(fin, "%lf\n", &speaker_gmm[i].m_m[j]);
			}
			// for (j = 0; j < 108; j++) {
			// 	printf("%d: %lf\n", j, speaker_gmm[i].m_m[j]);
			// }
		}

		// get V
		memset(buffer, 0, sizeof(buffer));
		fgets(buffer, sizeof(buffer), fin);
		if (strncmp(buffer, "V\n", 2) == 0) {
			//printf("read V!\n");
			int j = 0;
			for (j = 0; j < 108; j++) {
				fscanf(fin, "%lf\n", &speaker_gmm[i].m_v[j]);
			}
			// for (j = 0; j < 108; j++) {
			// 	printf("%d: %lf\n", j, speaker_gmm[i].m_v[j]);
			// }
		}

		// get W
		memset(buffer, 0, sizeof(buffer));
		fgets(buffer, sizeof(buffer), fin);
		if (strncmp(buffer, "W\n", 2) == 0) {
			//printf("read W!\n");
			int j = 0;
			for (j = 0; j < 9; j++) {
				fscanf(fin, "%lf\n", &speaker_gmm[i].m_w[j]);
			}
			// for (j = 0; j < 9; j++) {
			// 	printf("%d: %lf\n", j, speaker_gmm[i].m_w[j]);
			// }
		}
	}
	printf("Finish reading gmms.\n");
	fclose(fin);
}