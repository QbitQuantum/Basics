static void PrintTime(char *output, FILETIME TimeToPrint)
{
	WORD Date, Time;
	if (FileTimeToLocalFileTime(&TimeToPrint, &TimeToPrint) &&
				FileTimeToDosDateTime(&TimeToPrint, &Date, &Time))
	{
		// What a silly way to print out the file date/time. Oh well,
		// it works, and I'm not aware of a cleaner way to do it.
		wsprintf(output, "%d/%d/%d %02d:%02d:%02d",
					(Date / 32) & 15, Date & 31, (Date / 512) + 1980,
					(Time / 2048), (Time / 32) & 63, (Time & 31) * 2);
	}
	else
		output[0] = 0;
}