int create_Result_file()
{

	int i, nbVal;
	double tabR[20000], Inc;
	char *F_name;
	int fp;

	F_name = "j1_out.ref2";
	nbVal = 20000;

	Inc = exp(1);

	for (i = 0; i < nbVal; i++)
		tabR[i] = j1(Inc * i);

	fp = open(F_name, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (!fp) {
		printf("error opening file");
		close(fp);
		return -1;
	} else {
		for (i = 0; i < nbVal; i++) {
			write(fp, &tabR[i], sizeof(double));
		}

		close(fp);
		return 0;
	}
	return (0);
}