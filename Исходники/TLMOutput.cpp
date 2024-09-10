// Print the project name and a time and date stamp to the top of a file 
void PrintFileHeader(FILE *File)
{
	char *TimeBuffer;
	struct tm Time;
	time_t PrintTime;
	TimeBuffer = (char*)malloc(100*sizeof(char));

	time(&PrintTime);
	gmtime_s(&Time, &PrintTime);
	asctime_s(TimeBuffer, 100, &Time);

	fprintf(File,"Event based TLM\nProject: %s\n%s\n\n", ProjectName, TimeBuffer);

	free(TimeBuffer);
}