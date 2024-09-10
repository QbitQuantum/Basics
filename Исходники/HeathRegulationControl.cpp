//
//schrijfFile() for test fase. This file can you use in excel to make a grafic ot the data
//
void HeathRegulationControl::schrijfFile() {
	//wegschrijven naar file//

	FILE	*hp;

	hp = fopen("temperaturener.txt", "a");

	char dateStr [9];
	char timeStr [9];
	_strdate( dateStr);
	_strtime( timeStr);
	fprintf(hp, "%s - ", dateStr);
	fprintf(hp, "%s ", timeStr);
	fprintf(hp, "%3.2f ", calculate.getTemperatures(0));
	fprintf(hp, "%3.2f ", calculate.getTemperatures(1));
	fprintf(hp, "%3.2f ", calculate.getTemperatures(2));
	fprintf(hp, "%3.2f ", calculate.getTemperatures(3));
	fprintf(hp, "%3.2f ", calculate.getTemperatures(4));
	fprintf(hp, "%3.2f ", calculate.getTemperatures(5));
	fprintf(hp, "%3.2f ", calculate.getTemperatures(6));
	fprintf(hp, "%3.2f ", calculate.getSetpoint());
	fprintf(hp, "%3.2f ", calculate.getAverage());
	fprintf(hp, "Outdoor Temperature=%5.2f ", calculate.getTemperatures(6));
	fprintf(hp, "(Buiten_regeling_%s)", (calculate.getStateFans((4/3)-1)==1) ? "aan" : "uit");
	fprintf(hp, "%3.2f ", calculate.getMaxAverage());
	fprintf(hp, "%3.2f \n", calculate.getMinAverage());

	fclose(hp);
}